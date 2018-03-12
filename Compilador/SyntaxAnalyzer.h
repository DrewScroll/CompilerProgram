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
#define SYN_ERR_DIMEN						"Valor en la dimension no es un numero no es un numero"
#define SYN_ERR_PROFUNMAIN_B4_VAR			"Procedure, Function o Main declarados anteriormente"
#define SYN_ERR_MAIN_B4_PROCFUN				"Main declarado anteriormente"
#define SYN_ERR_NO_ID						"ID no identificado"
#define SYN_ERR_NO_PARM						"Parametros no identificados"
#define SYN_ERR_NO_BLOCK					"Bloque no identificado"

	class SyntaxAnalyzer
	{
	private:
		msclr::gcroot<ErrorsModule ^> managedRef_errorsModule;			// REFERENCE TO MANAGED ERRORS MODULE
		LexAnalyzer* Lexico;
		SymTab* Symbols;

		void addError(int lineNum, const char *desc);
		void addErrorExpect(int lineNum, const char* e, const char* f);
		void checkProgram();
		void checkVars();
		void checkType(std::vector <std::string> vars, const Token* t);
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
		void checkEXPLOG();  // !
		void checkInc_Dec();
		void checkBlockProcFunc();
		void checkStatement();
		void checkBlockState();
		void checkCallProcFunc();

		bool isStatement();
	public:
		SyntaxAnalyzer(ErrorsModule^ err, LexAnalyzer* lex);
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