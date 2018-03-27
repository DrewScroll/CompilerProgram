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
			checkVars(GLOBAL_VAR);
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

Compilador::SyntaxAnalyzer::~SyntaxAnalyzer()
{
	delete Symbols;
}

bool Compilador::SyntaxAnalyzer::CheckSyntax()
{
	checkProgram();
	return (managedRef_errorsModule->NumErrorsSyn == 0);
}

void Compilador::SyntaxAnalyzer::checkVars(ENODE_CLASS nclass)
{
	const Token* t = Lexico->peekToken(0);
	map <std::string, int> temp;
	int dimen = 0;
	while ((t != nullptr) && (!t->getLex().compare("var")))
	{
		do {
			t = Lexico->getNextToken();
			string stemp;
			if (t->getType() == ID)
			{
				temp.insert(std::make_pair(t->getLex(), 0));
				stemp = t->getLex();
			}
			else
			{
				addErrorExpect(t->getLineNumber(), "id", t->getLex().c_str());
				stemp = "";
				//recoverFromError();
			}
			t = Lexico->getNextToken();
			if (!t->getLex().compare("["))
			{
				dimen = checkDimension();
				if (dimen > 0 && stemp != "")
				{
					auto it = temp.find(stemp);
					if (it != temp.end())
					{
						it->second = dimen;
					}
				}
				t = Lexico->getNextToken();
			}
		} while (!t->getLex().compare(","));
		if (t->getLex().compare(":"))
		{
			addErrorExpect(t->getLineNumber(), ":", t->getLex().c_str());
			//recoverFromError();
		}
		t = Lexico->getNextToken();
		checkType(temp, t, nclass);
		t = Lexico->getNextToken();
		if (t->getLex().compare(";"))
		{
			addErrorExpect(t->getLineNumber(), ";", t->getLex().c_str());
			//recoverError();
		}
		t = Lexico->getNextToken();
	}
}

