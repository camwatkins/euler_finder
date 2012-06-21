#include <list>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#include "EulerPath.h"
#include "Parser.h"
#include "Graph.h"

using namespace std;

int main(int argc, const char* argv[])
{
	Parser parser;	//on stack
	Graph graphNMOS;	//on stack
	Graph graphPMOS;	//on stack
	string logicExpression = "";
	string logicExpressionDual = "";
	string RPNExp = "";
	string RPNExpDual = "";
	string::iterator it;

	//stores all possible euler paths for NMOS and PMOS
	list<EulerPath> pathsNMOS;
	list<EulerPath> pathsPMOS;
	list<EulerPath> pathsFull;

	//main processing loop
	while (1)
	{
		//init back to default values
		logicExpression = "";
		logicExpressionDual = "";
		RPNExp = "";
		RPNExpDual = "";
		pathsNMOS.clear();
		pathsPMOS.clear();
		pathsFull.clear();

		cout << "Please enter a logic expression (type \"quit\" to exit):" << endl;
		getline(cin, logicExpression);

//		logicExpression = "(A+B+C)";
		//exit
		if (logicExpression == "quit")
			return 0;

		//ignore length 0 expressions
		if (logicExpression.size() < 1)
			continue;

		//get the dual of the logic expression for (PMOS)
		logicExpressionDual = parser.getDual(logicExpression);

		//retrieve the RPN expression from the logic expression (NMOS)
		RPNExp = parser.getRPN(logicExpression);

		//retrieve the dual of the RPN expression from the logic expression (PMOS)
		RPNExpDual = parser.getRPN(logicExpressionDual);

		if (RPNExp == "" || RPNExpDual == "")	//check for garbage in expression
		{
			cout << "Expression could not be parsed, please try again." << endl;
			continue;
		}

		cout << "\nLogic Expression: " << logicExpression << endl;
		cout << "Logic Expression Dual: " << logicExpressionDual << endl;
		cout << "RPN Expression: " << RPNExp << endl;
		cout << "RPN Expression Dual: " << RPNExpDual << endl;

		pathsNMOS = graphNMOS.getEulerPaths(RPNExp);
		pathsPMOS = graphPMOS.getEulerPaths(RPNExpDual);

		//find duplicates and add them to paths full
		for (list<EulerPath>::iterator itP = pathsPMOS.begin(); itP != pathsPMOS.end(); itP++)
		{
			for (list<EulerPath>::iterator itN = pathsNMOS.begin(); itN != pathsNMOS.end(); itN++)
			{
			//	if (*itP == *itN)
					pathsFull.push_back(*itP);
			}
		}

		pathsFull.sort();

		pathsFull.unique();

		pathsFull.pop_front();
		cout << "\nPossible Euler path: " << pathsFull.front() << endl;
		cout << endl;

	}

	return 0;
}

//takes a char and returns an operator based on the char
//if no operator can be found, it returns NO_OP
op getOperator(char test)
{
	op curOp;

	//extract operator if it exists
	if (test == '.')
		curOp = AND;
	else if (test == '*')
		curOp = AND;
	else if (test == '+')
		curOp = OR;
	else if (test == '|')
		curOp = OR;
	else if (test == '(')
		curOp = OPEN_PARA;
	else if (test == ')')
		curOp = CLOSE_PARA;
	else
		curOp = NO_OP;

	return curOp;
}

char opToChar(op curOp)
{
	if (curOp == AND)
		return '*';
	else if (curOp == OR)
		return '+';
	else if (curOp == CLOSE_PARA)
		return ')';
	else if (curOp == OPEN_PARA)
		return '(';

	return (char)0;
}
