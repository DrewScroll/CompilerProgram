#pragma once
#include "Token.h"
#include "ExpLogTree.h"
#include <map>
#include <vector>
#include <stack>

using namespace std;

namespace Compilador
{
	enum PREDOMINANCIA
	{
		UNDEFINED = 0,
		PLUS_MINUS,
		MUL_DIV
	};

	class SemanticAnalyzer
	{
	private:
		map <string, vector<Token*>> mapExpLog;
	public:
		SemanticAnalyzer();
		~SemanticAnalyzer();

		void addExpLog(string, vector<Token*>);
		vector<Token*> infix2PostFix(vector<Token*>);
		void evaluateExpressions();
	};
}
