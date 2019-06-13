/////////////////////////////////
#include "../headers/helper.h" //
/////////////////////////////////
void print(string message){
	cout<<message<<endl;
}
void print_red(string message){
    cout<<message<<endl;
}
void print_green(string message){
    cout<<message<<endl;
}
void print_yellow(string message){
    cout<<message<<endl;
}
void print_blue(string message){
    cout<<message<<endl;
}
void print_magenta(string message){
    cout<<message<<endl;
}
void print_cyan(string message){
    cout<<message<<endl;
}
void print_white(string message){
    cout<<message<<endl;
}
string toUpper(string str){
	for(int i=0;str[i]!=0;i++)
		if(str[i]<='z' && str[i]>='a')
		str[i]-=32;
	return str;
}
string toString(char x){
	string s(1, x);
	return s;
}