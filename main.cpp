#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <cmath>
using namespace std;

char ch;
ifstream myfile;
string line;
int lineNumber=0;

#include "source/helper.cpp"
#include "source/lexeme.cpp"
#include "source/lexer.cpp"
#include "source/parser.cpp"
#include "source/environment.cpp"
#include "source/evaluator.cpp"

int main(int argc, char *args[]){
    /////////////////////////////////////////
    cout<<"starting.."<<endl;
    string mode = "evaluator";
    /////////////////////////////////////////
    myfile.open("example.txt");
    getNextLine();
    print_yellow  ("------------ ");
    print_red(mode);
    println_yellow(" ------------");
    Lexeme* lexeme = new Lexeme();

    if(mode=="tokens")
    {
        while(lexeme->type!=END_OF_FILE)
        {
            lexeme=lex();
            lexeme->display();
        }
    }
    else if(mode=="tree")
    {
        lexeme = parse();
        showTree(lexeme);
    }
    else if(mode=="evaluator")
    {
        Lexeme* env = createEnv();
        lexeme = parse();
        while(lexeme)
        {
            eval(lexeme->left,env);
            lexeme=lexeme->right;
        }
    }
    println_yellow("-----------------------------------");
    myfile.close();

	return 0;
}
