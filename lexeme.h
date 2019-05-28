#ifndef lexeme_
#define lexeme_

enum lexeme_type : short;

struct Lexeme{

	lexeme_type type;

	// has a value
	string 	strVal;
	int 	intVal;
	float 	realVal;
	bool 	boolVal;
	char 	chVal;

	Lexeme* left;
	Lexeme* right;

	int lineNumber;
	/////////////////////////////

	Lexeme();
	Lexeme(lexeme_type t);
	Lexeme(lexeme_type,int);
	Lexeme(lexeme_type,int,string);
	Lexeme(lexeme_type,int,char);
	Lexeme(lexeme_type,int,int);
	Lexeme(lexeme_type,int,float);
	Lexeme(lexeme_type,int,bool);
	void display();
	string getValue();
	string type_to_string();
	bool hasLeft();
	bool hasRight();
};
//add to helper
string index_to_string(int index);
Lexeme* cons(lexeme_type t,Lexeme* left,Lexeme* right);
Lexeme* cons(Lexeme* main,Lexeme* left,Lexeme* right);

#endif