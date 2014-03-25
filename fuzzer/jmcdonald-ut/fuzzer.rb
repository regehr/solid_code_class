# Jonathon McDonald
class Fuzzer
  def self.run
    fuzzer = Fuzzer.new
  end

  def initialize
    build_template
    write_line 'printf("Hello fuzzer!\\n");'
    build_c_file
    run_fuzzer
    clean_up
  end

  def build_template
    template = File.new("template.c")
    @template = template.read
    template.close
  end

  def build_c_file
    @template.gsub!('{CODE}', @code)

    out = File.new("main.c", "w")
    out.write(@template)
    out.close
  end

  def clean_up
    File.delete('a.out')
    File.delete('main.c')
  end

  def write_line string
    @code = "" if @code.nil?

    @code += "#{string} "
  end

  def run_fuzzer
    `musl-gcc -static main.c`
    puts `./a.out`
  end
end

Fuzzer.run