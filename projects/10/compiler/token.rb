require_relative './language_rules.rb'

class Token
  include LanguageRules

  attr_reader :value

  def initialize(value)
    @value = value
  end

  def type
    return :keyword if KEYWORDS.include?(value)
    return :symbol if SYMBOLS.include?(value)
    return :integerConstant if valid_int_const?
    return :stringConstant if valid_string_const?
    return :identifier if valid_identifier?
  end

  def valid_int_const?
    value.match(/^\d+$/) && (0..32767).cover?(value.to_i)
  end

  def valid_string_const?
    value.match(/^"[^"]+"$/)
  end

  def valid_identifier?
    value.match(/^[^\d]+.*$/)
  end
end
