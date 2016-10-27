//============================================================================
// Name        : parse.cpp
// Author      : David Thompson
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <stack>
#include "syntax.h"



using namespace std;

int main() {


	cin.get(lex);



	while(lex != '\n'){
		if (B())
				cout<<"syntax correct";

		cout << lex<< endl;
		cin.get(lex);

	}
	return 0;
}
