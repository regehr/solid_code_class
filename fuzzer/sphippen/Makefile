.PHONY: fuzz clean

fuzz:
	./fuzz.rkt

clean:
	@rm -f fuzz.c {musl,glibc}{.bin,-fuzz}
