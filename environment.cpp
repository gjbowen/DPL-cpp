#include "environment.h"


Lexeme* createEnv(){
	return cons(ENV,cons(TABLE,NULL,NULL),NULL);
}

Lexeme* extendEnv(Lexeme* vars,Lexeme* vals,Lexeme* env){
	return cons(ENV,cons(TABLE,vars,vals),env);
}

void insertEnv(Lexeme* variable,Lexeme* value,Lexeme*env){
	Lexeme* table = env->left;
	table->left =cons(VARS,variable,table->left);
	table->right=cons(VALS,value,table->right);
}

Lexeme* lookupEnv(Lexeme* variable,Lexeme* env){
	while (env)
	{
		Lexeme* table = env->left;
		Lexeme* vars = table->left;
		Lexeme* vals = table->right;
		while (vars)
		{
			if (sameVariable(variable,vars->left))
			{
				return vals->left;
			}
			vars = vars->right;
			vals = vals->right;
		}
		env = env->right;
	}
	print_red("variable "+variable->strVal+" is undefined");
	exit(EXIT_FAILURE);
	return NULL;
}
Lexeme* updateEnv(Lexeme* variable,Lexeme* newValue,Lexeme* env){
	while (env)
	{
		Lexeme* table = env->left;
		Lexeme* vars = table->left;
		Lexeme* vals = table->right;
		while (vars)
		{
			if (sameVariable(variable,vars->left))
			{
				vals->left=newValue;
				return NULL;
			}
			vars = vars->right;
			vals = vals->right;
		}
		env = env->right;
	}
	print_red("variable "+variable->strVal+" is undefined");
	exit(EXIT_FAILURE);
	return NULL;
}