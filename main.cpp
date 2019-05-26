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
 	Lexeme* token = new Lexeme();
 	Lexeme* tree = new Lexeme();

	while (token->type != END_OF_FILE) 
	{ 
		token = lex();
		cons(tree,NULL,token);
		//tree=tree->right;
		token->display(); 
	} 
	myfile.close();
	print_green("--------------------------------------");
	showTree(tree);
	return 0;
}
