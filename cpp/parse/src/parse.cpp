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




	get_char();
	while(lex != '\n'){

		if (B())
		{
				cout<<"syntax correct"<<endl;
				cout << "boolean statement evaluation: "<< endl;
		}
		else
		{
			cout<<"syntax error"<<endl;
			break;
		}


		cin.get(lex);

	}
	return 0;
}
