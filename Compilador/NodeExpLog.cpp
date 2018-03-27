#include "stdafx.h"
#include "NodeExpLog.h"

bool Compilador::NodeExpLog::evaluate()
{
	if (node1 != nullptr)
	{
		node1->evaluate();
	}
	if (node2 != nullptr)
	{
		node2->evaluate();
	}
	if (node1 == nullptr && node2 == nullptr)
	{
		currentNodeRes =
	}
	else
	{
		RES_EXPLOGNODE r1 = node1->getResult();
		RES_EXPLOGNODE r2 = node2->getResult();
		if (nodeOperatorType == OP_ARIT)
		{

		}
		else if (nodeOperatorType == OP_LOG)
		{

		}
		else if (nodeOperatorType == OP_REL)
		{

		}
	}
}
