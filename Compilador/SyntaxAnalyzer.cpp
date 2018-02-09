#include "stdafx.h"
#include "SyntaxAnalyzer.h"


void Compilador::SyntaxAnalyzer::checkProgram()
{
	const Token* t = Lexico->getNextToken();
	if (t->getLex().compare("var"))
	{
		checkVars();
	}
	else if ((t->getLex().compare("function"))|| (t->getLex().compare("procedure")))
	{
		checkFuncProc();
	}
	else if (t->getLex().compare("main"))
	{
		checkMain();
	}
}

Compilador::SyntaxAnalyzer::SyntaxAnalyzer(ErrorsModule ^ err, LexAnalyzer* lex)
{
	managedRef_errorsModule = err;
	Lexico = lex;
}

bool Compilador::SyntaxAnalyzer::CheckSyntax()
{
	checkProgram();
	return (managedRef_errorsModule->NumErrorsSyn == 0);
}

void Compilador::SyntaxAnalyzer::checkVars()
{
}

void Compilador::SyntaxAnalyzer::checkFuncProc()
{
}

void Compilador::SyntaxAnalyzer::checkMain()
{
}
