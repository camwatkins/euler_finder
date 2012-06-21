#include <string>
#include <stack>

#include "Parser.h"
#include "main.h"

using namespace std;

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

//takes a  logic expression and returns the dual of it (used for PMOS)
string Parser::getDual(string &logicExpression)
{
	string dualExpression;
	string::iterator it;	//iterator for logic expression

	//iterate through logic expression
	for (it = logicExpression.begin(); it < logicExpression.end(); it++)
	{
		//replace ANDs with ORs and ORs with ANDs
		if (*it == '.' || *it == '*')
			dualExpression.push_back('+');
		else if (*it == '+' || *it == '|')
			dualExpression.push_back('*');
		else
			dualExpression.push_back(*it);	//just add anything else
	}

	return dualExpression;
}

//takes a logic expession and returns an equivalent RPN expression
string Parser::getRPN(string &logicExpression)
{
	stack<op> opStack;		//operator stack
	string::iterator it;	//iterator for logic expression
	op curOp = NO_OP;

	string RPNExp = "";

	//iterate through logic expression
	for (it = logicExpression.begin(); it < logicExpression.end(); it++)
	{
		//skip whitespace
		if (*it == ' ')
			continue;

		//extract the operator if it exists
		curOp = getOperator(*it);

		if (curOp)	//operator encountered
		{
			if (curOp == OPEN_PARA)	//special case, just push to stack
			{
				opStack.push(curOp);
			}
			else if (curOp == CLOSE_PARA)	//pop everything up till last para
			{
				while (!opStack.empty() && opStack.top() != OPEN_PARA)
				{
					RPNExp.push_back(opToChar(opStack.top()));	//add popped operator to RPN expression
					opStack.pop();	//remove operator
				}

				// remove the open para
		//		if (opStack.top() == OPEN_PARA)
			//		opStack.pop();
			}
			else	//AND/OR operator encountered
			{
				//pop off items less than current operator
				while (!opStack.empty() && curOp <= opStack.top())
				{
					if (opStack.top() != OPEN_PARA && opStack.top() != CLOSE_PARA)
						RPNExp.push_back(opToChar(opStack.top()));	//add top operator to RPN expression

					opStack.pop();	//remove operator
				}

				//push the AND/OR operator
				opStack.push(curOp);
			}
		}
		else	//operand encountered
		{
			//check for garbage characters, abort if this is the case
			if (*it < (char)0x41 || *it > (char)0x5A)
				return "";

			RPNExp.push_back(*it);	//add operand to RPN expression
		}

	}

	//pop off any remaining items on stack and add to expression
	while (!opStack.empty())
	{
		RPNExp.push_back(opToChar(opStack.top()));
		opStack.pop();
	}

	return RPNExp;
}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}
