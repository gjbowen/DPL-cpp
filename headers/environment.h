#ifndef environment_
#define environment_
Lexeme* createEnv();
Lexeme* extendEnv(Lexeme* vars,Lexeme* vals,Lexeme* env);
void insertEnv(Lexeme* variable,Lexeme* value,Lexeme* env);
Lexeme* lookupEnv(Lexeme* variable,Lexeme* env);
Lexeme* updateEnv(Lexeme* variable,Lexeme* newValue,Lexeme* env);
#endif
