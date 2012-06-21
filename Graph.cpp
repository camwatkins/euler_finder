#include <stack>
#include <iostream>
#include <list>

#include "Node.h"
#include "EulerPath.h"
#include "main.h"
#include "Graph.h"

using namespace std;

Graph::Graph()
{
	// TODO Auto-generated constructor stub

}

list<EulerPath> Graph::getEulerPaths(string &RPNExp)
{
	list<EulerPath> eulerPaths;

	//generate the graph first
	generateGraphOnRPN(RPNExp);

	//iterate over and gates swapping them
	for (list<Node*>::iterator it2 = andGates.begin(); it2 != andGates.end(); it2++)
	{
		//twist ANDs
		Node *temp = (*it2)->left;
		(*it2)->left = (*it2)->right;
		(*it2)->right = temp;

		for (list<Node*>::iterator it = it2; it != andGates.end(); it++)
		{
			//twist ANDs
			Node *temp = (*it)->left;
			(*it)->left = (*it)->right;
			(*it)->right = temp;

			eulerPaths.push_back(ruleA());
			eulerPaths.push_back(ruleC());
		
			//remove redudances
			eulerPaths.sort();
			eulerPaths.unique();
		}
	}

#ifdef _DEBUG_
/*	for (list<EulerPath>::iterator it = eulerPaths.begin(); it != eulerPaths.end(); it++)
	{
		for (deque<Node*>::iterator dit = *it.path; dit != *it.path.end(); dit++)
		{
			cout << *dit
		}
	}*/
#endif	

	return eulerPaths;
}

EulerPath Graph::ruleA ()
{
	EulerPath EPath;

	transA(graphTop, &EPath);

	return EPath;
}

void Graph::transA (Node *n, EulerPath *path)
{
	if (n->left != NULL)
		transA(n->left, path);
	if (n->right != NULL)
		transA(n->right, path);

	if (n->edge != NULL)
		path->addNode(n);
}


EulerPath Graph::ruleC ()
{
	EulerPath EPath;

	transC(graphTop, &EPath);

	return EPath;
}

void Graph::transC (Node *n, EulerPath *path)
{
	if (n->right != NULL)
		transC(n->right, path);
	if (n->left != NULL)
		transC(n->left, path);

	if (n->edge != NULL)
		path->addNode(n);
}

void Graph::generateGraphOnRPN(string &RPNExp)
{
	string::iterator it;
	stack<Node*> nodeStack;
	Node *node1 = NULL;
	Node *node2 = NULL;
	static int id = 0;

#ifdef _DEBUG_
//	cout << "d***************************************b" << endl;
#endif
	for (it = RPNExp.begin(); it < RPNExp.end(); it++)
	{
		op curOp = getOperator(*it);	//get the operator type

		if (curOp)
		{
			//retrieve previous two nodes
			if (!nodeStack.empty())
			{
				node1 = nodeStack.top();
				nodeStack.pop();
			}
			else
				node1 = NULL;

			if (!nodeStack.empty())
			{
				node2 = nodeStack.top();
				nodeStack.pop();
			}
			else
				node2 = NULL;

			//build new node
			Node *newNode = new Node();
			newNode->setLeftAdj(node1);
			newNode->setRightAdj(node2);
			newNode->setOperator(curOp);
			newNode->id = id;

			//add to AND gate list if and
			if (curOp == AND)
				andGates.push_back(newNode);

			//push back onto stack
			nodeStack.push(newNode);

#ifdef _DEBUG_
			cout << "EL: " << newNode->left->id << " ER:" << newNode->right->id << " OP: " << newNode->opType << " ID: " << newNode->id << endl;
		//	cout << "*\tCombining nodes with: " << opToChar(curOp) << "\t\t*" << endl;
#endif
		}
		else	//variable
		{
			nodeStack.push(new Node(new Edge(*it)));
			nodeStack.top()->id = id;

#ifdef _DEBUG_
			cout << "*\tNew Node ID: " << nodeStack.top()->id << " edge: " << nodeStack.top()->edge->id << "\t\t\t*" << endl;
#endif
		}
		id++;
	}
#ifdef _DEBUG_
//	cout << "q***************************************p" << endl << endl;
#endif

	//store node element locally
	graphTop = nodeStack.top();

}

Graph::~Graph()
{
	// TODO Auto-generated destructor stub
}
