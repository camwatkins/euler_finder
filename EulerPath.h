#ifndef EULERPATH_H_
#define EULERPATH_H_

#include <deque>
#include <sstream>

#include "Node.h"

using namespace std;

class EulerPath {
public:
	EulerPath();
	~EulerPath();

	void addNode(Node *node);
	Node nextNode();

	//sequence of the euler path
	deque<Node*> path;

	bool equals(EulerPath &other);
	bool operator==(const EulerPath &other);
	bool operator<(const EulerPath &other);

	friend ostream& operator<<(ostream& out, EulerPath &target);
};

#endif /* EULERPATH_H_ */
