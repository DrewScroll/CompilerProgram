#include "stdafx.h"
#include "SemanticAnalyzer.h"

Compilador::SemanticAnalyzer::SemanticAnalyzer()
{
}

Compilador::SemanticAnalyzer::~SemanticAnalyzer()
{
}

vector<Compilador::Token*> Compilador::SemanticAnalyzer::infix2PostFix(vector<Token*> T)
{
	vector <Token*>Res;
	int iParenthesis = 0;
	stack<Token*> Operators;
	PREDOMINANCIA temp = UNDEFINED;
	for (int i = 0; i < T.size(); i++)
	{
		if (T[i]->getLex() == "(" || T[i]->getLex() == ")")
		{
			if (T[i]->getLex() == "(")
			{
				Operators.push(T[i]);
				++iParenthesis;
			}
			else
			{
				--iParenthesis;
				while (!Operators.empty() && Operators.top()->getLex() != "(")
				{
					Res.push_back(Operators.top());
					Operators.pop();
				}
				if (!Operators.empty() && Operators.top()->getLex() == "(")
				{
					Operators.pop();
				}
				else
				{
					//addError
				}
			}
		}
		else if (T[i]->getLex() == "+" || T[i]->getLex() == "-")
		{
			if (temp == PLUS_MINUS)
			{
				Res.push_back(Operators.top());
				Operators.pop();
			}
			else if (temp > PLUS_MINUS)
			{
				while (!Operators.empty() && Operators.top()->getLex() != "(")
				{
					Res.push_back(Operators.top());
					Operators.pop();
				}
			}
			temp = PLUS_MINUS;
			Operators.push(T[i]);
		}
		else if (T[i]->getLex() == "*" || T[i]->getLex() == "/")
		{
			if (temp == MUL_DIV)
			{
				Res.push_back(Operators.top());
				Operators.pop();
			}
			Operators.push(T[i]);
			temp = MUL_DIV;
		}
		else
		{
			Res.push_back(T[i]);
		}
	}
	while (!Operators.empty())
	{
		Res.push_back(Operators.top());
		Operators.pop();
	}
	if (iParenthesis != 0)
	{
		//addError
	}
	return Res;
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

