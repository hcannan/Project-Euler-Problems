# fibWords makefile

# compile
compile:
	g++ -Wall -g -std=c++11 -o fib fibWords.cc

# run:
run:
	./fib

# clean compiled stuff
clean:
	rm fib
	rm -rf *.dSYM