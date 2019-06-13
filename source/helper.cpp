/////////////////////////////////
#include "../headers/helper.h" //
/////////////////////////////////
void print(string message){
    cout<<message<<endl;
}
void print_red(string message){
    cout << "\033[1;31m"<<message<<"\033[0m\n";
}
void print_green(string message){
    cout << "\033[1;32m"<<message<<"\033[0m\n";
}
void print_yellow(string message){
    cout << "\033[1;33m"<<message<<"\033[0m\n";
}
void print_blue(string message){
    cout << "\033[1;34m"<<message<<"\033[0m\n";
}
void print_magenta(string message){
    cout << "\033[1;35m"<<message<<"\033[0m\n";
}
void print_cyan(string message){
    cout << "\033[1;36m"<<message<<"\033[0m\n";
}
void print_white(string message){
    cout << "\033[1;37m"<<message<<"\033[0m\n";
}


void println(string message){
    print(message+"\n");
}
void println_red(string message){
    print_red(message+"\n");
}
void println_green(string message){
    print_green(message+"\n");
}
void println_yellow(string message){
    print_yellow(message+"\n");
}
void println_blue(string message){
    print_blue(message+"\n");
}
void println_magenta(string message){
    print_magenta(message+"\n");
}
void println_cyan(string message){
    print_cyan(message+"\n");
}
void println_white(string message){
    print_white(message+"\n");
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