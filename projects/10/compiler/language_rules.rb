module LanguageRules
  TOKEN_TYPES = [:keyword, :symbol, :identifier, :int_const, :string_const].freeze

  SYMBOLS = %w({ } ( ) [ ] . , ; + - * / & | < > = -).freeze

  KEYWORDS = %w(
    class constructor function method field static var int char
    boolean void true false null this let do if else while return
  ).freeze
end
