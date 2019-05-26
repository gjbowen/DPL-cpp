#ifndef parser_
#define parser_


Lexeme* advance();
Lexeme* match(lexeme_type type);
bool check(lexeme_type type);
void matchNoAdvance(lexeme_type type);
void showTree();


//add to helper
Lexeme* cons(lexeme_type t,Lexeme* left,Lexeme* right);
Lexeme* cons(Lexeme* main,Lexeme* left,Lexeme* right);

#endif