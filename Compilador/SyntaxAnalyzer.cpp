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
	bool functProcessed = false;
	bool procProcessed = false;
	bool mainProcessed = false;
	const Token* t = Lexico->getNextToken();
	while (t != NULL) {
		if (!t->getLex().compare("var"))
		{
			checkVars();
			varsProcessed = true;
			if (mainProcessed || functProcessed || procProcessed)
			{
				//addError(t->getLineNumber(), SYN_ERROR_)
			}
		}
		else if (!t->getLex().compare("function"))
		{
			checkFunct();
			functProcessed = true;
			if (mainProcessed)
			{
				//addError
			}
		}
		else if (!t->getLex().compare("procedure"))
		{
			checkProc();
			procProcessed = true;
			if (mainProcessed)
			{
				//addError
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

void Compilador::SyntaxAnalyzer::checkDimension()
{
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

void Compilador::SyntaxAnalyzer::checkProc()
{
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
