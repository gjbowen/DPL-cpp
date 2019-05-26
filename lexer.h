#ifndef lexer_
#define lexer_

void getNextLine();
void cleanChar();
void getChar();
void skipWhiteSpace();
void pushBack();

Lexeme* lex();
Lexeme* lexVariableOrKeyword();
Lexeme* lexString();
Lexeme* lexNumber();
Lexeme* decNumber();

#endif