
# define a makefile variable for the java & compiler
CC = g++ -std=c++11
run  = ./
rm  = rm -rf

default: clear headers compile run

# Clear Console
#
clear:
	clear

# Compile c++ files
#
compile:
	 $(CC) ./main.cpp -o main.out -g

headers:
	clear
	python3 source/help.py

# Run
#
run:
	gdb ./main.out

# Show tokens
#
tokens:
	python3 source/help.py
	$(CC) ./main.cpp -o main.out
	clear
	./main.out tokens

# Show parse tree
#	
tree:
	python3 source/help.py
	$(CC) ./main.cpp -o main.out
	clear
	./main.out tree

# Test environment
#
environment:
	python3 source/help.py
	$(CC) ./main.cpp -o main.out
	clear
	./main.out environment

# Run the evaluator
#
evaluator:
	python3 source/help.py
	$(CC) ./main.cpp -o main.out
	clear
	./main.out evaluator

# Removes all .out files
#
clean: 
	$(RM) *.out *.o
