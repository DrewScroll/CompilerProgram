#pragma once
#include "Token.h"
#include "NodeExpLog.h"
#include <vector>

using namespace std;

namespace Compilador
{
	class ExpLogTree
	{
	public:
		NodeExpLog * root;

		ExpLogTree(vector<Token*>);
		~ExpLogTree();

		bool evaluate();
	};
}
