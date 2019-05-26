//////////////////////
#include "parser.h" //
//////////////////////

Lexeme* current;

//////////////////////////////////////////////////////////////
Lexeme* program(){
	Lexeme* tree = new Lexeme(PROGRAM);
	if(statementPending()) {
		tree.setCar(statement());
	}
	if (programPending())
		tree.setCdr(program());
	return tree;
}

bool programPending(){
	return statementPending();
}
//////////////////////////////////////////////////////////////
bool funcDefPending(){
	return check(FUNCTION);
}
Lexeme* funcDef(){
	Lexeme* tree = cons(match(FUNCTION),match("ID"),null);
	Lexeme* body = new Lexeme(FUNCTION_GLUE);
	match(Open_PAREN);
	body.setCar(paramList()); 
	match(CLOSE_PAREN);

	body.setCdr(block());

	tree.setCdr(body);;
	return tree;
}










//////////////////////////////////////////////////////////////
//first helper function in the Parser/Parser
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
		print_red("Syntax.Error\n\tActual: "+current->type_to_string());
			// "Expected: "+current->type_to_string(type)+"\n\t"+
		exit(EXIT_FAILURE);
	}
}
void showTree(Lexeme* tree){
	print("TYPE: "+tree->type_to_string()+"    VALUE: "+tree->getValue());
	print("    LINE: "+tree->lineNumber);
	print("left node: "+to_string(tree->hasLeft())+"\tright node: "+to_string(tree->hasRight()));

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
//////////////////////////////////////////////
// just some helpers
/////////////////////////////////////////////

Lexeme* cons(lexeme_type t,Lexeme* left,Lexeme* right){
	Lexeme* main = new Lexeme(t);
	main->left=left;
	main->right=right;
	return main;
}
Lexeme* cons(Lexeme* main,Lexeme* left,Lexeme* right){
	main->right=right;
	main->left=left;
	return main;
}
