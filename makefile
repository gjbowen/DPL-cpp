
# define a makefile variable for the java & compiler
cc = g++
run  = ./
rm  = rm -rf

default: clear compile run

# Clear Console
#
clear:
	clear

# Test File
#
test:
	g++ ./test.cpp -o test.out
	./test.out

# Compile c++ files
#
compile:
	g++ ./main.cpp -o main.out

headers:
	clear
	python3 help.py
# Run
#
run:
	./main.out

tokens:
	g++ ./main.cpp -o main.out
	clear
	./main.out tokens
token:
	$(tokens)
	
tree:
	g++ ./main.cpp -o main.out
	clear
	./main.out tree

environment:
	g++ ./main.cpp -o main.out
	clear
	./main.out environment

# Removes all .out files
#
clean: 
	$(RM) *.out *.o