void Compilador::SyntaxAnalyzer::checkType(map <std::string, int> vars, const Token* t, ENODE_CLASS nclass)
{
	if (!t->getLex().compare("int") || !t->getLex().compare("float") || !t->getLex().compare("bool") || !t->getLex().compare("string"))
	{
		for (auto it = vars.begin(); it != vars.end(); it++)
		{
			Symbols->AddSymbol(it->first, nclass, it->second, t->getLex(), "");
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
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
	if (!t->getLex().compare(")"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
	}
	if (!t->getLex().compare("{"))
	{
		checkBlock();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkSwitch()
{
	const Token* t = Lexico->getNextToken();
	bool isDefault = false, DefaultProc = false;
	if (!t->getLex().compare("("))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
	if (t->getType() == ID)
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_ID);
	}
	if (!t->getLex().compare(")"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
	}
	if (!t->getLex().compare("{"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}
	while (t->getLex().compare("}"))
	{
		t = Lexico->getNextToken();
		if (!t->getLex().compare("case"))
		{
			if (DefaultProc)
			{
				addError(t->getLineNumber(), SYN_ERR_DEFAULT_PROC);
			}
			t = Lexico->getNextToken();
			if (t->getType() == INT || t->getType() == STRING)
			{
				checkBlockSwitch();
			}
			else
			{
				addErrorExpect(t->getLineNumber(), "int o string", t->getLex().c_str());
			}
		}
		if (!t->getLex().compare("default") && !isDefault)
		{
			checkBlockSwitch();
			isDefault = true;
			DefaultProc = true;
		}
	}
}

void Compilador::SyntaxAnalyzer::checkWhile()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("while"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "while", t->getLex().c_str());
	}
	if (t->getLex().compare("("))
	{
		processExpression();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
	if (!t->getLex().compare(")"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
	}
	if (!t->getLex().compare("{"))
	{
		checkBlock();
	}
}

void Compilador::SyntaxAnalyzer::checkFor()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("for"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "for", t->getLex().c_str());
	}
	if (!t->getLex().compare("("))
	{
		t = Lexico->getNextToken();
		if (t->getType == ID)
		{
			t = Lexico->getNextToken();
			checkAssign();
			t = Lexico->getNextToken();
		}
		else
		{
			addErrorExpect(t->getLineNumber(), "id", t->getLex().c_str());
		}
	}
	processExpression();
	t = Lexico->getNextToken();
	checkInc_Dec();
	t = Lexico->getNextToken();
	if (!t->getLex().compare(")"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
	}
	if (!t->getLex().compare("{"))
	{
		checkBlock();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}
}

int Compilador::SyntaxAnalyzer::checkDimension()
{
	const Token* t = Lexico->getNextToken();
	t = Lexico->getNextToken();
	if (t->getType() == INT || !t->getLex().compare("]"))
	{
		if (t->getType() == INT)
		{
			return stoi(t->getLex());
		}
		else if (!t->getLex().compare("]"))
		{
			addError(t->getLineNumber(), SYN_ERR_NO_DIMEN);
		}
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_DIMEN);
	}
}

void Compilador::SyntaxAnalyzer::checkRead()
{
	const Token* t = Lexico->getNextToken();
	int dimen = 0;
	if (!t->getLex().compare("("))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
	processExpression();
	if (!t->getLex().compare(")"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
	}
	if (t->getLex().compare(";"))
	{
		addErrorExpect(t->getLineNumber(), ";", t->getLex().c_str());
	}
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
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("print"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "print", t->getLex().c_str());
	}
	if (!t->getLex().compare("("))
	{
		while (t != NULL && !t->getLex().compare(")") && !t->getLex().compare(";") && !t->getLex().compare("{"))
		{
			processExpression();
			t = Lexico->getNextToken();
			if (!t->getLex().compare(","))
			{
				t = Lexico->getNextToken();
			}
		}
		if (t->getLex().compare(")"))
		{
			addErrorExpect(t->getLineNumber, ")", t->getLex().c_str());
		}
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkIf()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("if"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "if", t->getLex().c_str());
	}
	if (t->getLex().compare("("))
	{
		processExpression();
		if (!t->getLex().compare(")"))
		{
			t = Lexico->getNextToken();
		}
		else
		{
			addErrorExpect(t->getLineNumber(), ")", t->getLex().c_str());
		}
		if (!t->getLex().compare("{"))
		{
			checkBlock();
		}
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "(", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkParam()
{
	const Token* t = Lexico->getNextToken();
	map <std::string, int> temp;
	int dimen = 0;
	while (t != NULL && !t->getLex().compare(")"))
	{
		do {
			string stemp;
			if (t->getType() == ID)
			{
				temp.insert(std::make_pair(t->getLex(), 0));
				stemp = t->getLex();
			}
			else
			{
				addErrorExpect(t->getLineNumber(), "id", t->getLex().c_str());
				stemp = "";
				//recoverFromError();
			}
			t = Lexico->getNextToken();
			if (!t->getLex().compare("["))
			{
				dimen = checkDimension();
				if (dimen > 0 && stemp != "")
				{
					auto it = temp.find(stemp);
					if (it != temp.end())
					{
						it->second = dimen;
					}
				}
				t = Lexico->getNextToken();
			}
		} while (!t->getLex().compare(","));
		if (t->getLex().compare(":"))
		{
			addErrorExpect(t->getLineNumber(), ":", t->getLex().c_str());
			//recoverFromError();
		}
		t = Lexico->getNextToken();
		checkType(temp, t, PARAM);
		t = Lexico->getNextToken();
		if (t->getLex().compare(";") && t->getLex().compare(")"))
		{
			addErrorExpect(t->getLineNumber(), ") o ;", t->getLex().c_str());
		}
	}
}

void Compilador::SyntaxAnalyzer::checkAssign()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("="))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "=", t->getLex().c_str());
	}
	processExpression();
	t = Lexico->getNextToken();
	if (!t->getLex().compare(";"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ";", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkProcFunc()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("function"))
	{
		checkFunct();
	}
	else
	{
		checkProc();
	}
}

void Compilador::SyntaxAnalyzer::checkProc()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getType == ID)
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_ID);
	}
	if (!t->getLex().compare("("))
	{
		checkParam();
		t = Lexico->getNextToken();
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_PARM);
	}
	if (!t->getLex().compare("{"))
	{
		checkBlock();
	}
	else
	{
		addError(t->getLineNumber, SYN_ERR_NO_BLOCK);
	}
}

