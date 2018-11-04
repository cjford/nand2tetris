class VMWriter
  def initialize(output_file_path)
    @output_file = File.open(output_file_path, 'w+')
  end

  def write_push(segment, index)
    output_file.write("push #{segment} #{index}\n")
  end

  def write_pop(segment, index)
    output_file.write("pop #{segment} #{index}\n")
  end

  def write_arithmetic(op_symbol)
    command = case op_symbol
      when '+'     then 'add'
      when '-'     then 'sub'
      when '='     then 'eq'
      when '*'     then 'call Math.multiply 2'
      when '/'     then 'call Math.divide 2'
      when '|'     then 'or'
      when '&amp;' then 'and'
      when '&lt;'  then 'lt'
      when '&gt;'  then 'gt'
      else "unkown arithmetic symbol #{op_symbol}"
      end

    output_file.write("#{command}\n")
  end

   def write_unary_arithmetic(op_symbol)
    command = case op_symbol
      when '~' then 'not'
      when '-' then 'neg'
      else 'unkown unary arithmetic symbol'
      end

    output_file.write("#{command}\n")
  end

  def write_label(label)
    output_file.write("label #{label}\n")
  end

  def write_goto(label)
    output_file.write("goto #{label}\n")
  end

  def write_if(label)
    output_file.write("if-goto #{label}\n")
  end

  def write_call(function_name, arg_count)
    output_file.write("call #{function_name} #{arg_count}\n")
  end

  def write_function(function_name, local_count)
    output_file.write("function #{function_name} #{local_count}\n")
  end

  def write_return
    output_file.write("return\n")
  end

  def close
    @output_file.close
  end

  private

  attr_reader :output_file
end
