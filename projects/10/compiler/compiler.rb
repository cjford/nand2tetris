require_relative './tokenizer.rb'
require_relative './symbol_table'
require_relative './parse_tree'

class Compiler
  def initialize(args)
    @args = args
  end

  def compile
    input_files.each do |input_file|
      tokenizer = Tokenizer.new(input_file)
      parse_tree = ParseTree.new(tokenizer, input_file)
      parse_tree.build
    end
  end

  private

  def input_files
    raise 'Please specify a file or directory for compilation' unless @args[0]

    if @args[0].match(/^\S+\.jack$/) && File.file?(@args[0])
      return [@args[0]]
    elsif File.directory?(@args[0])
      return Dir.glob("#{@args[0]}/*.jack")
    end

    raise 'Specified input file/directory was not found'
  end
end

compiler = Compiler.new(ARGV)
compiler.compile
