 # Chad Miller March 2014
# gcc has form
# int vfprintf(FILE *stream, const char *format, va_list arg)
# musl has form
# int musl_vfprintf(MUSL_FILE *restrict f, const char *restrict fmt, va_list ap)
# grammar has format: %[flags][width][.precision][length]specifier 
require 'securerandom'

class TestPrintf 

  def initialize

    @args = ""
    @snprintf 
    @stream = ""
    @specifier = {'c'=>'c','d'=>'d','e'=>'e','E'=>'E',
      'f'=>'f','g'=>'g','G'=>'G','o'=>'o','s'=>'s',
      'u'=>'u', 'x'=>'x','p'=>'p','n'=>'n'}
    @flags = {'-'=>'-','+'=>'+','#'=>'#','0'=>'0'}
    @precision = {'p'=>'.', 'arg'=>'.*', 'nil'=>''}
    @length = {'h'=>'h','l'=>'l','L'=>'L'}
    @flag
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
    includes = "#include <stdio.h>\n#include <stdarg.h>\n#include <wchar.h>\n#include \"musl.h\"\n"\
    "#define BUFF_SIZE 100\n\n"
    main_code = " char buff[BUFF_SIZE];\n  #{@test_musl}\n  fputs(buff, stdout);\n  return 0;"
    main = "\nint main(){\n\n #{main_code}\n}\n"
    file = File.open("test-musl.c", 'w') 
    code = includes+main
    file.write(code) 
    file.close
  end

  # Makes a gcc test file (for differential testing)
  def mk_gccf
    includes = "#include <stdio.h>\n#include <stdarg.h>\n#include <wchar.h>\n#define BUFF_SIZE 100\n"
    main_code = " char buff[BUFF_SIZE];\n"\
                 "  #{@test_gcc}\n  fputs(buff, stdout);\n  return 0;"
    main = "\nint main(){\n\n #{main_code}\n}\n"
    code = includes+main
    file = File.open("test-gcc.c", 'w') 
    file.write(code) 
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
      fmt = "\"%#{flag}#{width}#{@precision['']}#{length}#{@specifier['c']}\""
      args = SecureRandom.random_number(1000)
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end


  def d_func

    flags = {'-'=>'-','+'=>'+', '0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'l'=>'l', 'h'=>'h', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
        flag = set_nonzero_flag()
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
        flag = set_nonzero_flag()
      end
      args = args.to_s + SecureRandom.random_number(1000).to_s
      if length == 'l'
        args = args+"L"
      end
      width = SecureRandom.random_number(1000000)
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['d']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end      
  end


  def e_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      args = args.to_s + SecureRandom.random_number().to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['e']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end

  def E_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      args = args.to_s + SecureRandom.random_number().to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['E']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
   
    end
  end


  def f_func


    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      args = args.to_s + SecureRandom.random_number().to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['f']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
   
    end
  end

  def g_func


    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      args = args.to_s + SecureRandom.random_number().to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['g']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
   
   end
  end

  def G_func

    flags = {'-'=>'-','+'=>'+', '#'=>'#','0'=>'0','nil'=>'', 'space'=>' '}
    lengths = {'L'=>'L', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)     
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      args = args.to_s + SecureRandom.random_number().to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['G']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
   
    end
  end

  def o_func

    flags = {'-'=>'-', '#'=>'#','0'=>'0','nil'=>''}
    lengths = {'l'=>'l', 'h'=>'h', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)     
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
        flag = ["-", "", "#"].sample 
     elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
        flag = ["-", "", "#"].sample 
      end
      args = args.to_s + SecureRandom.random_number(1000).to_s
      if length == 'l' or length == 'L'
        args = args.to_s+"L"
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['o']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end
 
  def s_func

    flags = {'-'=>'-', 'nil'=>''}
    lengths = {'l'=>'l', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)     
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
      end
      arg1 = SecureRandom.random_number(1000).to_s  
      arg_s = "\"#{arg1}\""   
      if length == 'l'
        arg_s = "(wchar_t *)"+arg_s
      end
      args = args.to_s + arg_s
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['s']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end

  def u_func

    flags = {'-'=>'-','0'=>'0','nil'=>''}
    lengths = {'l'=>'l', 'h'=>'h', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
        flag = ["-", ""].sample
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
        flag = ["-", ""].sample
      end
      args = args.to_s + SecureRandom.random_number(1000).to_s
      if length == 'l'
        args = args+"L"
      end
      width = SecureRandom.random_number(1000000)
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['u']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end      
  end

  def x_func

    flags = {'-'=>'-','0'=>'0','nil'=>''}
    lengths = {'l'=>'l', 'h'=>'h', 'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      precision = @precision[@precision.keys.sample]    
      if precision == '.*'
        args = SecureRandom.random_number(1000).to_s+","
        flag = ["-", ""].sample
      elsif precision == '.'
        precision = "."+SecureRandom.random_number(1000).to_s
        flag = ["-", ""].sample
      end
      args = args.to_s + SecureRandom.random_number(1000).to_s
      if length == 'l'
        args = args+"L"
      end
      width = SecureRandom.random_number(1000000)
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['x']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end      
  end

  def p_func

    flags = {'-'=>'-', 'nil'=>''}
    lengths = {'nil'=>''}
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      flag = flags[flags.keys.sample]
      width = SecureRandom.random_number(1000)     
      precision = ''
      arg1 = SecureRandom.random_number(1000).to_s  
      arg_s = "\"#{arg1}\""   
      if length == 'l'
        arg_s = "(void *)"+arg_s
      end
      args = args.to_s + arg_s
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['p']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end

  def n_func

    flags = {'nil'=>''}
    lengths = {'l'=>'l', 'h'=>'h','nil'=>''}
    @test_gcc += "  int n;\n"
    @test_musl += "  int n;\n"
    (1..100).each do |i|
      length = lengths[lengths.keys.sample]
      #length = ''
      flag = flags[flags.keys.sample]
      width = ''
      precision = ''
      args = 'n'
      if length == 'l'
        args = "(long int*)&"+args.to_s
      elsif length == 'h'
        args = "(short int *)&"+args.to_s
      else
        args = "&"+args.to_s
      end
      fmt = "\"%#{flag}#{width}#{precision}#{length}#{@specifier['n']}\""
      @snprintf = "snprintf(buff, BUFF_SIZE, #{fmt},#{args});\n"
      @test_musl += "  musl_"+@snprintf
      @test_gcc += "  "+@snprintf
    end
  end


  def rand_flag
    return @flags[@flags.keys.sample]
  end

  def rand_length
    return @length[@length.keys.sample]
  end

  # Set the precision
  def set_nonzero_flag()
    flags = {'-'=>'-','+'=>'+','nil'=>'', 'space'=>' '}
    return flags[flags.keys.sample]
  end


end


tpf = TestPrintf.new
tpf.run_fuzz
#tpf.write_musl
