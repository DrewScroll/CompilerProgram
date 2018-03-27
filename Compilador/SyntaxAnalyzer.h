#pragma once
#include "ErrorModule.h"
#include "LexAnalizer.h"
#include "Token.h"
#include "SymTab.h"
#include <vcclr.h>

//struct STOKENEXPECTED
//{
//	std::vector<TOKEN_TYPE> tokenType;
//	std::vector<std::string> tokensLex;
//	bool bRequired;
//	bool bRepeat;
//};

namespace Compilador
{
#define SYN_ERR_VAR_GLOBAL_DEFINED			"Var global ya definida"
#define SYN_ERR_VAR_LOCAL_DEFINED			"Var local ya definida"
#define SYN_ERR_VAR_SAME_NAME_PROCFUNC		"Var no se puede llamar igual que proc/func"
#define SYN_ERR_PARAM_DEFINED				"Parametro ya definido"
#define SYN_ERR_PROCFUNC_DEFINED			"Proc/Func ya definido"
#define SYN_ERR_SAME_NAME_PARAM				"Var local no se puede llamar igual que parametro"
#define SYN_ERR_NO_MAIN						"Main no localizada"
#define SYN_ERR_MULT_MAIN					"Multiples Mains existentes"
#define SYN_ERR_DIMEN						"Valor en la dimension no es un numero"
#define SYN_ERR_NO_DIMEN					"No contiene valor para dimension"
#define SYN_ERR_PROFUNMAIN_B4_VAR			"Procedure, Function o Main declarados anteriormente"
#define SYN_ERR_MAIN_B4_PROCFUN				"Main declarado anteriormente"
#define SYN_ERR_NO_ID						"ID no identificado o valido"
#define SYN_ERR_NO_PARM						"Parametros no identificados"
#define SYN_ERR_NO_BLOCK					"Bloque no identificado"
#define SYN_ERR_RETURN						"No hay valor aceptable para return"
#define SYN_ERR_DEFAULT_PROC				"Ya existe default dentro del Switch"
#define SYN_ERR_NO_OPERANDS					"La expresion no contiene operandos"
#define SYN_ERR_NO_OPERATORS				"La expresion tiene una cantidad mayor o menor de operadores"
#define SYN_ERR_NO_PARENTHESIS				"No se cerro parentesis en la expresion"
#define SYN_ERR_NEGATE						"Solo se puede negar constantes logicas"
#define SYN_ERR_CALL_PROC_EXP				"No se puede llamar un procedimiento en una expresion"
	
	struct S_Nested_Level
	{
		int numOperators = 0;
		int numOperands = 0;
	};

	class SyntaxAnalyzer
	{
	private:
		msclr::gcroot<ErrorsModule ^> managedRef_errorsModule;			// REFERENCE TO MANAGED ERRORS MODULE
		LexAnalyzer* Lexico;
		SymTab* Symbols;

		void addError(int lineNum, const char *desc);
		void addErrorExpect(int lineNum, const char* e, const char* f);
		void checkProgram();
		void checkVars(ENODE_CLASS nclass);
		void checkType(map <std::string, int> vars, const Token* t, ENODE_CLASS nclass);
		void checkMain();
		void checkSwitch();
		void checkWhile();
		void checkFor();
		int checkDimension();
		void checkRead();
		void checkPrint();
		void checkIf();
		void checkParam();
		void checkAssign();
		void checkProcFunc();
		void checkProc();
		void checkFunct();
		void checkBlock();
		void checkReturn();
		void checkListaImp();
		bool processExpression();
		bool isOperator(const Token* t);
		bool isConst(const Token* t);
		void checkEXPLOG(vector <S_Nested_Level> *nestedLevels, int *currentNestedLevel, int *NumErrors);  // !
		void checkTerm(vector <S_Nested_Level> *nestedLevels, int *currentNestedLevel, int *NumErrors);
		void checkInc_Dec();
		void checkStatement();
		void checkCallProcFunc();
		void checkBlockSwitch();


		bool isStatement();
	public:
		SyntaxAnalyzer(ErrorsModule^ err, LexAnalyzer* lex);
		~SyntaxAnalyzer();
		bool CheckSyntax();

	};

	/*class SyntaxState
	{
	public:
		SyntaxState();
		~SyntaxState();

		virtual void checkSyntax() = 0;

	protected:
		SyntaxAnalyzer* syntax;
		LexAnalyzer* lex;
		std::vector<STOKENEXPECTED> m_expectedTokens;
		int indexToExpToken;
	};

	class SyntaxProgram : public SyntaxState
	{
	public:
		SyntaxProgram();
		~SyntaxProgram();

		void checkSyntax();
	};

	class SyntaxVar : public SyntaxState
	{
	public:
		SyntaxVar();
		~SyntaxVar();

		void checkSyntax();
	};*/
}