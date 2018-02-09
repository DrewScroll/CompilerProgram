#pragma once
#include "ErrorModule.h"
#include "LexAnalizer.h"
#include "Token.h"
#include <vcclr.h>

namespace Compilador
{
	class SyntaxAnalyzer
	{
	private:
		msclr::gcroot<ErrorsModule ^> managedRef_errorsModule;			// REFERENCE TO MANAGED ERRORS MODULE
		LexAnalyzer* Lexico;

		void checkProgram();
	public:
		SyntaxAnalyzer(ErrorsModule^ err, LexAnalyzer* lex);
		bool CheckSyntax();
		void checkVars();
		void checkFuncProc();
		void checkMain();
	};
}
