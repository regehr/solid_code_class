fs = require 'fs'
async = require 'async'
exec = require 'child_process'

musl = ''
gcc = '/bin/gcc'
include = '#include <stdio.h>'
body = 'helloworld'

file =
"""
#{include}

int main (){
  printf("#{body}");
}
"""

console.log file