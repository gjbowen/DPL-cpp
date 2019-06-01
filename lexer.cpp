/////////////////////
#include "lexer.h" //
/////////////////////
char pushBackCh;
bool chHasBeenPushed=false;
bool done = false;

void getNextLine(){
	++lineNumber;
	if(!getline (myfile,line)){
		myfile.close();
		done=true;
		ch=' ';
	}
	if(!done)
	{	 
		if(line.length() == 0||line=="\n"){
			getNextLine();
		}
	}
}

void getChar(){
	if(chHasBeenPushed)
	{
		ch = pushBackCh;
		cleanChar();
		chHasBeenPushed = false;
	}

	else if(!done)
	{
		if(line.length()==0)//done with the line
			getNextLine();	
		if(!done)
		{ 
			ch = line[0];
			cleanChar();
			line = line.substr(1,line.length());
			
		}
	}
}
void cleanChar(){
	if (ch=='\t' || ch=='\r')
		ch=' ';
}

void pushBack() {
	if(chHasBeenPushed) 
	{
		cout<<"TOO MANY PUSHBACKS!!"<<endl;
		exit(1);
	}
	pushBackCh=ch;
	chHasBeenPushed=true;
}


void skipWhiteSpace() {
	if(!done){
		if(ch=='#')
		{
			getNextLine();
			getChar();
			skipWhiteSpace();
		}
		else if(ch=='\n'||ch==' ')
		{
			getChar();
			skipWhiteSpace();
		}
	}
}

Lexeme* lex(){
	getChar();

	skipWhiteSpace(); 

	if(done)
		return new Lexeme(END_OF_FILE, lineNumber); 
	switch(ch) 
	{
		case '(': return new Lexeme(OPEN_PAREN,lineNumber);
		case ')': return new Lexeme(CLOSE_PAREN,lineNumber);
		case '{': return new Lexeme(OPEN_BRACE,lineNumber);
		case '}': return new Lexeme(CLOSE_BRACE,lineNumber);
		case '[': return new Lexeme(OPEN_BRACKET,lineNumber);
		case ']': return new Lexeme(CLOSE_BRACKET,lineNumber);
		case ',': return new Lexeme(COMMA,lineNumber);
		case ':': return new Lexeme(COLON,lineNumber);
		case '*': return new Lexeme(TIMES,lineNumber);
		case '/': return new Lexeme(DIVIDE,lineNumber);
		case ';': return new Lexeme(SEMI,lineNumber);
		case '^': return new Lexeme(POWER,lineNumber);
		case '%': return new Lexeme(MOD,lineNumber);

		default:

		if (isdigit(ch))
		{ 
			return lexNumber(); 
		}
		else if(ch=='+')
		{
			getChar();
			if(ch=='+')
				return new Lexeme(INCREMENT_ONE,lineNumber);
			else if(ch=='=')
				return new Lexeme(INCREMENT,lineNumber);
			else{
				pushBack();
				return new Lexeme(PLUS,lineNumber);
			}
		}
		else if(ch=='-')
		{
			getChar();
			if(ch=='-')
				return new Lexeme(DECREMENT_ONE,lineNumber);
			if(ch=='=')
				return new Lexeme(DECREMENT,lineNumber);
			else{
				pushBack();
				return new Lexeme(MINUS,lineNumber);
			}
		}
		else if(ch=='=')
		{
			getChar();
			if(ch=='=')
				return new Lexeme(EQUAL,lineNumber);
			else{
				pushBack();
				return new Lexeme(ASSIGN,lineNumber);
			}
		}
		else if(ch=='<')
		{
			getChar();
			if(ch=='=')
				return new Lexeme(LESS_THAN_EQUAL,lineNumber);
			else{
				pushBack();
				return new Lexeme(LESS_THAN,lineNumber);
			}
		}
		else if(ch=='>')
		{
			getChar();
			if(ch=='=')
				return new Lexeme(GREATER_THAN_EQUAL,lineNumber);
			else{
				pushBack();
				return new Lexeme(GREATER_THAN,lineNumber);
			}
		}
		else if(ch=='.')
		{
			getChar();
			if(isdigit(ch))
				return decNumber();
			else{
				pushBack();
				return new Lexeme(DOT,lineNumber);
			}
		}
		else if (isalpha(ch))
		{
			return lexVariableOrKeyword();
		}
		else if (ch == '"') 
		{
			return lexString(); 
		}
		else
			return new Lexeme(UNKNOWN, lineNumber,ch); 
	}
}

Lexeme* lexVariableOrKeyword() {
	string token="";
	while (isalnum(ch)||isdigit(ch))
	{
		token = token + ch;
		getChar();
	}
	pushBack();

		//token holds either a variable or a keyword, so figure it out
	if (toUpper(token)=="FUNCTION"||toUpper(token)=="FUNC") 		
		return new Lexeme(FUNCTION,lineNumber);
	else if (toUpper(token)=="PRINT") 	return new Lexeme(PRINT,lineNumber);
	else if (toUpper(token)=="PRINTLN") return new Lexeme(PRINT,lineNumber);
	else if (toUpper(token)=="IF")    	return new Lexeme(IF,lineNumber);
	else if (toUpper(token)=="ELSE")  	return new Lexeme(ELSE,lineNumber);
	else if (toUpper(token)=="WHILE") 	return new Lexeme(WHILE,lineNumber);
	else if (toUpper(token)=="FOR")   	return new Lexeme(FOR,lineNumber);
	else if (toUpper(token)=="NOT")   	return new Lexeme(NOT,lineNumber);
	else if (toUpper(token)=="RETURN")  return new Lexeme(RETURN,lineNumber);
	else if (toUpper(token)=="TRUE")  return new Lexeme(BOOLEAN,lineNumber,true);
	else if (toUpper(token)=="FALSE")  return new Lexeme(BOOLEAN,lineNumber,false);
		//must be a variable!
	return new Lexeme(VARIABLE,lineNumber,token);
}

Lexeme* decNumber() {
	string token = "";
	while (isdigit(ch)) {
		token = token + ch;
		getChar();
	}
	pushBack();
	return new Lexeme(REAL,lineNumber, stof('.'+token));
}

Lexeme* lexNumber() {
	string token = "";
	bool real;
	if(ch=='.') {
		real=true;
	}
	else real=false;
	while (isdigit(ch)||ch=='.') {
		token = token + ch;
		if(ch=='.') real=true;
		getChar();
	}
	pushBack();
	if(real)
		return new Lexeme(REAL,lineNumber, stof(token));
	return new Lexeme(INTEGER,lineNumber, stoi(token));
}

Lexeme* lexString() {
	string token = "";
	getChar();
	while (ch!='"') 
	{
		token = token + ch;
		getChar();
	}
	return new Lexeme(STRING,lineNumber, token);
}