class SymbolTable
  def initialize
    @class_scope = []
    @subroutine_scope = []
  end

  def start_subroutine
    @subroutine_scope = []
  end

  def define(name, type, kind)
    scope(kind) << {
      name: name,
      type: type,
      kind: kind,
      segment: segment(kind),
      index: count(kind)
    }
  end

  def scope(kind)
    return @class_scope if ['static', 'field'].include?(kind)

    @subroutine_scope
  end

  def count(kind)
    scope(kind).count { |symbol| symbol[:kind] == kind }
  end

  def segment(kind)
    puts "SEGMENT for #{kind} "
    case kind
    when 'argument' then 'argument'
    when 'field'    then 'this'
    when 'var'      then 'local'
    when 'static'   then 'static'
    end
  end

  def find(name)
    @subroutine_scope.select { |symbol| symbol[:name] == name}.first ||
    @class_scope.select { |symbol| symbol[:name] == name}.first
  end
end
