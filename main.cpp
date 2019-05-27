#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
using namespace std;

char ch;
ifstream myfile;
string line;
int lineNumber=0;

#include "helper.cpp"
#include "lexeme.cpp"
#include "lexer.cpp"
#include "parser.cpp"

int main(int argc, char *args[]){
	myfile.open("example.txt");
	getNextLine();
	print_green("--------------------------------------");
	Lexeme* tree = parse();
	showTree(tree);
	print_green("--------------------------------------");
	myfile.close();
	
	return 0;
}
