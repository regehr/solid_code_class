# Jonathon McDonald
class Fuzzer
  def self.diff f1, f2
    output1 = "#{f1.output}"
    output2 = "#{f2.output}"

    build_diff_file("output1", output1)
    build_diff_file("output2", output2)

    out = `diff output1 output2`

    File.delete("output1")
    File.delete("output2")

    puts out unless out.empty?
  end

  def initialize name, type = :musl
    @name = name
    @out_name = @name.gsub('.c', '')
    @type = type

    build_template
  end

  def output
    (1..1000).each do |i|
      write_line "printf(\"Printing number %i\\n\", #{i});"
    end

    build_c_file
    out = run_fuzzer
    clean_up

    out
  end

  private

  def self.build_diff_file name, text
    file = File.new(name, "w")

    file.write(text)

    file.close
  end

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
    File.delete(@out_name)
    File.delete(@name)
  end

  def write_line string
    @code = "" if @code.nil?

    @code += "#{string} "
  end

  def run_fuzzer
    gcc = 'gcc'
    gcc = 'musl-gcc' if @type == :musl
    `#{gcc} -static #{@name} -o #{@out_name}`
    return `./#{@out_name}`
  end
end

f1 = Fuzzer.new('gcc.c', :gcc)
f2 = Fuzzer.new('musl-gcc.c')

Fuzzer.diff(f1, f2)
