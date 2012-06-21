#ifndef PARSER_H_
#define PARSER_H_

#include <string>

using namespace std;

class Parser {
public:
	Parser();

	//returns the RPN expression of a string
	string getRPN(string &logicExpression);

	//returns the dual of a logic expression (used for PMOS)
	string getDual(string &logicExpression);

	virtual ~Parser();

private:

};

#endif /* PARSER_H_ */
