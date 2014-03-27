# App

The main script for "musl-printf-fuzzer".

    async = require 'async'
    exec = require('child_process').exec
    fs = require 'fs'
    tmp = require 'tmp'

    muslGcc = '/usr/local/musl/bin/musl-gcc'
    gnuGcc = 'gcc'
    callsPerFile = 1

    breakChance = .05
    formatStringChance = .2
    flagChance = .1
    widthChance = .1
    precisionChance = .1
    starChance = .2
    maxPadding = 64

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

    displayable = [
      ' ',   '!',   '\\"', '#',   '$',   '&',   '\'',  '(',   ')',   '*'
      '+',   ',',   '-',   '.',   '/',   '0',   '1',   '2',   '3',   '4'
      '5',   '6',   '7',   '8',   '9',   ':',   ';',   '<',   '=',   '>'
      '?',   '@',   'A',   'B',   'C',   'D',   'E',   'F',   'G',   'H'
      'I',   'J',   'K',   'L',   'M',   'N',   'O',   'P',   'Q',   'R'
      'S',   'T',   'U',   'V',   'W',   'X',   'Y',   'Z',   '[',   '\\\\'
      ']',   '^',   '_',   '`',   'a',   'b',   'c',   'd',   'e',   'f'
      'g',   'h',   'i',   'j',   'k',   'l',   'm',   'n',   'o',   'p'
      'q',   'r',   's',   't',   'u',   'v',   'w',   'x',   'y',   'z'
      '{',   '|',   '}',   '~'
    ]

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

Clean up temporary files even when an uncaught exception occurs.

    tmp.setGracefulCleanup()

    randomInRange = (min, max) -> Math.floor(Math.random() * (max - min)) + min
    randomElement = (array) -> array[randomInRange(0, array.length)]

    tries = 0
    errors = 0

    async.forever(
      (callback) ->
        console.log "Try: #{tries} Errors: #{errors}"
        tries += 1
        async.auto(
          {
            cTmpFile: (callback) -> tmp.tmpName postfix: '.c', callback

            writer: ['cTmpFile', (callback, results) ->
              callback null, fs.createWriteStream(results.cTmpFile)
            ]

            writeHeader: ['writer', (callback, results) ->
              results.writer.write(
                """
                #include <stdio.h>

                int main() {

                """
                callback
              )
            ]

            printfCalls: (callback) ->
              vars = 0
              callback null, (for _ in [0...callsPerFile]
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
                #{declarations.join '\n'}
                  printf(#{args.join ', '});

                """
              )


            writeBody: ['writeHeader', 'printfCalls', (callback, results) ->
              for call, i in results.printfCalls
                results.writer.write(
                  """
                    // #{i}
                  #{call}
                  """
                  callback
                )
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

            muslOutFile: (callback) -> tmp.tmpName postfix: '.out', callback

            compileMusl: ['writeFooter', 'muslOutFile', (callback, results) ->
              exec(
                "#{muslGcc} -o #{results.muslOutFile} #{results.cTmpFile}"
                callback
              )
            ]

            muslStdoutFile: (callback) -> tmp.tmpName callback

            execMusl: ['compileMusl', 'muslStdoutFile', (callback, results) ->
              stdoutFile = fs.createWriteStream results.muslStdoutFile
              child = exec "#{results.muslOutFile}", callback
              child.stdout.pipe stdoutFile
            ]

            gnuOutFile: (callback) -> tmp.tmpName postfix: '.out', callback

            compileGnu: ['writeFooter', 'gnuOutFile', (callback, results) ->
              exec(
                "#{gnuGcc} -o #{results.gnuOutFile} #{results.cTmpFile}"
                callback
              )
            ]

            gnuStdoutFile: (callback) -> tmp.tmpName callback

            execGnu: ['compileGnu', 'gnuStdoutFile', (callback, results) ->
              stdoutFile = fs.createWriteStream results.gnuStdoutFile
              child = exec "#{results.gnuOutFile}", callback
              child.stdout.pipe stdoutFile
            ]

            diffOutputs: ['execMusl', 'execGnu', (callback, results) ->
              exec "diff #{results.muslStdoutFile} #{results.gnuStdoutFile}",
                callback
            ]
          }
          (err, results) ->
            if err? then callback err

            if results.diffOutputs[0] isnt ''
              console.log "Saving error as error#{errors}.c"
              fs.createReadStream(results.cTmpFile)
              .pipe fs.createWriteStream("error#{errors}.c")
              errors += 1

            fs.unlink results.cTmpFile
            fs.unlink results.muslOutFile
            fs.unlink results.gnuOutFile
            fs.unlink results.muslStdoutFile
            fs.unlink results.gnuStdoutFile

            callback()
        )
      (err) -> throw err if err?
    )
