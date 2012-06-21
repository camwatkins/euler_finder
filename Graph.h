#ifndef GRAPH_H_
#define GRAPH_H_
#include <vector>
#include <string>
#include <list>

#include "EulerPath.h"

using namespace std;

class Graph {
public:
	Graph();
	~Graph();

	//returns a vector of all possible Euler paths
	list<EulerPath> getEulerPaths(string &RPNExp);

	//generates a graph based on an RPN expression and stores it in "nodes"
	void generateGraphOnRPN(string &RPNExp);

	//transversal functions
	EulerPath ruleA();
	void transA(Node *n, EulerPath *path);
	EulerPath ruleC();
	void transC(Node *n, EulerPath *path);

	//top of the graph
	Node *graphTop;
	list<Node*> andGates;
};

#endif /* GRAPH_H_ */
