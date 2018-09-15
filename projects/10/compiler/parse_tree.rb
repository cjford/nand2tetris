class ParseTree
  attr_accessor :root_node

  def initialize(tokenizer)
    @tokenizer = tokenizer
  end

  def build
    @tokenizer.tokenize
    @root_node = accept_class
  end

  def token
    @tokenizer.current_token
  end

  def next_token
    @tokenizer.next_token
  end

  class Node
    attr_accessor :token, :child_nodes

    def initialize(token, child_nodes = [])
      @token = token
      @child_nodes = child_nodes
    end

    def add_child(token)
      child = Node.new(token, self)
      child_nodes << child

      child
    end

    def to_xml(indentation_level = 0)
      output_string = ''

      if token.is_a?(Token)
        indentation_level.times { output_string += '  ' }
        output_string += "<#{token.type}> #{token.value} </#{token.type}>\n"
      else
        indentation_level.times { output_string += '  ' }
        output_string += "<#{token}>\n"
        child_nodes.compact.each do |child|
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
    nodes = []
    nodes << accept('class')
    nodes << accept(:identifier)
    nodes << accept('{')

    while ['static', 'field'].include?(token.value)
      nodes << accept_class_var_dec
    end

    while ['constructor', 'function', 'method'].include?(token.value)
      nodes << accept_subroutine_dec
    end

    nodes << accept('}')

    Node.new('class', nodes)
  end

  def accept_class_var_dec
    nodes = []

    nodes << (accept('static') || accept('field'))
    nodes << accept_type
    nodes << accept(:identifier)

    while comma = accept(',')
      nodes << comma
      nodes << accept(:identifier)
    end

    nodes << accept(';')

    Node.new('classVarDec', nodes)
  end

  def accept_subroutine_dec
    nodes = []

    nodes << (accept('constructor') || accept('function') || accept('method'))
    nodes << (accept('void') || accept_type)
    nodes << accept(:identifier)
    nodes << accept('(')
    nodes << accept_parameter_list
    nodes << accept(')')
    nodes << accept_subroutine_body

    Node.new('subroutineDec', nodes)
  end


  def accept_subroutine_body
    nodes = [ accept('{') ]

    nodes << accept_var_dec while token.value == 'var'

    nodes += [
      accept_statements,
      accept('}')
    ]

    Node.new('subroutineBody', nodes)
  end

  def accept_parameter_list
    nodes = [accept_type, accept(:identifier)].compact

    return Node.new('parameterList') if nodes.count < 2

    while comma = accept(',')
      nodes << comma
      nodes += [accept_type, accept(:identifier)]
    end

    Node.new('parameterList', nodes)
  end

  def accept_var_dec
    nodes = [
      accept('var'),
      accept_type,
      accept(:identifier)
    ]

    while comma = accept(',')
      nodes << comma
      nodes << accept(:identifier)
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

    Node.new('doStatement', nodes)
  end

  def accept_let
    nodes = [
      accept('let'),
      accept(:identifier)
    ]

    if token.value == '['
      nodes += [
        accept('['),
        accept_expression,
        accept(']')
      ]
    end

    nodes += [
      accept('='),
      accept_expression,
      accept(';')
    ]

    Node.new('letStatement', nodes)
  end

  def accept_while
    nodes = [
      accept('while'),
      accept('('),
      accept_expression,
      accept(')'),
      accept('{'),
      accept_statements,
      accept('}')
    ]

    Node.new('whileStatement', nodes)
  end

  def accept_return
    nodes = [
      accept('return'),
      accept_expression,
      accept(';')
    ]

    Node.new('returnStatement', nodes)
  end

  def accept_if
    nodes = [
      accept('if'),
      accept('('),
      accept_expression,
      accept(')'),
      accept('{'),
      accept_statements,
      accept('}')
    ]

    if token.value == 'else'
      nodes += [
        accept('else'),
        accept('{'),
        accept_statements,
        accept('}')
      ]
    end

    Node.new('ifStatement', nodes)
  end

  def accept_expression
    nodes = [accept_term]

    return if nodes.first.nil?

    while op = accept_op
      nodes << op
      nodes << accept_term
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
    elsif token.type == :identifier
      if next_token.value == '['
        nodes += accept_array_access
      elsif next_token.value == '('
        nodes += accept_subroutine_call
      else
        nodes << accept(:identifier)
      end
    elsif ['-', '~'].include? token.value
      nodes += [
        accept_unary_op,
        accept_term
      ]
    else
      nodes << (accept(:integerConstant) || accept(:stringConstant) || accept_keyword_const || accept_unary_op)
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
    [
      accept(:identifier),
      accept('['),
      accept_expression,
      accept(']')
    ]
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
    return accept_subroutine_call_without_receiver if next_token == '('
    accept_subroutine_call_with_receiver
  end

  def accept_subroutine_call_with_receiver
    [
      accept(:identifier),
      accept('.'),
      accept(:identifier),
      accept('('),
      accept_expression_list,
      accept(')')
    ]
  end

  def accept_subroutine_call_without_receiver
    [
      accept(:identifer),
      accept('('),
      accept_expression_list,
      accept(')')
    ]
  end
end
