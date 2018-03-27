#pragma once
#include "Token.h"

namespace Compilador
{
	enum RES_EXPLOGNODE
	{
		RES_ARIT,
		RES_BOOL
	};

	enum OP_EXPLOGNODE
	{
		OP_ARIT,
		OP_REL,
		OP_LOG
	};

	class NodeExpLog
	{
	public:
		Token* nodeOperator, operand;
		NodeExpLog* node1;
		NodeExpLog* node2;

		RES_EXPLOGNODE expectedResNode1, expectedResNode2, currentNodeRes;
		OP_EXPLOGNODE nodeOperatorType;

		bool evaluate();
		NodeExpLog();
		~NodeExpLog();
	};
}
