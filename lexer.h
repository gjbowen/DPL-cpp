#ifndef lexer_
#define lexer_
void getNextLine();
void getChar();
void cleanChar();
void pushBack();
void skipWhiteSpace();
Lexeme* lex();
Lexeme* lexVariableOrKeyword();
Lexeme* decNumber();
Lexeme* lexNumber();
Lexeme* lexString();
#endif
