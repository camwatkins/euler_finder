#ifndef MAIN_H_
#define MAIN_H_

//#define _DEBUG_

//define operator types
enum op
{
	AND = 3,
	OR = 2,
	OPEN_PARA = 4,
	CLOSE_PARA = 5,
	NO_OP = 0,
};

//returns and operator type based on a character
op getOperator(char test);
char opToChar(op curOp);

#define MAX_EDGES_PER_NODE 2

#endif /* MAIN_H_ */
