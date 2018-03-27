#include "stdafx.h"
#include "SemanticAnalyzer.h"

Compilador::SemanticAnalyzer::SemanticAnalyzer()
{
}

Compilador::SemanticAnalyzer::~SemanticAnalyzer()
{
}

void Compilador::SemanticAnalyzer::evaluateExpressions()
{
	for (auto it = mapExpLog.begin(); it != mapExpLog.end(); ++it)
	{
		ExpLogTree *t = new ExpLogTree(it->second);
		if (!t->evaluate())
		{
			//addError()
		}
	}

}

