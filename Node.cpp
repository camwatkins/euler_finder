#include <iostream>

#include "Node.h"
#include "main.h"

//default constructor
Node::Node()
{
	//init all to default values
	visited = false;

	left = NULL;
	right = NULL;
	edge = NULL;
	opType = NO_OP;
}

Node::Node(Edge *edge)
{
	//init all to default values
	visited = false;

	left = NULL;
	right = NULL;
	this->edge = edge;
	opType = NO_OP;
}

void Node::addEdge(Edge *edge)
{
	if (edge != NULL)
		this->edge = edge;
}

void Node::setLeftAdj(Node *node)
{
	if (node != NULL)
		this->left = node;
}

void Node::setRightAdj(Node *node)
{
	if (node != NULL)
		this->right = node;
}

void Node::setOperator(op opType)
{
	this->opType = opType;
}

void Node::setID(int id)
{
	this->id = id;
}

bool Node::operator==(const Node &other) const
{
	if (this->opType != NO_OP || other.opType != NO_OP)
		return true;

	if (*edge == *other.edge)
		return true;

	return false;
}

bool Node::operator<(const Node &other) const
{
	if (opType != NO_OP || other.opType != NO_OP)
		return (this->opType < other.opType);

	if (*edge < *other.edge)
		return true;

	return false;
}

Node::~Node()
{
	// TODO Auto-generated destructor stub
}