void Compilador::SyntaxAnalyzer::checkFunct()
{
	map <std::string, int> temp;

	const Token* t = Lexico->getNextToken();
	if (t->getType() == ID)
	{
		temp.insert(std::make_pair(t->getLex(), 0));
		t = Lexico->getNextToken();
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_ID);
	}
	if (!t->getLex().compare("("))
	{
		checkParam();
		t = Lexico->getNextToken();
	}
	else
	{
		addError(t->getLineNumber(), SYN_ERR_NO_PARM);
	}
	if (!t->getLex().compare(":"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ":", t->getLex().c_str());
		//recoverFromError();
	}
	checkType(temp, t, FUNC);
	t = Lexico->getNextToken();
	if (!t->getLex().compare("{"))
	{
		checkBlock();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}

}

void Compilador::SyntaxAnalyzer::checkBlock()
{
	const Token *t = Lexico->getNextToken();

	if ((t->getLex().compare("var")))
	{
		checkVars(LOCAL_VAR);
	}

	while (t->getLex().c_str() != "}")
	{
		t = Lexico->getNextToken();
		if (isStatement())
		{
			checkStatement();
		}
	}
}

void Compilador::SyntaxAnalyzer::checkReturn()
{
	const Token* t = Lexico->peekToken(0);
	if (t->getLex().compare("return"))
	{
		addErrorExpect(t->getLineNumber(), "return", t->getLex().c_str());
	}
	else
	{
		t = Lexico->getNextToken();
		if (t->getType() != ID || t->getType() != INT || t->getType() != FLOAT || t->getType() != STRING)
		{
			addError(t->getLineNumber(), SYN_ERR_RETURN);
		}
	}
}

void Compilador::SyntaxAnalyzer::checkListaImp()
{
}

bool Compilador::SyntaxAnalyzer::processExpression()
{
	const Token* t = Lexico->peekToken(0);
	vector <S_Nested_Level> nestedLevels;
	int currentNestedLevel = 0;
	int numErrors = 0;
	S_Nested_Level lvl0;
	nestedLevels.push_back(lvl0);
	checkEXPLOG(&nestedLevels, &currentNestedLevel, &numErrors);
	if (nestedLevels[currentNestedLevel].numOperands < 1)
	{
		addError(t->getLineNumber(), SYN_ERR_NO_OPERANDS);
		numErrors++;
	}
	if ((nestedLevels[currentNestedLevel].numOperators > 0)&&nestedLevels[currentNestedLevel].numOperands != (nestedLevels[currentNestedLevel].numOperators+1))
	{
		addError(t->getLineNumber(), SYN_ERR_NO_OPERATORS);
		numErrors++;
	}
	if (currentNestedLevel > 0)
	{
		addError(t->getLineNumber(), SYN_ERR_NO_PARENTHESIS);
		numErrors++;
	}
	return (numErrors == 0);
}

bool Compilador::SyntaxAnalyzer::isOperator(const Token * t)
{
	const Token* t = Lexico->peekToken(0);
	if (t->getType() == RELATIONAL_OPERATOR || t->getType() == ARITHMETIC_OPERATOR || t->getType == LOGICAL_OPERATOR)
	{
		return true;
	}
	return false;
}

bool Compilador::SyntaxAnalyzer::isConst(const Token * t)
{
	if (t->getType() == INT || t->getType() == FLOAT || t->getType() == LOGICAL_CONSTANT || t->getType() == STRING)
	{
		return true;
	}
	return false;
}

void Compilador::SyntaxAnalyzer::checkEXPLOG(vector <S_Nested_Level> *nestedLevels, int *currentNestedLevel, int *NumErrors)
{
	checkTerm(nestedLevels, currentNestedLevel, NumErrors);
	const Token* t = Lexico->getNextToken();
	if (isOperator(t))
	{
		nestedLevels->at(*currentNestedLevel).numOperators++;
		t = Lexico->getNextToken();
		checkEXPLOG(nestedLevels, currentNestedLevel, NumErrors);
	}
}

