//////////////////////
#include "lexeme.h"	//
//////////////////////
enum lexeme_type : short{
	AND,
	ANYTHING,
	ARGS,
	ASSIGN,
	BLOCK,
	BOOLEAN,
	CHARACTER,
	CLOSE_BRACE,
	CLOSE_BRACKET,
	CLOSE_PAREN,
	COLON,
	COMMA,
	DECREMENT,
	DECREMENT_ONE,
	DIVIDE,
	DOT,
	ELSE,
	END_OF_FILE,
	EQUAL,
	FOR,
	FUNCTION,
	FUNCTION_CALL,
	FUNCTION_GLUE,
	GLUE,
	GREATER_THAN,
	GREATER_THAN_EQUAL,
	IF,
	INCREMENT,
	INCREMENT_ONE,
	INTEGER,
	LESS_THAN,
	LESS_THAN_EQUAL,
	MINUS,
	NOT,
	NOT_EQUAL,
	OPEN_BRACE,
	OPEN_BRACKET,
	OPEN_PAREN,
	OR,
	PARAMS,
	PLUS,
	POWER,
	PRINT,
	PRINTLN,
	PROGRAM,
	REAL,
	RETURN,
	SEMI,
	STRING,
	TIMES,
	UNKNOWN,
	VARIABLE,
	WHILE,
	ENV,
	VALUES,
	JOIN,
	TABLE,
	VALS,
	VARS,
	MOD,
	CLOSURE
};
string index_to_string(int index){
	switch(index){
		case 0: return "AND";
		case 1: return "ANYTHING";
		case 2: return "ARGS";
		case 3: return "ASSIGN";
		case 4: return "BLOCK";
		case 5: return "BOOLEAN";
		case 6: return "CHARACTER";
		case 7: return "CLOSE_BRACE";
		case 8: return "CLOSE_BRACKET";
		case 9: return "CLOSE_PAREN";
		case 10: return "COLON";
		case 11: return "COMMA";
		case 12: return "DECREMENT";
		case 13: return "DECREMENT_ONE";
		case 14: return "DIVIDE";
		case 15: return "DOT";
		case 16: return "ELSE";
		case 17: return "END_OF_FILE";
		case 18: return "EQUAL";
		case 19: return "FOR";
		case 20: return "FUNCTION";
		case 21: return "FUNCTION_CALL";
		case 22: return "FUNCTION_GLUE";
		case 23: return "GLUE";
		case 24: return "GREATER_THAN";
		case 25: return "GREATER_THAN_EQUAL";
		case 26: return "IF";
		case 27: return "INCREMENT";
		case 28: return "INCREMENT_ONE";
		case 29: return "INTEGER";
		case 30: return "LESS_THAN";
		case 31: return "LESS_THAN_EQUAL";
		case 32: return "MINUS";
		case 33: return "NOT";
		case 34: return "NOT_EQUAL";
		case 35: return "OPEN_BRACE";
		case 36: return "OPEN_BRACKET";
		case 37: return "OPEN_PAREN";
		case 38: return "OR";
		case 39: return "PARAMS";
		case 40: return "PLUS";
		case 41: return "POWER";
		case 42: return "PRINT";
		case 43: return "PRINTLN";
		case 44: return "PROGRAM";
		case 45: return "REAL";
		case 46: return "RETURN";
		case 47: return "SEMI";
		case 48: return "STRING";
		case 49: return "TIMES";
		case 50: return "UNKNOWN";
		case 51: return "VARIABLE";
		case 52: return "WHILE";
		case 53: return "ENV";
		case 54: return "VALUES";
		case 55: return "JOIN";
		case 56: return "TABLE";
		case 57: return "VALS";
		case 58: return "VARS";
		case 59: return "MOD";
		case 60: return "CLOSURE";

		default:
		return "TYPE_NOT_MADE!";
	}
}
string Lexeme::type_to_string(){
	switch(type){
		case 0: return "AND";
		case 1: return "ANYTHING";
		case 2: return "ARGS";
		case 3: return "ASSIGN";
		case 4: return "BLOCK";
		case 5: return "BOOLEAN";
		case 6: return "CHARACTER";
		case 7: return "CLOSE_BRACE";
		case 8: return "CLOSE_BRACKET";
		case 9: return "CLOSE_PAREN";
		case 10: return "COLON";
		case 11: return "COMMA";
		case 12: return "DECREMENT";
		case 13: return "DECREMENT_ONE";
		case 14: return "DIVIDE";
		case 15: return "DOT";
		case 16: return "ELSE";
		case 17: return "END_OF_FILE";
		case 18: return "EQUAL";
		case 19: return "FOR";
		case 20: return "FUNCTION";
		case 21: return "FUNCTION_CALL";
		case 22: return "FUNCTION_GLUE";
		case 23: return "GLUE";
		case 24: return "GREATER_THAN";
		case 25: return "GREATER_THAN_EQUAL";
		case 26: return "IF";
		case 27: return "INCREMENT";
		case 28: return "INCREMENT_ONE";
		case 29: return "INTEGER";
		case 30: return "LESS_THAN";
		case 31: return "LESS_THAN_EQUAL";
		case 32: return "MINUS";
		case 33: return "NOT";
		case 34: return "NOT_EQUAL";
		case 35: return "OPEN_BRACE";
		case 36: return "OPEN_BRACKET";
		case 37: return "OPEN_PAREN";
		case 38: return "OR";
		case 39: return "PARAMS";
		case 40: return "PLUS";
		case 41: return "POWER";
		case 42: return "PRINT";
		case 43: return "PRINTLN";
		case 44: return "PROGRAM";
		case 45: return "REAL";
		case 46: return "RETURN";
		case 47: return "SEMI";
		case 48: return "STRING";
		case 49: return "TIMES";
		case 50: return "UNKNOWN";
		case 51: return "VARIABLE";
		case 52: return "WHILE";
		case 53: return "ENV";
		case 54: return "VALUES";
		case 55: return "JOIN";
		case 56: return "TABLE";
		case 57: return "VALS";
		case 58: return "VARS";
		case 59: return "MOD";
		case 60: return "CLOSURE";

		default:
		return "TYPE_NOT_MADE!";
	}
}
Lexeme::Lexeme(){}
Lexeme::Lexeme(lexeme_type t,int l){
	type=t;
	lineNumber=l;
}
Lexeme::Lexeme(lexeme_type t,int l,string s){
	type=t;
	lineNumber=l;
	strVal=s;
}
Lexeme::Lexeme(lexeme_type t,int l,char c){
	type=t;
	lineNumber=l;
	chVal=c;
}
Lexeme::Lexeme(lexeme_type t,int l,int i){
	type=t;
	lineNumber=l;
	intVal=i;
}
Lexeme::Lexeme(lexeme_type t,int l,float f){
	type=t;
	lineNumber=l;
	realVal=f;
}
Lexeme::Lexeme(lexeme_type t,int l,bool i){
	type=t;
	lineNumber=l;
	boolVal=i;
}
Lexeme::Lexeme(lexeme_type t){
	type=t;
}
void Lexeme::display(){
	if(type==CHARACTER)
		cout<<"CHARACTER: "<<chVal<<endl;
	else if(type==STRING)
		cout<<"STRING:    "<<strVal<<endl;
	else if(type==INTEGER)
		cout<<"INTEGER:   "<<intVal<<endl;
	else if(type==REAL)
		cout<<"REAL:      "<<realVal<<endl;
	else if(type==BOOLEAN)
		cout<<"BOOLEAN:   "<<boolVal<<endl;
	else if(type==VARIABLE)
		cout<<"VARIABLE:  "<<strVal<<endl;
	else{
		cout<<"KEYWORD:   ";print_blue(type_to_string());
	}
}
string Lexeme::getValue(){
	if(type==CHARACTER)
		return toString(chVal);
	else if(type==STRING)
		return strVal;
	else if(type==INTEGER)
		return to_string(intVal);
	else if(type==REAL)
		return to_string(realVal);
	else if(type==BOOLEAN){
		if(boolVal)
			return "TRUE";
		else
			return "FALSE";
	}
	else if(type==VARIABLE)
		return strVal;
	return "NULL";
}



bool Lexeme::hasLeft(){
	if(this->left)
		return true;
	return false;
}
bool Lexeme::hasRight(){
	if(this->right)
		return true;
	return false;
}
///////////////////////
// just some helpers //
///////////////////////

Lexeme* cons(lexeme_type t,Lexeme* left,Lexeme* right){
	Lexeme* main = new Lexeme(t);
	main->left=left;
	main->right=right;
	return main;
}
Lexeme* cons(Lexeme* main,Lexeme* left,Lexeme* right){
	main->left=left;
	main->right=right;
	return main;
}


bool sameVariable(Lexeme* left, Lexeme* right){
	if(!left->strVal.empty() && !right->strVal.empty())
		if(left->type==VARIABLE && right->type== VARIABLE){
			if(left->strVal==right->strVal)
				return true;
		}
	return false;
}

Lexeme::~Lexeme(){  
	cout << "Hey look I am in destructor" << endl;
	delete this;
} 