#include "stdafx.h"
#include "SyntaxAnalyzer.h"

void Compilador::SyntaxAnalyzer::addError(int lineNum, const char * desc)
{
	String ^ strDesc = gcnew String(desc);
	String ^ strLine = gcnew String("");

	managedRef_errorsModule->addError(Compilador::ERROR_PHASE::SYN_ANALYZER, lineNum, strDesc, strLine);
}

void Compilador::SyntaxAnalyzer::addErrorExpect(int lineNum, const char * e, const char * f)
{
	std::string wasExpected("Se esperaba ");
	std::string wasFound("se encontro ");
	std::string line;
	line += wasExpected + e + ", " + wasFound + f;
	addError(lineNum, line.c_str());
}

void Compilador::SyntaxAnalyzer::checkProgram()
{
	bool varsProcessed = false;
	bool functprocProcessed = false;
	bool Processed = false;
	bool mainProcessed = false;
	const Token* t = Lexico->getNextToken();
	while (t != NULL) {
		if (!t->getLex().compare("var"))
		{
			checkVars();
			varsProcessed = true;
			if (mainProcessed || functprocProcessed)
			{
				addError(t->getLineNumber(), SYN_ERR_PROFUNMAIN_B4_VAR);
			}
		}
		else if (!t->getLex().compare("function") || !t->getLex().compare("procedure"))
		{
			checkProcFunc();
			functprocProcessed = true;
			if (mainProcessed)
			{
				addError(t->getLineNumber(), SYN_ERR_MAIN_B4_PROCFUN);
			}
		}
		else if (!t->getLex().compare("main"))
		{
			if (mainProcessed != false)
			{
				addError(t->getLineNumber(), SYN_ERR_MULT_MAIN);
			}
			else
			{
				checkMain();
				mainProcessed = true;
			}
		}
	}
	if (mainProcessed == false)
	{
		addError(t->getLineNumber(), SYN_ERR_NO_MAIN);
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
	const Token* t = Lexico->peekToken(0);
	vector <std::string> temp;
	while ((t != nullptr) && (!t->getLex().compare("var")))
	{
		do {
			t = Lexico->getNextToken();
			if (t->getType() == ID)
			{
				temp.push_back(t->getLex());
			}
			else
			{
				addErrorExpect(t->getLineNumber(), "id", t->getLex().c_str());
				//recoverFromError();
			}
			t = Lexico->getNextToken();
			if (!t->getLex().compare("["))
			{
				checkDimension();
				t = Lexico->getNextToken();
			}
		} while (!t->getLex().compare(","));
		if (t->getLex().compare(":"))
		{
			addErrorExpect(t->getLineNumber(), ":", t->getLex().c_str());
			//recoverFromError();
		}
		t = Lexico->getNextToken();
		checkType(temp, t);
		t = Lexico->getNextToken();
		if (t->getLex().compare(";"))
		{
			addErrorExpect(t->getLineNumber(), ";", t->getLex().c_str());
			//recoverError();
		}
		t = Lexico->getNextToken();
	}
}

void Compilador::SyntaxAnalyzer::checkType(std::vector <std::string> vars, const Token* t)
{
	if (!t->getLex().compare("int")|| !t->getLex().compare("float")|| !t->getLex().compare("bool")||!t->getLex().compare("string"))
	{
		for (int i = 0; i < vars.size(); i++)
		{
			Symbols->AddSymbol(vars[i], GLOBAL_VAR, 0, t->getLex(), "");
		}
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "int, float, bool o string", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkMain()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getLex().compare("("))
	{
		t = Lexico->getNextToken();
		if (!t->getLex().compare(")"))
		{
			checkBlock();
		}
		else
		{
			addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
		}
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkSwitch()
{
}

void Compilador::SyntaxAnalyzer::checkWhile()
{
}

void Compilador::SyntaxAnalyzer::checkFor()
{
}

int Compilador::SyntaxAnalyzer::checkDimension()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getLex().compare("["))
	{
		t = Lexico->getNextToken();
		if (!t->getType() == INT || !t->getType() == DIMENSION_OPERATOR)
		{
			if (!t->getType() == INT)
			{
				return ;
			}
		}
		else
		{
			addError(t->getLineNumber(), SYN_ERR_DIMEN);
		}
	}
}

void Compilador::SyntaxAnalyzer::checkRead()
{
}

//Compilador::SyntaxState::SyntaxState()
//{
//}
//
//Compilador::SyntaxState::~SyntaxState()
//{
//}
//
//Compilador::SyntaxProgram::SyntaxProgram()
//{
//}
//
//Compilador::SyntaxProgram::~SyntaxProgram()
//{
//}
//
//void Compilador::SyntaxProgram::checkSyntax()
//{
//	while ()
//	{
//		SyntaxState* s = syntax->getSyntaxState(t->getLex());
//	}
//}
//
//Compilador::SyntaxVar::SyntaxVar()
//{
//}
//
//Compilador::SyntaxVar::~SyntaxVar()
//{
//}
//
//void Compilador::SyntaxVar::checkSyntax()
//{
//}

void Compilador::SyntaxAnalyzer::checkPrint()
{
}

void Compilador::SyntaxAnalyzer::checkIf()
{
}

void Compilador::SyntaxAnalyzer::checkParam()
{
}

void Compilador::SyntaxAnalyzer::checkAssign()
{
}

void Compilador::SyntaxAnalyzer::checkProcFunc()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getLex().compare("function"))
	{
		checkFunct();
	}
	else if (!t->getLex().compare("procedure"))
	{
		checkProc();
	}
	else
	{
		checkProcFunc();
	}
}

