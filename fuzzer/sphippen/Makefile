.PHONY: fuzz clean

fuzz:
	./fuzz.rkt

clean:
	@cp vfprintf-fixed.c.gcov holy-grail
	@rm -f fuzz.c fuzz *-fuzz *.bin *.o *.gcov *.gcno *.gcda
