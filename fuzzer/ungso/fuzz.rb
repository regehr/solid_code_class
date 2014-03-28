# Chad Miller
# gcc has form
# int vfprintf(FILE *stream, const char *format, va_list arg)
# musl has form
# int musl_vfprintf(MUSL_FILE *restrict f, const char *restrict fmt, va_list ap)
# grammar has format: %[flags][width][.precision][length]specifier 
class TestPrintf 


  def intialize
    @includes
    @func
    @func_code
    @main
    @main_code
    @code
    @vfprintf = "writef(#{@file},#{@fmt},#{@args})"
    @file
    @fmt
    @args
    @stream
    @specifier = {'c'=>'c','d'=>'d','e'=>'e','E'=>'E',
      'f'=>'f','g'=>'g','G'=>'G','o'=>'o','s'=>'s',
      'u'=>'u', 'x'=>'x','p'=>'p','n'=>'n'}
    @flags = {'-'=>'-','+'=>'+','#'=>'#','0'=>'0'}
    @width = {'w'=>"#{w}",'arg'=>'*'}
    @w #number
    @precision = {'p'=>".#{p}", 'arg'=>'.*'}
    @p #number
    leng = {'h'=>'h','l'=>'l','L'=>'L'}
    @code_musl = ""
    @code_gcc = ""
  end

  def run_fuzz

    write_fuzz
    mk_muslf
    mk_gccf
    test_it

  end


  def write_fuzz
    write_musl
    write_gcc
  end

  # Makes a musl test file
  def mk_muslf
    @includes = "#include <stdio.h>\n#include <stdarg.h>\n#include \"musl.h\"\n\n"
    @func_code = "va_list args;\n  va_start(args, format);\n  "\
                  "musl_vfprintf(f, format, args);\n  va_end(args);\n"  
    @func = "void write_f(MUSL_FILE * restrict f, const char * format, ...){\n  "\
                 "#{@func_code}}\n"
    @file = "f"
    @main_code = "MUSL_FILE *restrict f;\n  #{@vfprintf}\n return 0;"
    @main = "\nint main(){\n\n #{@main_code}\n}\n"
    file = File.open("test-musl.c", 'w') 
    @code = @includes+@func+@main
    file.write(@code) 
    file.close
  end

  # Makes a gcc test file
  def mk_gccf
    @includes = "#include <stdio.h>\n#include <stdarg.h>\n\n"
    @func_code = "va_list args;\n  va_start(args, format);\n  "\
                  "vfprintf(f, format, args);\n  va_end(args);\n"  
    @func = "void write_f(FILE * f, const char * format, ...){\n  "\
                 "#{@func_code}}\n"
  
    @main_code = " FILE *f;\n  f = fopen(\"gcc.txt\", \"w\");\n"\
                 "#{@vfprintf}\n  fclose(f);\n  return 0;"
    @main = "\nint main(){\n\n #{@main_code}\n}\n"
    @code = @includes+@func+@main
    file = File.open("test-gcc.c", 'w') 
    file.write(@code) 
    file.close
  end


  def test_it
    compile_and_exec
    %x(diff musl.txt gcc.txt) # diff rslt
  end

  def compile_and_exec
    system("gcc -g -o gcc_exec test-gcc.c")
    system("gcc -g -ftest-coverage -fprofile-arcs -o musl_exec test-musl.c vfprintf.c fwrite.c")
    system("./gcc_exec")
    system("./musl_exec")  
  end


  def write_musl
    

  end


  def write_gcc
    


  end

end


tpf = TestPrintf.new
tpf.run_fuzz