void Compilador::SyntaxAnalyzer::checkProc()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getType == ID)
	{
		Symbols->AddSymbol();
		t = Lexico->getNextToken();
		if (!t->getLex().compare("("))
		{
			checkParam();
			t = Lexico->getNextToken();
			if (!t->getLex().compare("{"))
			{
				checkBlockProcFunc();
			}
			else
			{
				addError(t->getLineNumber, SYN_ERR_NO_BLOCK);
			}
		}
		else
		{
			addError(t->getLineNumber(), SYN_ERR_NO_PARM);
		}

	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_ID);
	}
}

void Compilador::SyntaxAnalyzer::checkFunct()
{
}

void Compilador::SyntaxAnalyzer::checkBlock()
{
	
}

void Compilador::SyntaxAnalyzer::checkReturn()
{
}

void Compilador::SyntaxAnalyzer::checkListaImp()
{
}

void Compilador::SyntaxAnalyzer::checkEXPLOG()
{
}

void Compilador::SyntaxAnalyzer::checkInc_Dec()
{
}

void Compilador::SyntaxAnalyzer::checkBlockProcFunc()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("{"))
	{
		t = Lexico->getNextToken();
		if (!t->getLex().compare("var"))
		{
			checkVars();
			t = Lexico->getNextToken();
		}
		if (isStatement())
		{
			checkStatement();
			t = Lexico->getNextToken();
		}
		if (!t->getLex().compare("}"))
		{
			t = Lexico->getNextToken();
		}
		else
		{
			addErrorExpect(t->getLineNumber(), "}", t->getLex().c_str());
		}
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkStatement()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("if"))
	{
		checkIf();
	}
	if (t->getLex().compare("while"))
	{
		checkWhile();
	}
	if (!t->getLex().compare("for"))
	{
		checkFor();
	}
	if (!t->getLex().compare("switch"))
	{
		checkSwitch();
	}
	if (!t->getLex().compare("read"))
	{
		checkRead();
	}
	if (!t->getLex().compare("print"))
	{
		checkPrint();
	}
	if (!t->getLex().compare("return"))
	{
		t = Lexico->getNextToken();
		if (t->getType() != ID)
		{
			addErrorExpect(t->getLineNumber(), "id", t->getLex().c_str());
		}
		else
		{
			t = Lexico->getNextToken();
		}
		t = Lexico->getNextToken();
		if (t->getLex().compare(";"))
		{
			addErrorExpect(t->getLineNumber(), ";", t->getLex().c_str());
		}
	}
	if (!t->getLex().compare("procedure"))
	{
		checkCallProcFunc();
	}
}

void Compilador::SyntaxAnalyzer::checkCallProcFunc()
{
	const Token* t = Lexico->peekToken(0);
	Symbols->AddSymbol(t->getLex(),PROC,0,"procedure", );
}

bool Compilador::SyntaxAnalyzer::isStatement()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("if") || t->getLex().compare("while") || t->getLex().compare("for") || t->getLex().compare("switch") || t->getLex().compare("read") || t->getLex().compare("print") || t->getLex().compare("return") || t->getLex().compare("procedure") || t->getLex().compare("function"))
		return true;
	return false;
}
