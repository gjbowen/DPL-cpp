//////////////////////
#include "lexeme.h"	//
//////////////////////
enum lexeme_type : short{
	ASSIGN,
	BOOLEAN,
	CHARACTER,
	CLOSE_BRACKET,
	CLOSE_PAREN,
	COLON,
	COMMA,
	FUNCTION,
	DIVIDE,
	END_OF_FILE,
	EQUAL,
	GREATER_THAN,
	GREATER_THAN_EQUAL,
	INTEGER,
	LESS_THAN,
	LESS_THAN_EQUAL,
	MINUS,
	OPEN_BRACKET,
	OPEN_PAREN,
	PLUS,
	PRINT,
	PRINTLN,
	REAL,
	SEMI,
	STRING,
	TIMES,
	UNKNOWN,
	VARIABLE,

	FOR,
	WHILE,
	IF,
	ELSE,
	INCREMENT_ONE,
	DECREMENT_ONE,
	POWER,
	DOT,
	NOT,
	OPEN_BRACE,
	CLOSE_BRACE,
	RETURN,
	ANYTHING,
	PROGRAM,
	FUNCTION_GLUE,
	PARAMS,
	INCREMENT,
	DECREMENT,
	FUNCTION_CALL,
	BLOCK,
	ARGS
};

string Lexeme::type_to_string(){
	switch(type){
		case 0: return "ASSIGN";
		case 1:	return "BOOLEAN";
		case 2:	return "CHARACTER";
		case 3:	return "CLOSE_BRACKET";
		case 4:	return "CLOSE_PAREN";
		case 5:	return "COLON";
		case 6:	return "COMMA";
		case 7:	return "FUNCTION";
		case 8:	return "DIVIDE";
		case 9:	return "END_OF_FILE";
		case 10: return "EQUAL";
		case 11: return "GREATER_THAN";
		case 12: return "GREATER_THAN_EQUAL";
		case 13: return "INTEGER";
		case 14: return "LESS_THAN";
		case 15: return "LESS_THAN_EQUAL";
		case 16: return "MINUS";
		case 17: return "OPEN_BRACKET";
		case 18: return "OPEN_PAREN";
		case 19: return "PLUS";
		case 20: return "PRINT";
		case 21: return "PRINTLN";
		case 22: return "REAL";
		case 23: return "SEMI";
		case 24: return "STRING";
		case 25: return "TIMES";
		case 26: return "UNKNOWN";
		case 27: return "VARIABLE";
		case 28: return "FOR";
		case 29: return "WHILE";
		case 30: return "IF";
		case 31: return "ELSE";
		case 32: return "PLUSPLUS";
		case 33: return "MINUSMINUS";
		case 34: return "POWER";
		case 35: return "DOT";
		case 36: return "NOT";
		case 37: return "OPEN_BRACE";
		case 38: return "CLOSE_BRACE";
		case 39: return "RETURN";
		case 40: return "ANYTHING";
		case 41: return "PROGRAM";
		case 42: return "FUNCTION_GLUE";
		case 43: return "PARAMS";
		case 44: return "FUNCTION_CALL";
		case 45: return "BLOCK";
		case 46: return "ARGS";
	}
}
Lexeme::Lexeme(){}
Lexeme::Lexeme(lexeme_type t){
	type=t;
}
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
	else if(type==BOOLEAN)
		return to_string(boolVal);
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