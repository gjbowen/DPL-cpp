#include "../headers/evaluator.h"

Lexeme* eval(Lexeme* tree, Lexeme* env){
	switch (tree->type)
	{
			//self evaluating
		case INTEGER: return tree;
		case REAL: return tree;
		case STRING: return tree;
		case BOOLEAN: return tree;
			// //find value of variables in the environment
		case VARIABLE: return lookupEnv(tree,env);
			// //parenthesized expression
			// case OPEN_PAREN: return eval(tree->right,env);
			// //operators (both sides evaluated)
		case PLUS: return evalPlus(tree,env);
		case MINUS: return evalMinus(tree,env);
		case TIMES: return evalTimes(tree,env);
		case DIVIDE: return evalDivide(tree,env);
		case POWER: return evalPower(tree,env);
		case MOD: return evalMod(tree,env);
		case INCREMENT_ONE: return evalIncrementOne(tree,env);
		case DECREMENT_ONE: return evalDecrementOne(tree,env);
		case INCREMENT: return evalIncrement(tree,env);
		case DECREMENT: return evalDecrement(tree,env);
		case FUNCTION: return evalFuncDef(tree,env);

			// case GREATER_THAN: return evalSimpleOp(tree,env);
			// //AND and OR short-circuit
			// case AND:
			// case OR: return evalShortCircuitOp(tree,env);
			// //dot operator evals lhs, rhs a variable
			// case DOT: return evalDot(tree,env);
			// //assign operator evals rhs for sure
			// //	lhs is a variable or a dot operation
		case ASSIGN: return evalAssign(tree,env);
			// //variable and function definitions
			// case VAR_DEF: return evalVarDef(tree,env);
			// case FUNC_DEF: return evalFuncDef(tree,env);
			// //imperative constructs
		case PRINT: return evalPrint(tree,env);
			// case WHILE: return evalWhile(tree,env);
			// //function calls
		case FUNCTION_CALL: return evalFuncCall(tree,env);
			// //program and function body are parsed as blocks
		case BLOCK: return evalBlock(tree,env);
		default:
		print_red("UNKNOWN TYPE - "+tree->type_to_string());
		return NULL;
	}
	return NULL;
}

//////////////////
// Function Def //
//////////////////
Lexeme* evalFuncDef(Lexeme* tree,Lexeme* env){
	Lexeme* closure = cons(CLOSURE,tree->right,env);
	insertEnv(tree->left,closure,env);
	return NULL;
}

///////////////////
// Function Call //
///////////////////
Lexeme* evalFuncCall(Lexeme* tree,Lexeme* env){
	Lexeme* funcCallName =  tree->left; // DONE
	Lexeme* closure = 		lookupEnv(funcCallName,env);
	Lexeme* args = 		 	tree->right; // DONE
	Lexeme* params = 	 	closure->left->left; // DONE
	Lexeme* body =     	 	closure->left->right; // DONE
	Lexeme* closureEnv = 	closure->right; //INFINITE LOOP
	Lexeme* evaluatedArgs = evalArgs(args,env); // evaluate args
	env = extendEnv(params,evaluatedArgs,closureEnv); // extend the env
	return eval(body,env);
}

Lexeme* evalBlock(Lexeme* tree,Lexeme* env){
	while(tree){
		eval(tree->left,env);
		tree = tree->right;
	}
	return NULL;
}

Lexeme* evalArgs(Lexeme* tree,Lexeme* env){
	if(tree)
		return cons(JOIN,eval(tree->left,env),evalArgs(tree->right,env));
	else
		return NULL;
}

//
// MATH OPERATIONS
//
Lexeme* evalPlus(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = val->intVal + result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(result->getValue()) + stof(val->getValue());
		val->type=REAL;
	}
	else
	{
		val->strVal = val->getValue() + result->getValue();
		val->type=STRING; // convert to a string
	}
	return val;
}
Lexeme* evalMinus(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = val->intVal - result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(val->getValue()) - stof(result->getValue());
		val->type=REAL;
	}
	return val;
}
Lexeme* evalTimes(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = val->intVal * result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(val->getValue()) * stof(result->getValue());
		val->type=REAL;
	}
	return val;
}
Lexeme* evalDivide(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = val->intVal / result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(val->getValue()) / stof(result->getValue());
		val->type=REAL;
	}
	return val;
}
Lexeme* evalPower(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = pow(val->intVal,result->intVal);
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = pow(stof(val->getValue()),stof(result->getValue()));
		val->type=REAL;
	}
	return val;
}
Lexeme* evalMod(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal = val->intVal % result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = fmod(stof(val->getValue()),stof(result->getValue()));
		val->type=REAL;
	}
	return val;
}
Lexeme* evalIncrementOne(Lexeme* tree, Lexeme* env){
	Lexeme* var = eval(tree->left,env);
	Lexeme* val = eval(var,env);
	if(val->type==INTEGER)
		val->intVal += 1;
	else if(val->type==REAL)
		val->realVal += 1;
	return val;
}
Lexeme* evalDecrementOne(Lexeme* tree, Lexeme* env){
	Lexeme* var = eval(tree->left,env);
	Lexeme* val = eval(var,env);
	if(val->type==INTEGER)
		val->intVal -= 1;
	else if(val->type==REAL)
		val->realVal -= 1;
	return val;
}
Lexeme* evalIncrement(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);

	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal += result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(val->getValue()) + stof(result->getValue());
		val->type=REAL;
	}
	return val;
}
Lexeme* evalDecrement(Lexeme* tree, Lexeme* env){
	Lexeme* val = eval(tree->left,env);
	Lexeme* result = eval(tree->right,env);
	
	if(val->type==INTEGER && result->type==INTEGER)
		val->intVal= val->intVal - result->intVal;
	else if((val->type==INTEGER||val->type==REAL) && 
		(result->type==INTEGER||result->type==REAL))
	{
		val->realVal = stof(val->getValue()) - stof(result->getValue());
		val->type=REAL;
	}
	return val;
}
Lexeme* evalPrint(Lexeme* tree, Lexeme* env){
	tree = tree->left;
	string tokens =eval(tree,env)->getValue();
	print_blue(tokens);
	return NULL;
}
Lexeme* evalAssign(Lexeme* tree, Lexeme* env){
	Lexeme* var = tree->left;
	Lexeme* val = eval(tree->right,env);
	updateEnv(var,val,env);
	return NULL;
}