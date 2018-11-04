require_relative './token.rb'
require_relative './language_rules.rb'

class Tokenizer
  include LanguageRules

  def initialize(input_file)
    @input_file = input_file
    @tokens = []
    @current_token_index = 0
  end

  def tokenize
    input_string = File.read(input_file)
    input_string.gsub!(/\/\*(.|\n)*?\*\/|\/\/.*$|^\s*|\s*$/, '')

    token_strings = input_string.split(delimiter_regexp).reject(&:empty?)
    token_strings = handle_reserved_symbols(token_strings)

    @tokens = token_strings.map { |token_string| Token.new(token_string) }
    @current_token_index = 0
  end

  def handle_reserved_symbols(token_strings)
    token_strings.map do |token|
      case token
      when '<' then '&lt;'
      when '>' then '&gt;'
      when '&' then '&amp;'
      else token
      end
    end
  end

  def advance
    @current_token_index += 1
  end

  def current_token
    tokens[current_token_index]
  end

  def next_token
    tokens[current_token_index + 1]
  end

  def delimiter_regexp
    delimiters = ['\s', '(".*")'] +
      TOKEN_TYPES.map { |type| "(#{type})" } +
      SYMBOLS.map { |symbol|  "(\\#{symbol})" }

    Regexp.new(delimiters.join('|'))
  end

  private

  attr_reader :input_file, :current_token_index, :tokens
end
