#include <deque>

#include "EulerPath.h"
#include "Node.h"

EulerPath::EulerPath() {
	// TODO Auto-generated constructor stub

}

EulerPath::~EulerPath() {
	// TODO Auto-generated destructor stub
}

void EulerPath::addNode(Node *node)
{
	path.push_back(node);
}

bool EulerPath::equals(EulerPath &other)
{
	int i = 0;
	for (deque<Node*>::iterator it = path.begin(); it != path.end(); it++)
	{
	//	Node temp = *other.path.at(i);
		if ((*it)->opType == NO_OP || other.path.at(i)->opType == NO_OP)
			return true;

		if (!(**it == *other.path.at(i)))
			return false;

		i++;
	}

	return true;
}

bool EulerPath::operator==(const EulerPath &other)
{
	int i = 0;
	for (deque<Node*>::iterator it = path.begin(); it != path.end(); it++)
	{
	//	Node temp = *other.path.at(i);

		if (!(**it == *other.path.at(i)))
			return false;

		i++;
	}

	return true;
}

bool EulerPath::operator<(const EulerPath &other)
{
	int i = -1;
	for (deque<Node*>::iterator it = path.begin(); it != path.end(); it++)
	{
		i++;
		if (*it < other.path.at(i))
			return true;
		else if (*it == other.path.at(i))
			continue;
		else
			return false;
	}

	return false;
}

ostream& operator<<(ostream& out, EulerPath &target)
{
	for (deque<Node*>::iterator it = target.path.begin(); it != target.path.end(); it++)
	{
		if((*it)->opType == NO_OP)
		{
			//print IDS
			out << (*it)->edge->id;
		}

	}

	return out;
}
