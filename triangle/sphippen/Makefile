SPH_LIBS = /home/sphippen/libs
CADE_FLAGS = -I$(SPH_LIBS)/include -L$(SPH_LIBS)/lib -Wl,-rpath=$(SPH_LIBS)/lib
COMMON_FLAGS = -std=c99 -Wall -Werror -pedantic $(CADE_FLAGS)
LIBS = -lgmp
BIN = triangle
SRC = $(BIN).c

$(BIN): $(SRC)
	gcc -o $(BIN) $(COMMON_FLAGS) -O2 $(SRC) $(LIBS)

debug: $(SRC)
	gcc -o $(BIN) $(COMMON_FLAGS) -g $(SRC) $(LIBS)

test: $(SRC)
	gcc -o $(BIN) $(COMMON_FLAGS) -fprofile-arcs -ftest-coverage $(SRC) $(LIBS)
	@echo
	python3 test.py
	@echo
	gcov -b $(SRC)

.PHONY: clean
clean:
	@rm -rf $(BIN) $(BIN).gcda $(SRC).gcov $(BIN).gcno $(BIN).dSYM testresults.txt
