CC = g++ -std=c++11
CFLAGS = -Wall -Wextra -pedantic

compile: main.cpp
	${CC} -o a.out ${CFLAGS} baby.cpp main.cpp binary.cpp

run:
	./main.cpp

clean:
	rm -f a.out