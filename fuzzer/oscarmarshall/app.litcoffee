# App

The main script for "musl-printf-fuzzer".

    async = require 'async'
    exec = require('child_process').exec
    fs = require 'fs'
    tmp = require 'tmp'

    muslGcc = '/usr/local/musl/bin/musl-gcc'
    gnuGcc = 'gcc'
    callsPerFile = 1024
    breakChance = .05


Clean up temporary files even when an uncaught exception occurs.

    tmp.setGracefulCleanup()

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

            printfArgs: (callback) ->
              callback null, (for _ in [0...callsPerFile]
                result = []
                result[0] = ''
                loop
                  if Math.random() < breakChance
                    break
                  result[0] += 'a'
                result[0] = "\"#{result[0]}\\n\""
                result
              )


            writeBody: ['writeHeader', 'printfArgs', (callback, results) ->
              for args in results.printfArgs
                results.writer.write(
                  """
                    printf(#{args.join ', '});

                  """
                  callback
                )
            ]

            writeFooter: ['writeBody', (callback, results) ->
              results.writer.end(
                """
                  exit(0);
                }

                """
                callback
              )
            ]

            muslTmpFile: (callback) ->
              tmp.tmpName postfix: '.out', callback

            compileMusl: ['writeFooter', (callback, results) ->
              exec(
                "#{muslGcc} -o '#{results.muslTmpFile}' '#{results.cTmpFile}'"
                callback
              )
            ]

            execMusl: ['compileMusl', (callback, results) ->
              exec "#{results.muslTmpFile}", callback
            ]

            gnuTmpFile: (callback) ->
              tmp.tmpName postfix: '.out', callback

            compileGnu: ['writeFooter', (callback, results) ->
              exec(
                "#{gnuGcc} -o '#{results.gnuTmpFile}' '#{results.cTmpFile}'"
                callback
              )
            ]

            execGnu: ['compileGnu', (callback, results) ->
              exec "#{results.gnuTmpFile}", callback
            ]

            compareOutput: ['execMusl', 'execGnu', (callback, results) ->
              if results.execMusl[0] is results.execGnu[0]
                console.log "Saving error as error#{errors}.c"
                fs.createReadStream(results.cTmpFile)
                .pipe fs.createWriteStream("error#{errors}.c")
                errors += 1
              callback()
            ]
          }
          callback
        )
      (err) -> throw err if err?
    )

