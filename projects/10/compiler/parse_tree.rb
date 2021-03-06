require_relative './symbol_table'
require_relative './vm_writer'

class ParseTree
  def initialize(tokenizer, input_file)
    @tokenizer = tokenizer
    @input_file = input_file

    @symbol_table = SymbolTable.new
    @writer = VMWriter.new(@input_file.gsub('.jack', '.vm'))
    @label_id_index = 0
  end

  def build
    @tokenizer.tokenize
    @root_node = accept_class

    File.open(@input_file.gsub('.jack', '.xml'), 'w+') { |f| f.write(@root_node.to_xml) }
  end

  def token
    @tokenizer.current_token
  end

  def next_token
    @tokenizer.next_token
  end

  class Node
    attr_reader :token, :children
    attr_accessor :parent

    def initialize(token, children = [])
      @token = token
      @children = children
      children.compact.each { |child| child.parent = self }
    end

    def to_xml(indentation_level = 0)
      output_string = ''

      if token.is_a?(Token)
        indentation_level.times { output_string += '  ' }
        output_string += "<#{token.type}> #{token.value.gsub('"', '')} </#{token.type}>\n"
      else
        indentation_level.times { output_string += '  ' }
        output_string += "<#{token}>\n"
        children.compact.each do |child|
          output_string += child.to_xml(indentation_level + 1)
        end
        indentation_level.times { output_string += '  ' }
        output_string += "</#{token}>\n"
      end

      output_string
    end
  end

  private

  def accept(accepted)
    if (accepted.is_a?(Symbol) && token.type == accepted) || (accepted.is_a?(String) && token.value == accepted)
      accepted_node = Node.new(token)
      @tokenizer.advance

      return accepted_node
    end

    nil
  end

  def accept_type
    accept('int') || accept('char') || accept('boolean') || accept(:identifier)
  end

  def accept_class
    nodes = [
      accept('class'),
      accept(:identifier),
      accept('{')
    ]

    @class_name = nodes[1].token.value

    while ['static', 'field'].include?(token.value)
      nodes << accept_class_var_dec
    end

    while ['constructor', 'function', 'method'].include?(token.value)
      nodes << accept_subroutine_dec
      @symbol_table.start_subroutine
    end

    nodes << accept('}')

    Node.new('class', nodes)
  end

  def accept_class_var_dec
    nodes = [
      (accept('static') || accept('field')),
      accept_type,
      accept(:identifier)
    ]

    @symbol_table.define(nodes[2].token.value, nodes[1].token.value, nodes[0].token.value)

    while comma = accept(',')
      nodes << comma

      nodes << accept(:identifier)

      @symbol_table.define(nodes.last.token.value, nodes[1].token.value, nodes[0].token.value)
    end

    nodes << accept(';')

    Node.new('classVarDec', nodes)
  end

  def accept_subroutine_dec
    nodes =  [ (accept('constructor') || accept('function') || accept('method')) ]
    function_type = nodes.last.token.value

    nodes += [
      (accept('void') || accept_type),
      accept(:identifier)
    ]

    function_name = "#{@class_name}.#{nodes.last.token.value}"

    nodes += [
      accept('('),
      accept_parameter_list,
      accept(')')
    ]

    @symbol_table.increment_argument_indicies if function_type == 'method'
    nodes << accept_subroutine_body(function_type, function_name)

    Node.new('subroutineDec', nodes)
  end


  def accept_subroutine_body(function_type, function_name)
    nodes = [ accept('{') ]

    nodes << accept_var_dec while token.value == 'var'

    var_dec_nodes = nodes.select { |n| n.token == 'varDec' }
    local_var_count = var_dec_nodes.count
    local_var_count += var_dec_nodes.map(&:children).flatten.count { |n| n.token.value == ',' }

    @writer.write_function(function_name, local_var_count)

    if function_type == 'constructor'
      @writer.write_push('constant', @symbol_table.count('field'))
      @writer.write_call('Memory.alloc', 1)
      @writer.write_pop('pointer', 0)
    elsif function_type == 'method'
      @writer.write_push('argument', 0)
      @writer.write_pop('pointer', 0)
    end

    nodes += [
      accept_statements,
      accept('}')
    ]

    Node.new('subroutineBody', nodes)
  end

  def accept_parameter_list
    nodes = [accept_type, accept(:identifier)].compact

    return Node.new('parameterList') if nodes.count < 2

    @symbol_table.define(nodes[1].token.value, nodes[0].token.value, 'argument')

    while comma = accept(',')
      nodes << comma
      nodes += [accept_type, accept(:identifier)]

      @symbol_table.define(nodes.last.token.value, nodes.last(2).first.token.value, 'argument')
    end

    Node.new('parameterList', nodes)
  end

  def accept_var_dec
    nodes = [
      accept('var'),
      accept_type,
      accept(:identifier)
    ]

    @symbol_table.define(nodes[2].token.value, nodes[1].token.value, 'var')

    while comma = accept(',')
      nodes << comma
      nodes << accept(:identifier)

      @symbol_table.define(nodes.last.token.value, nodes[1].token.value, 'var')
    end

    nodes << accept(';')

    Node.new('varDec', nodes)
  end

  def accept_statements
    nodes = []
    nodes << accept_statement while %w[let if while do return].include?(token.value)
    Node.new('statements', nodes)
  end

  def accept_statement
    case token.value
      when 'let'    then accept_let
      when 'if'     then accept_if
      when 'while'  then accept_while
      when 'do'     then accept_do
      when 'return' then accept_return
    end
  end

  def accept_do
    nodes = [accept('do')]
    nodes += accept_subroutine_call
    nodes << accept(';')

    @writer.write_pop('temp', 0)

    Node.new('doStatement', nodes)
  end

  def accept_let
    nodes = [
      accept('let'),
      accept(:identifier)
    ]

    if token.value == '['
      array_assignment = true
      nodes += [
        accept('['),
        accept_expression,
        accept(']')
      ]

      symbol = @symbol_table.find(nodes[1].token.value)
      @writer.write_push(symbol[:segment], symbol[:index])
      @writer.write_arithmetic('+')
      @writer.write_pop('temp', 0)
    end

    nodes += [
      accept('='),
      accept_expression,
      accept(';')
    ]

    @writer.write_push('temp', 0)
    @writer.write_pop('pointer', 1)

    if array_assignment
      @writer.write_pop('that', 0)
    else
      symbol = @symbol_table.find(nodes[1].token.value)
      @writer.write_pop(symbol[:segment], symbol[:index])
    end

    Node.new('letStatement', nodes)
  end

  def accept_while
    label_id = @label_id_index
    @label_id_index += 1

    @writer.write_label("WHILE_#{label_id}_START")
    nodes = [
      accept('while'),
      accept('('),
      accept_expression
    ]

    @writer.write_unary_arithmetic('~')
    @writer.write_if("WHILE_#{label_id}_END")

    nodes += [
      accept(')'),
      accept('{'),
      accept_statements,
      accept('}')
    ]

    @writer.write_goto("WHILE_#{label_id}_START")
    @writer.write_label("WHILE_#{label_id}_END")


    Node.new('whileStatement', nodes)
  end

  def accept_return
    nodes = [
      accept('return'),
      accept_expression,
      accept(';')
    ]

    @writer.write_push('constant', 0) if nodes[1].nil?
    @writer.write_return

    Node.new('returnStatement', nodes)
  end

  def accept_if
    label_id = @label_id_index
    @label_id_index += 1

    nodes = [
      accept('if'),
      accept('('),
      accept_expression
    ]

    @writer.write_unary_arithmetic('~')
    @writer.write_if("ELSE_#{label_id}")

    nodes += [
      accept(')'),
      accept('{'),
      accept_statements,
      accept('}')
    ]

    @writer.write_goto("IF_#{label_id}_END")
    @writer.write_label("ELSE_#{label_id}")

    if token.value == 'else'
      nodes += [
        accept('else'),
        accept('{'),
        accept_statements,
        accept('}')
      ]
    end

    @writer.write_label("IF_#{label_id}_END")

    Node.new('ifStatement', nodes)
  end

  def accept_expression
    nodes = [accept_term]

    return if nodes.first.nil?

    while op = accept_op
      nodes << op
      nodes << accept_term

      @writer.write_arithmetic(op.token.value)
    end

    Node.new('expression', nodes)
  end

  def accept_term
    nodes = []

    if token.value == '('
      nodes += [
        accept('('),
        accept_expression,
        accept(')')
      ]
    elsif ['-', '~'].include? token.value
      unary_op = accept_unary_op
      nodes += [
        unary_op,
        accept_term
      ]

      @writer.write_unary_arithmetic(unary_op.token.value)
    elsif token.type == :identifier
      if next_token.value == '['
        nodes += accept_array_access
      elsif (next_token.value == '(' || next_token.value == '.')
        nodes += accept_subroutine_call
      else
        nodes << accept(:identifier)

        symbol = @symbol_table.find(nodes.last.token.value)
        @writer.write_push(symbol[:segment], symbol[:index])
      end
    elsif new_node = (accept(:integerConstant) || accept(:stringConstant) || accept_keyword_const)
      nodes << new_node
      write_constant_term(new_node)
    end

    return if nodes.compact.empty?
    Node.new('term', nodes)
  end

  def accept_keyword_const
    accept('true') || accept('false') || accept('null') || accept('this')
  end

  def accept_op
    accept('+') || accept('-') || accept('*')|| accept('/') ||
    accept('=') || accept('|') || accept('&amp;')|| accept('&lt;') || accept('&gt;')
  end

  def accept_unary_op
    accept('-') || accept('~')
  end

  def accept_array_access
    nodes = [
      accept(:identifier),
      accept('['),
      accept_expression,
      accept(']')
    ]

    symbol = @symbol_table.find(nodes[0].token.value)
    @writer.write_push(symbol[:segment], symbol[:index])
    @writer.write_arithmetic('+')
    @writer.write_pop('pointer', 1)
    @writer.write_push('that', 0)

    nodes
  end

  def accept_expression_list
    nodes = [accept_expression]
    if nodes.first.nil?
      return Node.new('expressionList')
    end

    while comma = accept(',')
      nodes << comma
      nodes << accept_expression
    end

    Node.new('expressionList', nodes)
  end

  def accept_subroutine_call
    return accept_subroutine_call_without_receiver if next_token.value == '('
    accept_subroutine_call_with_receiver
  end

  def accept_subroutine_call_with_receiver
    nodes = [
      accept(:identifier),
      accept('.'),
      accept(:identifier),
      accept('(')
    ]

    if symbol = @symbol_table.find(nodes[0].token.value)
      function_name = "#{symbol[:type]}.#{nodes[2].token.value}"
      argument_count = 1
      @writer.write_push(symbol[:segment], symbol[:index]) if symbol
    else
      argument_count = 0
      function_name = "#{nodes[0].token.value}.#{nodes[2].token.value}"
    end

    expression_list = accept_expression_list
    nodes << expression_list
    nodes << accept(')')

    argument_count += expression_list.children.count { |list| list.token == 'expression' }

    @writer.write_call(function_name, argument_count)

    nodes
  end

  def accept_subroutine_call_without_receiver
    nodes = [
      accept(:identifier),
      accept('(')
    ]

    @writer.write_push('pointer', 0)

    expression_list = accept_expression_list
    argument_count = expression_list.children.count { |list| list.token == 'expression' } + 1
    nodes << expression_list
    nodes << accept(')')

    @writer.write_call("#{@class_name}.#{nodes[0].token.value}", argument_count)

    nodes
  end

  def write_constant_term(new_node)
    if new_node.token.type == :stringConstant
      string = new_node.token.value.dup
      string.gsub!('"', '')

      @writer.write_push('constant', string.length)
      @writer.write_call('String.new', 1)

      string.split('').each do |char|
        @writer.write_push('constant', char.ord)
        @writer.write_call('String.appendChar', 2)
      end
    elsif new_node.token.value == 'this'
      @writer.write_push('pointer', 0)
    else
      value = new_node.token.value
      if value == 'true'
        @writer.write_push('constant', 1)
        @writer.write_unary_arithmetic('-')
      elsif value == 'false' || value == 'null'
        @writer.write_push('constant', 0)
      else
        @writer.write_push('constant', value)
      end
    end
  end
end
