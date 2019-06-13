#ifndef evaluator_
#define evaluator_
Lexeme* eval(Lexeme* tree, Lexeme* env);
Lexeme* evalFuncDef(Lexeme* tree,Lexeme* env);
Lexeme* evalFuncCall(Lexeme* tree,Lexeme* env);
Lexeme* evalBlock(Lexeme* tree,Lexeme* env);
Lexeme* evalArgs(Lexeme* tree,Lexeme* env);
Lexeme* evalPlus(Lexeme* tree, Lexeme* env);
Lexeme* evalMinus(Lexeme* tree, Lexeme* env);
Lexeme* evalTimes(Lexeme* tree, Lexeme* env);
Lexeme* evalDivide(Lexeme* tree, Lexeme* env);
Lexeme* evalPower(Lexeme* tree, Lexeme* env);
Lexeme* evalMod(Lexeme* tree, Lexeme* env);
Lexeme* evalIncrementOne(Lexeme* tree, Lexeme* env);
Lexeme* evalDecrementOne(Lexeme* tree, Lexeme* env);
Lexeme* evalIncrement(Lexeme* tree, Lexeme* env);
Lexeme* evalDecrement(Lexeme* tree, Lexeme* env);
Lexeme* evalPrint(Lexeme* tree, Lexeme* env);
Lexeme* evalPrintln(Lexeme* tree, Lexeme* env);
Lexeme* evalAssign(Lexeme* tree, Lexeme* env);
#endif
