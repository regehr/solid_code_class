# Jonathon McDonald
class Fuzzer
  def self.diff f1, f2
    `diff <(echo "#{f1.output}") <(echo "#{f2.output}"))`
  end

  def initialize name, type = :musl
    @name = name
    @type = :musl

    build_template
  end

  def output
    write_line 'printf("Hello fuzzer!\\n");'

    build_c_file
    out = run_fuzzer
    clean_up

    out
  end

  private

  def build_template
    file = File.new("template.c")
    @template = file.read
    file.close
  end

  def build_c_file
    @template.gsub!('{CODE}', @code)

    out = File.new(@name, "w")
    out.write(@template)
    out.close
  end

  def clean_up
    File.delete('a.out')
    File.delete(@name)
  end

  def write_line string
    @code = "" if @code.nil?

    @code += "#{string} "
  end

  def run_fuzzer
    gcc = 'gcc'
    gcc = 'musl-gcc' if @type == :musl
    `#{gcc} -static #{@name}`
    return `./a.out`
  end
end

f1 = Fuzzer.new('gcc.c', :gcc)
f2 = Fuzzer.new('musl-gcc.c')

Fuzzer.diff(f1, f2)