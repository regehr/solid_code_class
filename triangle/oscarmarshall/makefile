default:
	clang -lm triangle.c main.c -o triangle

debug:
	clang -Wall -Wextra -pedantic -Werror -fsanitize=undefined -lm triangle.c main.c -o triangle

clean:
	rm triangle