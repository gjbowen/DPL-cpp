//////////////////////
#include "../headers/parser.h" //
//////////////////////
/*
	NOTE: C++ has right to left implementation
		  Clang apparently has a left to right
*/

Lexeme* current;
///////////////////////////////////////////////
Lexeme* program(){
	Lexeme* tree = new Lexeme(PROGRAM);
	if(statementPending())
		tree->left=statement();
	if (statementPending())
		tree->right=program();
	return tree;
}
///////////////////////////////////////////////
bool funcDefPending(){
	return check(FUNCTION);
}
Lexeme* funcDef(){
	Lexeme* func = match(FUNCTION);
	Lexeme* var  = match(VARIABLE);
	Lexeme* tree = cons(func,var,NULL);
	Lexeme* body = new Lexeme(FUNCTION_GLUE);
	match(OPEN_PAREN);
	if(paramListPending())
		body->left =  paramList();
	match(CLOSE_PAREN);
	body->right=block();
	tree->right=body;
	return tree;
}
///////////////////////////////////////////////
bool returnPending(){
	return check(RETURN);
}
Lexeme* returnList(){
	Lexeme* tree = cons(match(RETURN),NULL,NULL);
	tree->left = expr();
	match(SEMI);
	return tree;
}
///////////////////////////////////////////////
bool paramListPending(){
	return check(VARIABLE);
}
Lexeme* paramList(){
	Lexeme* var = match(VARIABLE);
	Lexeme* paramTree = cons(ARGS,var,NULL);
	if(check(COMMA)) {
		match(COMMA);//more!
		paramTree->right = paramList();	
	}
	return paramTree;
}
Lexeme* argsList(){
	Lexeme* argTree = cons(ARGS,expr(),NULL);
	if(check(COMMA)) {
		match(COMMA);
		argTree->right = argsList();
	}
	return argTree;
}
///////////////////////////////////////////////
Lexeme* block() {
	match(OPEN_BRACE);
	Lexeme* tree = statementList();
	if(returnPending()){

	}
	match(CLOSE_BRACE);
	return tree;
}
Lexeme* statementList() {
	if(statementPending()){
		Lexeme* sTree = statement();
		Lexeme* sListTree = statementList(); 	
		return cons(BLOCK,sTree,sListTree);
	}
	return NULL;
}
///////////////////////////////////////////////
bool statementPending(){
	return 
	funcDefPending() 			||
	printStatementPending() 	||
	printlnStatementPending() 	||
	ifStatementPending() 		||
	incrementOnePending() 		||
	decrementOnePending() 		||
	whileStatementPending() 	||
	forStatementPending() 		||
	varExprPending();
}
Lexeme* statement(){
	if(funcDefPending())
		return funcDef();
	else if(printStatementPending())
		return printStatement();
	else if(printlnStatementPending())
		printlnStatement();
	else if(ifStatementPending())
		return ifStatement();
	else if(whileStatementPending())
		return whileStatement();
	else if(forStatementPending())
		return forStatement();
	/////////////////////////////
	else if(varExprPending()){
		Lexeme* tree = varExpr();
		match(SEMI);
		return tree;
	}
	else if(incrementOnePending()){
		Lexeme* tree = incrementOne();
		match(SEMI);	
		return tree;
	}
	else if(decrementOnePending()){
		Lexeme* tree = decrementOne();
		match(SEMI);	
		return tree;
	}
	return NULL;
}
/////////////////////////////////////////////////////
bool varExprPending(){
	return check(VARIABLE);
}
Lexeme* varExpr(){ 
	Lexeme* tree = cons(match(VARIABLE),NULL,NULL);
	if (check(OPEN_PAREN)) //function call
	{
		match(OPEN_PAREN); 
		tree=cons(FUNCTION_CALL,tree,NULL);
		tree->right = argsList();
		match(CLOSE_PAREN); 
	}
	else if(check(ASSIGN)) 
	{
		tree = cons(match(ASSIGN),tree,NULL);
		tree->right = expr();
	}
	else if(check(INCREMENT)) 
	{
		tree = cons(match(INCREMENT),tree,NULL);
		tree->right = expr();
	}
	else if(check(DECREMENT)) 
	{
		tree = cons(match(DECREMENT),tree,NULL);
		tree->right = expr();
	}
	//match(SEMI);
	return tree;
}
///////////////////////////////////////////////
bool printStatementPending(){
	return check(PRINT);
}
Lexeme* printStatement(){
	Lexeme* tree = cons(match(PRINT),NULL,NULL);
	match(OPEN_PAREN);
	tree->left = expr();
	match(CLOSE_PAREN);
	match(SEMI);
	return tree;
}
///////////////////////////////////////////////
bool printlnStatementPending(){
	return check(PRINTLN);
}
Lexeme* printlnStatement(){
	Lexeme* tree = cons(match(PRINTLN),NULL,NULL);
	match(OPEN_PAREN);
	tree->left = expr();
	match(CLOSE_PAREN);
	match(SEMI);
	return tree;
}
///////////////////////////////////////////////
Lexeme* expr(){
	Lexeme* unaryTree = unary();

	if(opPending()) // +  -  *  /  ^
	{
		Lexeme* opTree = op();
		Lexeme* exprTree = expr();
		Lexeme* tree =  cons(opTree,unaryTree,exprTree);
		return tree;
	}

	else if(check(OPEN_PAREN)) //function calls
	{
		match(OPEN_PAREN);
		Lexeme* exprTree = new Lexeme(FUNCTION_CALL);
		exprTree->left = unaryTree;
		exprTree->right = expr();
		match(CLOSE_PAREN);
		return exprTree;
	}
	return unaryTree;
}


