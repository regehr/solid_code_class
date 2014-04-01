# App

The main script for "musl-printf-fuzzer".

## Requires

    async = require 'async'
    exec = require('child_process').exec
    fs = require 'fs'
    tmp = require 'tmp'

## Configuration

    cc = 'gcc'
    cflags = '-coverage'
    times = 1024
    callsPerFile = 1024
    bufferSize = 1024
    maxPadding = 64

### Probabilities

The chance we're done generating the format string.

    breakChance = .05

The chance that we insert a format string instead of a displayable character.

    formatStringChance = .2

The chance that a flag is present in a format string.

    flagChance = .1

The chance that a width is specified.

    widthChance = .1

The chance that a precision is specified.

    precisionChance = .1

The chance that an `*` will be used instead of a number for width and precision.

    starChance = .2

### Types

    types =
      'int':
        min: -(2 ** 31)
        max: 2 ** 31 - 1
      'signed char':
        min: -(2 ** 7)
        max: 2 ** 7 - 1
      'short int':
        min: -(2 ** 15)
        max: 2 ** 15 - 1
      'long int':
        min: -(2 ** 31)
        max: 2 ** 31 - 1
      'long long int':
        min: -(2 ** 63)
        max: 2 ** 63 - 1
      'intmax_t':
        min: -(2 ** 31)
        max: 2 ** 31 - 1

### Displayable Characters

An array of escaped, single-character, string literals.

    displayable = [
      ' ',   '!',   '\\"', '#',   '$',   '&',   '\'',  '(',   ')',   '*',   '+'
      ',',   '-',   '.',   '/',   '0',   '1',   '2',   '3',   '4',   '5',   '6'
      '7',   '8',   '9',   ':',   ';',   '<',   '=',   '>',   '?',   '@',   'A'
      'B',   'C',   'D',   'E',   'F',   'G',   'H',   'I',   'J',   'K',   'L'
      'M',   'N',   'O',   'P',   'Q',   'R',   'S',   'T',   'U',   'V',   'W'
      'X',   'Y',   'Z',   '[',   '\\\\',']',   '^',   '_',   '`',   'a',   'b'
      'c',   'd',   'e',   'f',   'g',   'h',   'i',   'j',   'k',   'l',   'm'
      'n',   'o',   'p',   'q',   'r',   's',   't',   'u',   'v',   'w',   'x'
      'y',   'z',   '{',   '|',   '}',   '~'
    ]

### Format Specifiers

    formatSpecifiers = [
      {
        specifiers: ['d', 'i']
        flags: ['-', '+', ' ', '0']
        width: true
        precision: true
        lengths: [
          {string: '', type: 'int'}
          {string: 'hh', type: 'signed char'}
          {string: 'h', type: 'short int'}
          {string: 'l', type: 'long int'}
          {string: 'll', type: 'long long int'}
    #      {string: 'j', type: 'intmax_t'}
    #      {string: 'z', type: 'size_t'}
    #      {string: 't', type: 'ptrdiff_t'}
        ]
      }
    ]

### `tmp` Cleanup Setting

Clean up temporary files even when an uncaught exception occurs.

    tmp.setGracefulCleanup()

## Helper Functions

### `randomInRange()`

Returns a random number in the range [`min`, `max`).

    randomInRange = (min, max) -> Math.floor(Math.random() * (max - min)) + min

### `randomElement()`

Returns a random element from `array`.

    randomElement = (array) -> array[randomInRange(0, array.length)]

### `pad()

    pad = (n, width) ->
      n = String n
      if n.length >= width
        n
      else
        new Array(width - n.length + 1).join('0') + n

## Main Script

### State

The small amount of state necessary to display which "try" the app is executing
and how many tries have resulted in errors.

    errors = 0

### The Loop

    async.timesSeries(
      times
      (n, callback) ->
        console.log "Try: #{n} Errors: #{errors}"
        async.auto(
          {
            cTmpFile: (callback) -> tmp.tmpName(
              prefix: pad(n, 4), postfix: '.c'
              callback
            )

            writer: ['cTmpFile', (callback, results) ->
              callback null, fs.createWriteStream(results.cTmpFile)
            ]

            writeHeader: ['writer', (callback, results) ->
              results.writer.write(
                """
                #include <stdio.h>
                #include "#{process.cwd()}/../musl-printf-standalone/musl.h"

                int main() {
                  char musl[#{bufferSize}];
                  char gnu[#{bufferSize}];

                """
                callback
              )
            ]

            printfCalls: (callback) ->
              vars = 0
              callback null, (for i in [0...callsPerFile]
                declarations = []
                args = []
                args[0] = []
                loop
                  addDeclaration = (type, value) ->
                    declarations.push "  #{type} var#{vars} = #{value};"
                    args.push "var#{vars}"
                    vars += 1

                  numberOrStar = ->
                    if Math.random() < starChance
                      args[0].push '*'
                      addDeclaration 'int', randomInRange(0, maxPadding)
                    else
                      args[0].push "#{randomInRange 0, maxPadding}"

                  if Math.random() < breakChance then break

                  unless Math.random() < formatStringChance
                    args[0].push randomElement(displayable)
                    continue

                  args[0].push '%'
                  formatSpecifier = randomElement formatSpecifiers

                  for flag in formatSpecifier.flags
                    if Math.random() < flagChance
                      args[0].push flag

                  if formatSpecifier.width
                    if Math.random() < widthChance
                      numberOrStar()

                  if formatSpecifier.precision
                    if Math.random() < precisionChance
                      args[0].push '.'
                      numberOrStar()

                  length = randomElement formatSpecifier.lengths
                  args[0].push length.string
                  addDeclaration length.type,
                    randomInRange types[length.type].min, types[length.type].max

                  args[0].push randomElement(formatSpecifier.specifiers)

                args[0] = "\"#{args[0].join ''}\\n\""
                """
                  // #{i}
                #{declarations.join '\n'}
                  musl_snprintf(musl, #{bufferSize}, #{args.join ', '});
                  snprintf(gnu, #{bufferSize}, #{args.join ', '});
                  if (strcmp(musl, gnu) != 0) printf("Call #{i} failed!");

                """
              )


            writeBody: ['writeHeader', 'printfCalls', (callback, results) ->
              for call, i in results.printfCalls
                results.writer.write call, callback
            ]

            writeFooter: ['writeBody', (callback, results) ->
              results.writer.end(
                """
                  return 0;
                }

                """
                callback
              )
            ]

            outFile: (callback) -> tmp.tmpName(
              prefix: pad(n, 4), postfix: '.out'
              callback
            )

            compile: ['writeFooter', 'outFile', (callback, results) ->
              exec(
                "#{cc} #{cflags} -o #{results.outFile} #{results.cTmpFile}
                  ../musl-printf-standalone/fwrite.o
                  ../musl-printf-standalone/snprintf.o
                  ../musl-printf-standalone/vfprintf.o
                  ../musl-printf-standalone/vsnprintf.o"
                callback
              )
            ]

            exec: ['compile', (callback, results) ->
              exec "#{results.outFile}", callback
            ]
          }
          (err, results) ->
            if err? then callback err

            if results.exec[0] isnt ''
              console.log "Saving error as error#{errors}.c"
              fs.createReadStream(results.cTmpFile)
              .pipe fs.createWriteStream("error#{errors}.c")
              errors += 1

            fs.unlink results.cTmpFile
            fs.unlink results.outFile

            callback()
        )
      (err) -> if err? then throw err
      )
