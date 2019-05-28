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
	if(argc>1){
		string mode (args[1]);
		print_red("MODE: " + mode);
		Lexeme* lexeme = new Lexeme();
		if(mode=="tokens"){
			while(lexeme->type!=END_OF_FILE){
				lexeme=lex();
				lexeme->display();
			}
		}
		else if(mode=="tree"){
			lexeme = parse();
			showTree(lexeme);
		}
		else if(mode=="tree"){
			lexeme = parse();
			//showTree(lexeme);
		}
	}
	print_green("--------------------------------------");
	myfile.close();
	
	return 0;
}
