class Token
  TOKEN_TYPES = [:keyword, :symbol, :identifier, :int_const, :string_const].freeze
  SYMBOLS = %w({ } ( ) [ ] . , ; + - * / & | < > = -).freeze
  KEYWORDS = %w(
    class constructor function method field static var int char
    boolean void true false null this let do if else while return
  ).freeze

  def self.split_regexp
    delimiters = ['\s', '(".*")'] +
      TOKEN_TYPES.map { |type| "(#{type})" } +
      KEYWORDS.map { |keyword| "(#{keyword})" } +
      SYMBOLS.map { |symbol|  "(\\#{symbol})" }

    Regexp.new(delimiters.join('|'))
  end
end

input = File.read(ARGV[0]).gsub(/\/\*.*\*\/|\/\/.*$|^\s*|\s*$/, '')
puts input.split(Token.split_regexp).reject(&:empty?)
