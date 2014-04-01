# Jonathon McDonald
require File.join(File.dirname(__FILE__), 'print')

class Fuzzer
  def initialize
    build_template
  end

  def write_out
    musl = ""
    gcc = ""

    (1..50).each do |i|
      printGen = Print.rand
      musl += printGen.musl_printf
      gcc += printGen.printf
    end

    musl = @template.gsub('{CODE}', musl)
    gcc = @template.gsub('{CODE}', gcc)

    musl_file = File.new('musl.c', 'w')
    musl_file.write(musl)
    musl_file.close

    gcc_file = File.new('gcc.c', 'w')
    gcc_file.write(gcc)
    gcc_file.close
  end

  private

  def build_template
    file = File.new("template.c")
    @template = file.read
    file.close
  end
end

f1 = Fuzzer.new
f1.write_out
