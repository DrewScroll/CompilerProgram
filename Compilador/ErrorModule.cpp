#include "stdafx.h"
#include "ErrorModule.h"

/*
*/
Compilador::ErrorsModule::ErrorsModule()
{
	numErrors = 0;

	errorsArray = gcnew cli::array<String ^>(MAX_UAD_COMPILER_ERRORS);

	for (int i = 0; i < MAX_UAD_COMPILER_ERRORS; i++)
	{
		errorsArray[i] = gcnew String("");
	}
}

/*
*/
Compilador::ErrorsModule::~ErrorsModule()
{
}

/*
*/
void Compilador::ErrorsModule::clearErrors()
{
	// Clear num errors
	numErrors = 0;
}

/*
*/
bool Compilador::ErrorsModule::addError(ERROR_PHASE errorPhase, int lineNumber, String ^ errorDesc, String ^ errorLine)
{
	if (numErrors < MAX_UAD_COMPILER_ERRORS)
	{
		String ^ errLine = gcnew String("");
		if (errorLine->Length > 20)
		{
			errLine = errorLine->Substring(0, 20);
		}
		else
		{
			errLine = errorLine;
		}

		errorsArray->SetValue(String::Format("<{0}>: \t{1} \t\t{2} \t\t{3}", errorPhase.ToString(), lineNumber, errorDesc, errLine), numErrors);
		numErrors++;

		return true;
	}

	return false;
}
