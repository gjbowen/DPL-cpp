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
    myfile.open("example.txt");
    getNextLine();
    Lexeme* lexeme = new Lexeme();
    Lexeme* env = createEnv();
    lexeme = parse();
    while(lexeme)
    {
        eval(lexeme->left,env);
        lexeme=lexeme->right;
    }
    myfile.close();
    /////////////////////////////////////////
	/*if(argc>1)
	{
		myfile.open("example.txt");
		getNextLine();
		print_yellow("--------------------------------------");
		string mode (args[1]);
		print_red("MODE: " + mode);
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
		else if(mode=="environment")
		{
			Lexeme* env = createEnv();
			string var_str = "x";
			Lexeme* var = new Lexeme(VARIABLE,0,var_str);
			var_str = "y";
			Lexeme* var2 = new Lexeme(VARIABLE,0,var_str);
			var_str = "z";
			Lexeme* var3 = new Lexeme(VARIABLE,0,var_str);

			Lexeme* val = new Lexeme(INTEGER,0,1);
			Lexeme* val2 = new Lexeme(INTEGER,0,2);
			Lexeme* val3 = new Lexeme(INTEGER,0,3);

			Lexeme* val4 = new Lexeme(INTEGER,0,9);

			insertEnv(var,val,env);
			insertEnv(var2,val2,env);
			insertEnv(var3,val3,env);

			updateEnv(var2,val4,env);

			showTree(env->left);
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
		print_yellow("--------------------------------------");
		myfile.close();
	}*/

	return 0;
}