void Compilador::SyntaxAnalyzer::checkTerm(vector<S_Nested_Level>* nestedLevels, int * currentNestedLevel, int * NumErrors)
{
	const Token* t = Lexico->peekToken(0);
	bool negatedTerm = t->getType() == LOGICAL_UNARY_OPERATOR;
	if (negatedTerm)
	{
		t = Lexico->getNextToken();
	}
	if (t->getLex() == "(")
	{
		nestedLevels->at(*currentNestedLevel).numOperands++;
		(*currentNestedLevel)++;
		S_Nested_Level nextLvl;
		nestedLevels->push_back(nextLvl);
		t = Lexico->getNextToken();
		checkEXPLOG(nestedLevels, currentNestedLevel, NumErrors);
		if (t->getLex() == ")")
		{
			if (nestedLevels->at(*currentNestedLevel).numOperands<1)
			{
				addError(t->getLineNumber(), SYN_ERR_NO_OPERANDS);
				(*NumErrors)++;
			}
			if ((nestedLevels->at(*currentNestedLevel).numOperators > 0) && nestedLevels->at(*currentNestedLevel).numOperands != (nestedLevels->at(*currentNestedLevel).numOperators + 1))
			{
				addError(t->getLineNumber(), SYN_ERR_NO_OPERATORS);
				(*NumErrors)++;
			}
			(*currentNestedLevel)--;
		}
	}
	else if (isConst(t))
	{
		if (negatedTerm && t->getType() != LOGICAL_CONSTANT)
		{
			addError(t->getLineNumber(), SYN_ERR_NEGATE);
		}
		nestedLevels->at(*currentNestedLevel).numOperands++;
	}
	else if (t->getType() == ID)
	{
		ENODE_CLASS nclass = Symbols->getSymbolClass(t->getLex());
		if (nclass == PROC)
		{
			addError(t->getLineNumber(), SYN_ERR_CALL_PROC_EXP);
		}
		else if (nclass == FUNC)
		{
			checkCallProcFunc();
		}
		nestedLevels->at(*currentNestedLevel).numOperands++;
	}
}

void Compilador::SyntaxAnalyzer::checkInc_Dec()
{
	const Token* t = Lexico->peekToken(0);
	const Token* n = Lexico->getNextToken();
	if (t != n)
	{
		addErrorExpect(n->getLineNumber(), t->getLex().c_str(), n->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkStatement()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("if"))
	{
		checkIf();
	}
	else if (t->getLex().compare("while"))
	{
		checkWhile();
	}
	else if (!t->getLex().compare("for"))
	{
		checkFor();
	}
	else if (!t->getLex().compare("switch"))
	{
		checkSwitch();
	}
	else if (!t->getLex().compare("read"))
	{
		checkRead();
	}
	else if (!t->getLex().compare("print"))
	{
		checkPrint();
	}
	else if (!t->getLex().compare("return"))
	{
		checkReturn();
	}
	else if (t->getType() == ID)
	{
		t = Lexico->getNextToken();
		if (!t->getLex().compare("="))
		{
			checkAssign();
		}
		else if (!t->getLex().compare("("))
		{
			checkCallProcFunc();
		}
	}
}

void Compilador::SyntaxAnalyzer::checkCallProcFunc()
{
	const Token* t = Lexico->getNextToken();
	while (t != NULL && !t->getLex().compare(")") && !t->getLex().compare(";"))
	{
		processExpression();
		t = Lexico->getNextToken();
		if (!t->getLex().compare(","))
		{
			t = Lexico->getNextToken();
		}
	}
	if (t->getLex().compare(")"))
	{
		addErrorExpect(t->getLineNumber, ")", t->getLex().c_str());
	}
}

void Compilador::SyntaxAnalyzer::checkBlockSwitch()
{
	const Token* t = Lexico->getNextToken();
	if (!t->getLex().compare(":"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), ":", t->getLex().c_str());
	}
	if (!t->getLex().compare("{"))
	{
		t = Lexico->getNextToken();
	}
	else
	{
		addErrorExpect(t->getLineNumber(), "{", t->getLex().c_str());
	}
	while (t->getLex().compare("}"))
	{
		if (isStatement())
		{
			checkStatement();
		}
	}
}

bool Compilador::SyntaxAnalyzer::isStatement()
{
	const Token* t = Lexico->peekToken(0);
	if (!t->getLex().compare("if") || !t->getLex().compare("while") || !t->getLex().compare("for") || !t->getLex().compare("switch") || !t->getLex().compare("read") || !t->getLex().compare("print") || !t->getLex().compare("return") || t->getType() == ID)
		return true;
	return false;
}
