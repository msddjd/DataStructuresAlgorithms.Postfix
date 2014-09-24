#include <cstring>
#include <string>
#include "stack.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <vector>

using namespace std;
using namespace boost;

bool iscorrect(string input);
void evaluate (string input);

stack<int> mystack(15);


void print(vector <string> & v);
void det_case(string input);
void push_numb(int x);
void perform_op(char op);
class DivisionByZero{};

int main()
{
	
	char command = '-';
	string input = "";
	bool again = false;

	do{
		cout << "\n\t\t\t\t\t:) :) :) :) :) :) :) :) :)\tTHE POSTFIX EVALUATOR\t:) :) :) :) :) :) :) :) :)\n" << endl;
		cout << "Enter a PostFix Mathmatical Expression: ";
		getline(cin,input);

		if(iscorrect(input))
		det_case(input);
	
		cout << "\nGo Again? (Y/N) ";
		cin >> command;
		switch (command)
		{	case 'Y':
			again = true;
			mystack.makeEmpty(); //clear stack
			break;
			case 'N':
			again = false;
			break;
			default:
			cout << "Incorrect entry, now Exiting" << endl;
			again = false;
			break;
		}
	}while(again);

	return 0;
	
}


bool iscorrect(string input)
{
	int index;
	int non_space_chars_checked = 0;
	int int_count = 0;

	bool validity = false;
	

	//Check if last char is a semicolon
	if( input.at( input.length()-1 ) == ';')
	validity = true;
	else
	{cout << "You Forgot your semicolon" << endl;	
	return false;}


	//Check for Appropriate Chars
	index = 0;
	do
	{
		switch(input.at(index))
		{	case' ':
			case'+':
			case'-':
			case'*':
			case'/':
			case'%':
			case'_':
			case';':
			validity = true;
			index++;
			break;
	
			default:
				if( isdigit( input.at(index) ) )
				validity = true;
				else
				{cout << "Exception -- You have enetered an unnacepptable character. Now Exiting" << endl;
				return false;}
	
				index++;
			break;
		}
	}while(index < input.length() );
	 
	//Checking if first two chars are operands
	index = 0;
	while( (int_count < 2) && (non_space_chars_checked < 2) && (index < input.length()) )
	{	

		while( ( input.at(index) == ' ') || ( input.at(index) == '_' ) ) //skip spaces and underscores until we get to non space/underscore
		{	index++; }

		if( !isdigit(input.at(index)) ) //If char at current index is not a digit
		{non_space_chars_checked++;
		index++;}

		if( isdigit(input.at(index)) ) //If char at current index is a digit
		{int_count++;
		index++;
		non_space_chars_checked++;}
	}
	//stop when we've counted 2 ints or when we've checked the first 2 non space chars, whichever comes first. 
	if(int_count >= 2)
	validity = true;
	else if(non_space_chars_checked >= 2)
	{validity = false;
	cout << "First two non-space chars are not integers thus your postfix expression will cause a stack underflow" << endl;}

	return validity;
}


//Print out a vector
void print(vector <string> & v)
{
	for (size_t n = 0; n < v.size(); n++)
	cout << "\"" << v[n] << "\"\n";
	cout << endl;
}


void det_case(string input)
{
	//Method to determine what case each field is and send it to an appropriate method to be handled
	vector <string> fields;

	split( fields, input, is_any_of(" ") );


	//Convert split fieldsto a c string so that they can be converted to an int
	//	int a = atoi( fields[0].c_str() );
	//	int b = atoi( fields[1].c_str() );



	int v_index,s_index,a;
	bool alldigit;
	string stemp = "";
	for(v_index = 0; v_index < fields.size(); v_index++)
	{
		stemp = fields[v_index];
		alldigit = true;
		
		//Case that a field consist of only integers
		if( stemp.at(stemp.length()-1) != ';' )//if current field does not contain the semicolon check whole field
		for(s_index = 0; s_index < stemp.length(); s_index++)
		{	if( !isdigit( stemp.at(s_index) ) ) //If any char is not a digit
			alldigit = false; }


		if( stemp.at(stemp.length()-1) == ';' ) //if current field contains the semicolon, exclude semicolon when checking
			for(s_index = 0; s_index < stemp.length()-1; s_index++)
			{	if( !isdigit( stemp.at(s_index) ) ) //If any char is not a digit
				alldigit = false; }

		if(alldigit)
		push_numb( atoi (stemp.c_str()) );
	
		//Case that a field consists of only an operation
		if(stemp.length() == 1)
		{	 switch ( stemp.at(0) )
			{	case'+':
				case'-':
				case'*':
				case'/':
				case'%':
				perform_op(stemp.at(0));	
				break;

				default:
				break;
				
			}
		}

		//If the length is 2 and the field consists of a operation followed by a semicolon example +;
		if( (stemp.length() == 2) && (stemp.at(1) == ';') )
		{	 switch ( stemp.at(0) )
			{	case'+':
				case'-':
				case'*':
				case'/':
				case'%':
				perform_op(stemp.at(0));	
				break;

				default:
				break;
			}
		}

		
		//If the length is 2 and the field consists of a underscore followed by a int;
		if( (stemp.length() == 2) && (stemp.at(0) == '_') )
		{
				 
			a = stemp.at(1) - '0'; //Converting single char to int
			push_numb(a*-1);	
			
		}

		//Finally send the semicolon if this field contains the semicolon
		if( stemp.at( stemp.length()-1) == ';' )
		perform_op(stemp.at(stemp.length()-1));

	}
		fields.clear();	
}	

void push_numb(int x)
{
	cout << "Token = " << x << "\tpush " << x << endl;
	mystack.push(x);

}

void perform_op(char op) //Operation comming in should only be a single char
{

	int result;
	switch (op)
	{	case'+':
		case'-':
		case'*':
		case'/':
		case'%':
		{	cout << "Token = " << op;
			int b = mystack.top();
			cout << "\tPop " << b;
			mystack.pop();
			int a = mystack.top();
			cout << "\tPop " << a;
			mystack.pop();	
			cout << "\tPush ";
			if(op == '+')
				{result = a + b;
				mystack.push(result);
				cout << result;}
			if(op == '-')
				{result = a - b;
				mystack.push(result);
				cout << result;}
			if(op == '*')
				{result = a * b;
				mystack.push(result);
				cout << result;}
			if(op == '/')
				{
				    try
					{ 
						if(b == 0)
						throw DivisionByZero();
						else
						{result = a / b; 
						mystack.push(result);
						cout << result;}
					}
					catch (DivisionByZero exc)
					 { cout << "\nDivision By Zero Exception -- Now Exiting." << endl;	
						exit(1);	 }
				}
			if(op == '%')
				{result = a % b;
				mystack.push(result);
				cout << result;}

			cout << endl;
		}
		break;

		case ';':
		cout << "Token = " << op << "\tPop " <<  mystack.top() << endl;
		break;


	}

}

