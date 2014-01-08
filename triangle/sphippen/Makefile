SPH_LIBS = /home/sphippen/libs
CADE_FLAGS = -I$(SPH_LIBS)/include -L$(SPH_LIBS)/lib -Wl,-rpath=$(SPH_LIBS)/lib
COMMON_FLAGS = -std=c99 -Wall -Werror -pedantic $(CADE_FLAGS)
LIBS = -lgmp

triangle: triangle.c
	gcc -o triangle $(COMMON_FLAGS) -O2 triangle.c $(LIBS)

debug: triangle.c
	gcc -o triangle $(COMMON_FLAGS) -g triangle.c $(LIBS)

.PHONY: clean
clean:
	@rm -rf triangle
