#ifndef parser_
#define parser_

Lexeme* program();
bool programPending();
Lexeme* funcDef();
bool funcDefPending();
Lexeme* statement();
bool statementPending();
Lexeme* paramList();
bool paramListPending();
Lexeme* argsList();

Lexeme* printStatement();
bool printStatementPending();
Lexeme* printlnStatement();
bool printlnStatementPending();
Lexeme* block();
Lexeme* expr();
Lexeme*  statementList(); 
Lexeme* unary();
bool unaryPending();

bool opPending();
Lexeme* op();
Lexeme* conditionExpr();

bool ifStatementPending();
Lexeme* ifStatement();
bool optElsePending();
Lexeme* optElseStatement();

bool whileStatementPending();
Lexeme* whileStatement();
bool forStatementPending();
Lexeme* forStatement();

bool varExprPending();
Lexeme* varExpr();

bool incrementOnePending();
Lexeme* incrementOne();
bool decrementOnePending();
Lexeme* decrementOne();
bool incrementPending();
bool decrementPending();

bool compoundPending();
Lexeme* compound();
bool equalityPending();
Lexeme* equality();
//////////////////////////
Lexeme* parse();
Lexeme* advance();
Lexeme* match(lexeme_type type);
bool check(lexeme_type type);
void matchNoAdvance(lexeme_type type);
void showTree(Lexeme* tree);


#endif