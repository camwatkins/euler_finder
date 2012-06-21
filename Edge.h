/*
 * Edge.h
 *
 *  Created on: Jun 26, 2011
 *      Author: Jake
 */

#ifndef EDGE_H_
#define EDGE_H_

class Edge {
public:
	Edge();
	Edge(char id_);
	virtual ~Edge();

	char id;

	bool operator==(const Edge &other) const;
	bool operator<(const Edge &other) const;
};

#endif /* EDGE_H_ */
