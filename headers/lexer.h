#ifndef lexer_
#define lexer_
void getNextLine();
void getChar();
void cleanChar();
void pushBack();
void skipWhiteSpace();
Lexeme* lex();
Lexeme* lexVariableOrKeyword();
bool isPrint(string token);
bool isPrintln(string token);
Lexeme* decNumber();
Lexeme* lexNumber();
Lexeme* lexString();
#endif
