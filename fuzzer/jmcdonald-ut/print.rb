# Used by the fuzzer to generate both a valid musl-gcc printf statement and
# normal gcc printf statement
#
#
# i/d - signed decimal integer
# u - unsigned decimal integer
# o - octal
# x - hex integer
# X - hex integer (upper case)
# f - floating point lowercase
# e - sci notation lowercase
# E - sci notation uppercase
# g - use the shortest representation (e or f)
# c - character
# s - string
# p - pointer address
# n - nothing printed
class Print
  @@types = [
    :i, :d, :u, :o, :x, :X, :f, 
    :e, :E, :g, :c, :s
  ]

  @@o = [('a'..'z'), ('A'..'Z')].map { |i| i.to_a }.flatten
  @@u = (0..10).to_a
  @@i = (-5..5).to_a
  @@c = ('a'..'z').to_a
  @@f = [1.5, 0.3, -1.2, -32.4E+38, 3.4E+38, 2.2, 2.99953, -0.1]

  # Generates a random print object
  def self.rand
    Print.new(@@types.choice)
  end

  # Initialize an instance of the print object 
  def initialize type = :i
    raise Exception unless @@types.include? type

    @type = type
    @value = gen_value
  end

  def gen_value
    case @type
    when :i then return i
    when :d then return i
    when :u then return u
    when :o then return o
    when :x then return x
    when :X then return x
    when :f then return f
    when :e then return e
    when :E then return e
    when :g then return g
    when :c then return c
    when :s then return s
    end
  end

  def musl_printf
    "\t\tmusl_snprintf (buf, LEN, \"%#{@type.to_s}\", #{@value});\n\t\tprintf(\"%s\", buf);\n"
  end

  def printf
    "\t\tprintf(\"%#{@type.to_s}\", #{@value});\n"
  end

  private

  def i
    @@i.choice
  end

  def u
    @@u.choice
  end

  def o
    i.to_s.to_i(8)
  end

  def x
    i.to_s.to_i(16)
  end

  def f
    @@f.choice
  end

  def e
    f.to_s
  end

  def g
    f.to_s
  end

  def c
    return "'#{@@c.choice}'"
  end

  def s
    # Courtesy of stack overflow
    string = (0...50).map { @@o[rand(@@o.length)] }.join
    return "\"#{string}\""
  end
end