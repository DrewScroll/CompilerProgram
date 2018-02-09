#pragma once

//using namespace System;

namespace Compilador
{
	public enum class ERROR_PHASE
	{
		GLOBAL,
		LEX_ANALYZER,
		SYN_ANALYZER,
		SEM_ANALYZER,
		CODE_GENERATION
	};

#define MAX_UAD_COMPILER_ERRORS 100

	public ref class ErrorsModule
	{
	private:
		int numErrors;
		int numErrorsLex;
		int numErrorsSync;
		cli::array<System::String ^> ^ errorsArray;

	public:

		ErrorsModule();
		~ErrorsModule();

		void clearErrors();
		bool addError(ERROR_PHASE errorPhase, int lineNumber, System::String ^ errorDesc, System::String ^ errorLine);

		property int NumErrors
		{
			int get()
			{
				return numErrors;
			}
		}

		property int MaxErrors
		{
			int get()
			{
				return MAX_UAD_COMPILER_ERRORS;
			}
		}

		property cli::array<System::String ^> ^ Errors
		{
			cli::array<System::String ^> ^ get()
			{
				return errorsArray;
			}
		}
		property int NumErrorsLex
		{
			int get()
			{
				return numErrorsLex;
			}
		}
		property int NumErrorsSyn
		{
			int get()
			{
				return numErrorsSync;
			}
		}
	};
}
