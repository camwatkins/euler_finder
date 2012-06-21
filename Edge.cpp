#include "Edge.h"

//default constructor
Edge::Edge()
{
	id = 0;
}

//overloaded constructor
//takes and optional id parameter
Edge::Edge(char id_)
{
	id = id_;
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

bool Edge::operator==(const Edge &other) const
{
	if (this->id == other.id)
		return true;

	return false;
}

bool Edge::operator<(const Edge &other) const
{
	if (id < other.id)
		return true;

	return false;
}