bool unaryPending(){
	return 
	check(VARIABLE) ||
	check(INTEGER) 	||
	check(REAL) 	||
	check(STRING) 	||
	check(BOOLEAN) 	||
	check(CHARACTER);
}
Lexeme* unary(){
	if(unaryPending())
		return advance();
	return NULL;
}
///////////////////////////////////////////////
bool opPending() {
	return 
	check(PLUS)		||
	check(MINUS)	||
	check(TIMES)	||
	check(DIVIDE)	||
	check(MOD)		||
	check(POWER);
}
Lexeme* op() {
	return advance();
}

Lexeme* conditionExpr(){
	Lexeme* expr1 = expr();
	Lexeme* eq = equality();
	Lexeme* expr2 = expr();
	return cons(eq,expr1,expr2);
}

//////////////////////////////////////////////////////////////
bool forStatementPending() {
	return check(FOR);
}
Lexeme* forStatement() {
	Lexeme* forTree = match(FOR);
	match(OPEN_PAREN);
	Lexeme* var = varExpr();
	match(SEMI);

	Lexeme* cond = conditionExpr();
	match(SEMI);

	Lexeme* expr;
	if(incrementOnePending())
		expr = incrementOne();
	else if(decrementOnePending())
		expr =  decrementOne();
	else if(varExprPending())
		expr =  varExpr();
	match(CLOSE_PAREN);
	Lexeme* subGlueTree = cons(GLUE,var,expr);
	Lexeme* glueTree = cons(GLUE,subGlueTree,cond);

	forTree->left = glueTree;
	forTree->right = block();

	return forTree;
}
//////////////////////////////////////////////////////////////
bool whileStatementPending() {
	return check(WHILE);
}
Lexeme* whileStatement() {
	Lexeme* whileTree = match(WHILE);
	match(OPEN_PAREN);
	whileTree->left = conditionExpr();
	match(CLOSE_PAREN);
	whileTree->right = block();
	return whileTree;
}
//////////////////////////////////////////////////////////////
bool ifStatementPending() {
	return check(IF);
}
Lexeme* ifStatement() {
	Lexeme* ifTree = cons(match(IF),NULL,NULL);
	match(OPEN_PAREN);
	Lexeme* glueTree = cons(GLUE,conditionExpr(),NULL);
	match(CLOSE_PAREN);
	glueTree->right = block();
	ifTree->left = glueTree;
	Lexeme* elseTree = optElseStatement();
	ifTree->right = elseTree;
	return ifTree;
}
////////////////////////////
bool optElseStatementPending() {
	return check(ELSE);
}
Lexeme* optElseStatement() {
	if(optElseStatementPending())
	{
		Lexeme* elseTree = cons(match(ELSE),NULL,NULL);
		if(ifStatementPending()) //else if(..){}
		{
			return ifStatement();
		}
		else
		{
			elseTree->right = block();
			return elseTree;
		}
	}
	else
		return NULL;
}
//////////////////////////////////////////////////////////////
bool compoundPending() {
	return check(AND) || check(OR);
}
Lexeme* compound() {
	return match(current->type);
}
//////////////////////////////////////////////////////////////
bool equalityPending() {
	return 
	check(EQUAL)				||
	check(NOT_EQUAL)			||
	check(GREATER_THAN)			||
	check(GREATER_THAN_EQUAL)	||
	check(LESS_THAN)			||
	check(LESS_THAN_EQUAL);
}
Lexeme* equality() {
	return match(current->type);
}
//////////////////////////////////////////////////////////////
bool incrementOnePending() {
	return check(INCREMENT_ONE);
}
Lexeme* incrementOne() {
	Lexeme* op = match(INCREMENT_ONE);
	Lexeme* tree=cons(op,match(VARIABLE),NULL);
	//match(SEMI);
	return tree;
}

