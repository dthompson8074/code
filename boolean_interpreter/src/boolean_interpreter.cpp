//============================================================================
// Name        : bool_interpreter.cpp
// Author      : David Thompson
// Language    : C++
// Compiler    : GCC C++
// Description :Source File
//============================================================================

#include <iostream>
#include <stack>

#include "syntax_semantics.h"

using namespace std;


int main() {

	cout<<"Boolean Interpreter\n"<<"Enter Statement: ";

	get_char();

//Start Function
	if (B())
	{
			cout<<"Syntax Correct"<<endl;
			cout << "Boolean Statement Evaluation: "<< s.top()<< endl;
	}
	else
		cout<<"Syntax Error"<<endl;


	return 0;
}
