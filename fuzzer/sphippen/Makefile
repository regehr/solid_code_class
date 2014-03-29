.PHONY: fuzz clean

fuzz:
	./fuzz.rkt
	@cp vfprintf-fixed.c.gcov holy-grail

clean:
	@rm -f fuzz.c fuzz *-fuzz *.bin *.o *.gcov *.gcno *.gcda