bool decrementOnePending() {
	return check(DECREMENT_ONE);
}
Lexeme* decrementOne() {
	Lexeme* op = match(DECREMENT_ONE);
	Lexeme* tree=cons(op,match(VARIABLE),NULL);
	// match(SEMI);
	return tree;
}
//////////////////////////////////////////////////////////////
bool incrementPending() {
	return check(INCREMENT);
}
Lexeme* increment() {
	Lexeme* op = match(INCREMENT);
	Lexeme* tree=cons(op,match(VARIABLE),NULL);
	tree->right = expr();
	//match(SEMI);
	return tree;
}

bool decrementPending() {
	return check(DECREMENT);
}
Lexeme* decrement() {
	Lexeme* op = match(DECREMENT);
	Lexeme* tree=cons(op,match(VARIABLE),NULL);
	tree->right = expr();
	// match(SEMI);
	return tree;
}

///////////////////////////////////////
///////////////////////////////////////////////
//essentially the driver for Parser
Lexeme* parse() {
	current = lex();
	Lexeme* tree = program();
	return tree;
}//first helper function in the Parser/Parser
Lexeme* advance(){
	Lexeme* oldLexeme = current;
	current=lex(); //get the next	
	//System.out.println(current.type);
	return oldLexeme;
}
//like advance but forces the current lexeme to be matched
Lexeme* match(lexeme_type type) { 
	if(type==ANYTHING)
		return advance();
	matchNoAdvance(type); //MAY be optional. unknown..
	return advance(); 
}

bool check(lexeme_type type){
	return current->type==type;
}

void matchNoAdvance(lexeme_type type){
	if (!check(type)){
		print_red("Syntax.Error");
		print_red("\tExpected: "+index_to_string(stoi(to_string(type))));
		print_red("\tActual: "+current->type_to_string());
		exit(EXIT_FAILURE);
	}
}
void showTree(Lexeme* tree){
	print_blue("TYPE: " + tree->type_to_string()+"("+to_string(tree->type)+")");
	print("    VALUE: "+ tree->getValue());
	print("    LINE: " + to_string(tree->lineNumber));
	print("    left node: "+to_string(tree->hasLeft())+"    right node: "+to_string(tree->hasRight()));

	if(tree){ 
		if(tree->hasLeft()){
			print("Going left..");
			showTree(tree->left);
			print("Back up to parent!");
		}
		if(tree->hasRight()){
			print("Going right..");
			showTree(tree->right);
			print("Back up to parent!");
		}
	}
}

