//////////////////////
#include "parser.h" //
//////////////////////
/*
	NOTE: C++ has right to left implementation
		  Clang apparently has a left to right
*/

Lexeme* current;

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
	// body->right=block();
	tree->right=body;
	return tree;
}
///////////////////////////////////////////////
bool paramListPending(){
	return check(VARIABLE);
}
Lexeme* paramList(){
	Lexeme* paramTree = cons(match(VARIABLE),NULL,NULL);
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
	match(CLOSE_BRACE);
	return tree;
}
Lexeme*  statementList() {
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
	incrementOnePending() 		||
	decrementOnePending() 		||
	varExprPending();
}
Lexeme* statement(){
	if(funcDefPending())
		return funcDef();
	else if(printStatementPending())
		return printStatement();
	else if(printlnStatementPending())
		printlnStatement();
	else if(incrementOnePending())
		incrementOne();
	else if(decrementOnePending())
		decrementOne();
	else if(varExprPending())
		varExpr();
	return NULL;
}
/////////////////////////////////////////////////////
bool varExprPending(){
	return check(VARIABLE);
}
Lexeme* varExpr(){ 
	Lexeme* tree = cons(match(VARIABLE),NULL,NULL);
	if (check(OPEN_PAREN)){ //function call
		match(OPEN_PAREN); 
		tree=cons(FUNCTION_CALL,tree,NULL);
		//tree.setCdr(argsList());
		match(CLOSE_PAREN); 
	}

	/*else if(check("OBRACK")) {  //array set
		match("OBRACK");
		tree.setCar(expr());
		match("CBRACK");			
		Lexeme temp = tree;
		tree = cons("ARRAY_SET",temp,NULL);
		tree.lineNumber=temp.lineNumber;
		match(ASSIGN);
		tree.setCdr(expr());
	}*/
	else if(check(ASSIGN)) {
		tree = cons(match(ASSIGN),tree,NULL);
		tree->right = expr();
	}
	else if(incrementPending()){
		tree->left = match(INCREMENT);
		tree->right = unary();
	}
	else if(decrementPending()){
		tree->left = match(DECREMENT);
		tree->right = unary();
	}
	match(SEMI);
	return tree;
}
///////////////////////////////////////////////
bool printStatementPending(){
	check(PRINT);
}
Lexeme* printStatement(){
	Lexeme* tree = cons(PRINT,NULL,NULL);
	return tree;
}
///////////////////////////////////////////////
bool printlnStatementPending(){
	check(PRINTLN);
}
Lexeme* printlnStatement(){
	Lexeme* tree = cons(PRINTLN,NULL,NULL);
	return tree;
}
///////////////////////////////////////////////
Lexeme* expr(){
	Lexeme* uTree=unary();

	if(opPending()) // +  -  *  /  ^
	{
		Lexeme* oTree=op();
		Lexeme* eTree=expr();
		return cons(oTree,uTree,eTree);
	}
	return NULL;
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
	return check(PLUS)	||
	check(MINUS)	||
	check(TIMES)	||
	check(DIVIDE)	||
	check(POWER);
}
Lexeme* op() {
	return advance();
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
	Lexeme* tree=cons(match(INCREMENT_ONE),match(VARIABLE),NULL);
	match(SEMI);
	return tree;
}

bool decrementOnePending() {
	return check(DECREMENT_ONE);
}
Lexeme* decrementOne() {
	Lexeme* tree=cons(match(DECREMENT_ONE),match(VARIABLE),NULL);
	match(SEMI);
	return tree;
}

//////////////////////////////////////////////////////////////
bool incrementPending() {
	return check(INCREMENT);
}
bool decrementPending() {
	return check(DECREMENT);
}

///////////////////////////////////////////////
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
		print_red("\tActual: "+current->type_to_string());
		print_red("\tExpected: "+current->type_to_string());
		//exit(EXIT_FAILURE);
	}
}
void showTree(Lexeme* tree){
	print_blue("TYPE: " + tree->type_to_string());
	print("    VALUE: "+ tree->getValue());
	print("    LINE: " + tree->lineNumber);
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
