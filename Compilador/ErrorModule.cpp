#include "stdafx.h"
#include "ErrorModule.h"

/*
*/
Compilador::ErrorsModule::ErrorsModule()
{
	numErrors = 0;

	errorsArray = gcnew cli::array<System::String ^>(MAX_UAD_COMPILER_ERRORS);

	for (int i = 0; i < MAX_UAD_COMPILER_ERRORS; i++)
	{
		errorsArray[i] = gcnew System::String("");
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
bool Compilador::ErrorsModule::addError(ERROR_PHASE errorPhase, int lineNumber, System::String ^ errorDesc, System::String ^ errorLine)
{
	if (numErrors < MAX_UAD_COMPILER_ERRORS)
	{
		System::String ^ errLine = gcnew System::String("");
		if (errorLine->Length > 20)
		{
			errLine = errorLine->Substring(0, 20);
		}
		else
		{
			errLine = errorLine;
		}

		errorsArray->SetValue(System::String::Format("<{0}>: \t{1} \t\t{2} \t\t{3}", errorPhase.ToString(), lineNumber, errorDesc, errLine), numErrors);
		numErrors++;

		return true;
	}

	return false;
}
