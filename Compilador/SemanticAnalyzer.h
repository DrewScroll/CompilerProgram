#pragma once
#include "Token.h"
#include "ExpLogTree.h"
#include <map>
#include <vector>

using namespace std;

namespace Compilador
{
	class SemanticAnalyzer
	{
	private:
		map <string, vector<Token*>> mapExpLog;
	public:
		SemanticAnalyzer();
		~SemanticAnalyzer();

		void addExpLog(string, vector<Token*>);
		string infix2PostFix(vector<Token*>);
		void evaluateExpressions();
	};
}
