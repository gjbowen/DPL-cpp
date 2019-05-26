//////////////////////
#include "helper.h" //
//////////////////////
void print(string message){cout<<message<<endl;}
void print_red(string message){cout << "\033[1;31m"<<message<<"\033[0m\n";}
void print_green(string message){cout << "\033[1;32m"<<message<<"\033[0m\n";}
void print_blue(string message){cout << "\033[1;34m"<<message<<"\033[0m\n";}
string toUpper(string str)
{
	for(int i=0;str[i]!=0;i++)
		if(str[i]<='z' && str[i]>='a')
		str[i]-=32;
	return str;
}
string toString(char x){
	string s(1, x);
	return s;
}
