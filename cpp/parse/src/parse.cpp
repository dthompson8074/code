//============================================================================
// Name        : parse.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	char lex = NULL;

	cin.get(lex);
	while(lex != '\n'){
		cin.get(lex);
	cout << lex<< endl; // prints !!!Hello World!!!
	}
	return 0;
}
