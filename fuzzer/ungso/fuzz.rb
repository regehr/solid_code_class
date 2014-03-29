# Chad Miller March 2014
# gcc has form
# int vfprintf(FILE *stream, const char *format, va_list arg)
# musl has form
# int musl_vfprintf(MUSL_FILE *restrict f, const char *restrict fmt, va_list ap)
# grammar has format: %[flags][width][.precision][length]specifier 
require 'securerandom'

class TestPrintf 

  def initialize
    @includes
    @main
    @main_code
    @code
    @type = ""
    @fmt = ""
    @args = ""
    @snprintf 
    @stream = ""
    @specifier = {'c'=>'c','d'=>'d','e'=>'e','E'=>'E',
      'f'=>'f','g'=>'g','G'=>'G','o'=>'o','s'=>'s',
      'u'=>'u', 'x'=>'x','p'=>'p','n'=>'n'}
    @flags = {'-'=>'-','+'=>'+','#'=>'#','0'=>'0'}
    @w #number
    @width = {"w"=>"#{@w}",'arg'=>'*'}
    @p #number
    @precision = {'p'=>".#{@p}", 'arg'=>'.*'}
    @length = {'h'=>'h','l'=>'l','L'=>'L'}
    @test_musl = ""
    @test_gcc = ""
    @gcc_warnings
  end

  # Run it and test it
  def run_fuzz

    write_fuzz
    mk_muslf
    mk_gccf
    test_it

  end

  # Write the actual fuzzer
  def write_fuzz
    write_musl
  end

  # Makes a musl test file
  def mk_muslf
    @includes = "#include <stdio.h>\n#include <stdarg.h>\n#include \"musl.h\"\n"\
    "#define BUFF_SIZE 100\n\n"
    @type = "musl_"
    @main_code = " char buff[BUFF_SIZE];\n  #{@test_musl}\n  fputs(buff, stdout);\n  return 0;"
    @main = "\nint main(){\n\n #{@main_code}\n}\n"
    file = File.open("test-musl.c", 'w') 
    @code = @includes+@main
    file.write(@code) 
    file.close
  end

  # Makes a gcc test file (for differential testing)
  def mk_gccf
    @includes = "#include <stdio.h>\n#include <stdarg.h>\n#define BUFF_SIZE 100\n"
    @type = ""
    @main_code = " char buff[BUFF_SIZE];\n"\
                 "  #{@test_gcc}\n  fputs(buff, stdout);\n  return 0;"
    @main = "\nint main(){\n\n #{@main_code}\n}\n"
    @code = @includes+@main
    file = File.open("test-gcc.c", 'w') 
    file.write(@code) 
    file.close
  end

  # Differential testing
  def test_it
    compile_and_exec
  end

  # Compile the two files, exec and compare them
  def compile_and_exec
    @gcc_warnings = %x[gcc -g -o gcc_exec test-gcc.c]
    %x[gcc -g -ftest-coverage -fprofile-arcs -o musl_exec\
            test-musl.c snprintf.c vsnprintf.c vfprintf.c fwrite.c]
    file = File.open("warnings.txt", 'w') 
    file.write(@gcc_warnings) 
    file.close
    s1 = %x[./gcc_exec]
    s2 = %x[./musl_exec]
    puts s1 == s2
  end


  # Write musl fuzzer
  def write_musl
    #%[flags][width][.precision][length]specifier
    specifier_walk
  end

  # Walk-through each specifier
  def specifier_walk

    @specifier.each do |key, value|
      self.send(value+"_func")
    end
 end
 
  def c_func

    flags = {'-'=>'-','nil'=>''}
    lengths = {'l'=>'l', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000000)
      @fmt = "\"%#{flag}#{width}#{@precision['']}#{length}#{@specifier['c']}\""
      args = SecureRandom.random_number(1000)
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf
    end

  end


  def d_func

    flags = {'-'=>'-','+'=>'+', '0'=>'0','nil'=>''}
    lengths = {'l'=>'l', 'h'=>'h', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      args = SecureRandom.random_number(1000)
      if length == 'l'
        args = args.to_s+"L"
      end
      width = SecureRandom.random_number(1000000)
      @fmt = "\"%#{flag}#{width}#{@precision['']}#{length}#{@specifier['d']}\""
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf

    end
      
  end


  def e_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>''}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      args = SecureRandom.random_number
      width = SecureRandom.random_number(1000)
      precision = "."+SecureRandom.random_number(1000).to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      @fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['e']}\""
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf
    end
  end

  def E_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>''}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      args = SecureRandom.random_number
      width = SecureRandom.random_number(1000)
      precision = "."+SecureRandom.random_number(1000).to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      @fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['E']}\""
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf
   
    end
  end


  def f_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>''}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      args = SecureRandom.random_number
      width = SecureRandom.random_number(1000)
      precision = "."+SecureRandom.random_number(1000).to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      @fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['f']}\""
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf
   
    end
  end

  def g_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>''}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      args = SecureRandom.random_number
      width = SecureRandom.random_number(1000)
      precision = "."+SecureRandom.random_number(1000).to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      @fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['g']}\""
      @type = "musl_"
      @snprintf = "snprintf(buff, BUFF_SIZE, #{@fmt},#{args});\n"
      @test_musl += "musl_"+@snprintf
      @test_gcc += @snprintf
   
   end
  end

  def G_func


  end

  def o_func


  end

  def s_func


  end

  def u_func


  end

  def x_func


  end

  def p_func


  end

  def n_func


  end


  def rand_flag
    return @flags[@flags.keys.sample]
  end

  def rand_length
    return @length[@length.keys.sample]
  end

  # Set the width
  def set_width(x)
    @width['w'] = x
  end
  
  # Set the precision
  def set_prec(x)
    @precision['p'] = "."+x.to_s
  end


end


tpf = TestPrintf.new
tpf.run_fuzz
#tpf.write_musl
