#include <string>
#include "stack.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct BetNode
{
	char info;
	BetNode* left;
	BetNode* right;
};


vector <char> postfix;
void in_to_post(string input);
bool higherPrecedence (char top, char input);
stack <char> mystack(60);
void post_to_tree(char currchar);
void pre_traversal(BetNode* t);



stack <BetNode*> BetStack(60);

int main()
{
	ifstream infile;
	infile.open("infix.dat");

	string content = "";
	int i;

	while(infile) //Open file get the first string
	{
			//get current line from file and store it in a string
			getline(infile,content);

			//Print out the original line from string
			cout << "\nOriginal:\t" << content << endl;
			in_to_post(content);

			//Print out postfix expression
			cout << "Postfix:\t";
			for (i = 0; i < postfix.size(); i++)
			cout <<	postfix[i];
			cout << endl;

			//Get each char from post fix expression & send it to a method to create the BET tree
			for (i = 0; i < postfix.size(); i++)
			post_to_tree( postfix[i] ); 

			//Once tree is constructed do a pre-traversal to get pre-fix printout
			//Top item on stack is root of our tree
			cout << "Prefix:\t\t";
			pre_traversal(BetStack.top());
			cout << endl <<endl;
			

			postfix.clear(); //Must clear vector so that it is ready for next line in file

			while( !mystack.isEmpty() ) //Must also clear the stack
			mystack.pop();	
		
			while( !BetStack.isEmpty() ) //Must also clear BET stack and free up allocated pointer memory.
			{delete	BetStack.top();
			BetStack.top() == NULL;
			BetStack.pop();	}
	

	}
		infile.close();


return 0;
}

void in_to_post(string input)
{
	int index = 0;
	char character = ' ';
	char top = ' ';

	for(int i = 0; i < input.length(); i++)
	{	character =  input.at(index);
		switch(character)
		{
			case'(':
			mystack.push(character);
			break;
	
			case ' ':		
			break;
	
			case '+': 
			case '-': 
			case '*': 
			case '/':
				{top = mystack.top();
				if ( higherPrecedence(top, character) )
				mystack.push(character);
				else
				postfix.push_back(character);}
			break;
	
			case ')':
				{ top = mystack.top();
					while(top != '(')
					{ postfix.push_back(top);
					  mystack.pop();
					  top = mystack.top(); 
					}
				}
			break;
			
			default:
				//If current char from our string is a digit add it to our expression
				if( isdigit(character) )	
				postfix.push_back(character);
				
			break;
		}
		index++;
	}


}

bool higherPrecedence (char top, char input)
{
	if(top == input)
	return true;
	if( (top == '*') || (top == '/') )
	return true;
	if( (top == '+') || (top == '-') )
		if( (input == '+') || (input == '-'))
			return true;
	if( top == '(' )
	return true;
	return false;
}

void post_to_tree(char currchar)
{

	BetNode* t;
	t = new BetNode;
	t -> info = currchar;

	if( isdigit(currchar) )
	BetStack.push(t);
	else
	{	t -> right = BetStack.top();
		BetStack.pop();
		t -> left = BetStack.top();
		BetStack.pop();
		BetStack.push(t);
	}


}


void pre_traversal(BetNode* t)
{

	if(t != NULL )
	{
		cout << t -> info;
		pre_traversal( t -> left );
		pre_traversal( t -> right);

	}

}
