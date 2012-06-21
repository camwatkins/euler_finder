#ifndef NODE_H_
#define NODE_H_

#include <vector>

#include "main.h"
#include "edge.h"

using namespace std;

class Node {
public:
	static unsigned char id_count;

	Node();
	Node(Edge *edge);

	virtual ~Node();

	void setLeftAdj(Node *node);
	void setRightAdj(Node *node);

	void addEdge(Edge *edge);
	void setOperator(op opType);
	void setID(int id);

	Edge *edge; 
	Node *left;
	Node *right;

	op opType;
	bool visited;
	int id;

	bool operator==(const Node &other) const;
	bool operator<(const Node &other) const;
};
#endif /* NODE_H_ */
