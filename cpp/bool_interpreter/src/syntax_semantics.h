/*
 * syntax.h
 *
 *  Created on: Oct 27, 2016
 *      Author: David Thompson
 */

#ifndef SYNTAX_SEMANTICS_H_
#define SYNTAX_SEMANTICS_H_
using namespace std;

char lex;
char a0,a1;
std::stack<char> s;

bool B();			// bool statement
bool IT();			// Imply Term
bool OT(); 			//: Or term
bool AT();			// And term
bool IT_Tail();		// : Imply tail
bool OT_Tail();		// : Or tail
bool AT_Tail();		// : And tail
bool L(); 			// Literal
bool A();			//Atom

void get_char(void)
{
	cin.get(lex);
	while(lex == ' ')
		cin.get(lex);
}




//Syntax Definitions

//Imply term



//Atom
bool A(){
	if (lex == 'T'||lex == 'F')
	{
		s.push(lex);
		get_char();
		return true;
	}
	else if (lex == '(')
	{
		get_char();
		if (IT())
		{
			if (lex == ')')
			{
				get_char();
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

bool L()
{
	if (A())
		return true;
	else if (lex == '~')
	{
		get_char();
		if (L())
		{

//semantic eval of NEGATION

			a0 = s.top();
			s.pop();
			if (a0 == 'T')
				s.push('F');
			else
				s.push('T');

			return true;
		}
		else
			return false;
	}
	else
		return false;

}

bool AT_Tail()
{

	if (lex == '^')
		{
		get_char();
		if (L())
		{
//semantic eval of AND

			a0 = s.top();
			s.pop();
			a1 = s.top();
			s.pop();

			if (a0 == 'T'&&a1 == 'T')
				s.push('T');
			else
				s.push('F');

			if (AT_Tail())
				return true;
			else
				return false;
		}
		else
			return false;
		}

	else if (lex == '.'||lex == ')'||lex == '-'||lex == 'v')
		return true;
	else
		return false;
}


bool AT()
{
	if (L())
			if (AT_Tail())
				return true;
			else
				return false;
		else
			return false;
}

bool OT_Tail()
{

	if (lex == 'v')
		{
		get_char();
		if (AT())
		{
//semantic eval of OR

			a0 = s.top();
			s.pop();
			a1 = s.top();
			s.pop();

			if (a0 == 'T'||a1 == 'T')
				s.push('T');
			else
				s.push('F');

			if (OT_Tail())
				return true;
			else
				return false;
		}
		else
			return false;
		}

	else if (lex == '.'||lex == ')'||lex == '-')
		return true;
	else
		return false;
}


bool OT()
{
	if (AT())
	{
			if (OT_Tail())
				return true;
			else
				return false;
	}
		else
			return false;
}

bool IT_Tail()
{
	if (lex == '-')
	{
		get_char();
		if (lex == '>')
		{
			get_char();
			if (OT())
			{
//semantic eval of IMPLY

			a0 = s.top();
			s.pop();
			a1 = s.top();
			s.pop();

			if (a0 == 'F'&&a1 == 'T')
				s.push('F');
			else
				s.push('T');


				if (IT_Tail())

					return true;
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	else if (lex == '.'||lex == ')')
		return true;
	else
		return false;


}

bool IT()
{
	if (OT())
	{
		if (IT_Tail())
			return true;
		else
			return false;
	}
	else
		return false;

}

//start function
bool B()
{
	if (IT())
	{
		if (lex == '.')
			return true;
		else
			return false;
	}
	else
		return false;

}


#endif /* SYNTAX_SEMANTICS_H_ */
