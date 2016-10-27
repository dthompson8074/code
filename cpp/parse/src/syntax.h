/*
 * syntax.h
 *
 *  Created on: Oct 27, 2016
 *      Author: David Thompson
 */

#ifndef SYNTAX_H_
#define SYNTAX_H_
using namespace std;

char lex;

bool IT(){
	if (lex == 'T'||lex == 'F'||lex == '~'||lex == '(')
		return true;
	else
		return false;
}

bool B(){
	if (IT())
		return true;
	else
		cout<<"Error: was expecting '~','T','F','(' \n";
		return false;



}


#endif /* SYNTAX_H_ */
