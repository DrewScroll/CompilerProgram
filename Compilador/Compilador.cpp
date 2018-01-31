// Archivo DLL principal.

#include "stdafx.h"

#include "Compilador.h"

Compilador::Manager::Manager()
{
	err = gcnew ErrorsModule();
	lex = new LexAnalyzer(err);
}

Compilador::Manager::~Manager()
{
	delete lex;
}

cli::array<String^>^ Compilador::Manager::compile(String ^ program)
{
	int numPhaseFailed = 0;
	cli::array<String^> ^ compilationDetails;

	//Clear State

	if (err && lex != NULL)
	{
		err->clearErrors();
	}
	else
		if (!err)
		{
			compilationDetails = gcnew cli::array<String^>(1);
			compilationDetails[0] = gcnew String("Invalid Error Module");
			return compilationDetails;
		}
		else if (lex == NULL)
		{
			compilationDetails = gcnew cli::array<String^>(1);
			compilationDetails[0] = gcnew String("Invalid Lex Analyzer");
			return compilationDetails;
		}
	//Lex Analisis
	lex->parseCode((const char*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(program).ToPointer());
	
	compilationDetails = getCompilationDetails();

	return compilationDetails;

	// TODO: insertar una instrucción return aquí
}

cli::array<String^>^ Compilador::Manager::getAllTokens()
{
	cli::array<String^> ^ allTokens;
	if (lex->getNumTokens() > 0)
	{
		allTokens = gcnew cli::array <String^>(lex->getNumTokens());

		std::vector<Token *> allTokensVec;
		lex->getTokens(&allTokensVec);

		for (int i = 0; i < (int)allTokensVec.size(); i++)
		{
			String ^ templex = gcnew String(allTokensVec[i]->getLex().c_str());
			String ^ typ = gcnew String(allTokensVec[i]->getTypeStr().c_str());
			
			allTokens[i] = gcnew String("");
			allTokens[i] = String::Format("{0}\t\t{1}", templex, typ);
		}
	}
	else
	{
		allTokens = gcnew cli::array<String^>(1);
		allTokens[0] = gcnew String("<NO TOKENS FOUND>");
	}

	return allTokens;
}

cli::array<String^>^ Compilador::Manager::getCompilationDetails()
{
	int numErrorLines = 0;
	cli::array <String^>^ CompilationDetails;
	if (lex->succeeded())
	{
		CompilationDetails = gcnew cli::array<String^>(1);
		CompilationDetails[0] = gcnew String("Compile: Successful");
		return CompilationDetails;
	}
	else
	{
		numErrorLines = err->NumErrors + 3;
		CompilationDetails = gcnew cli::array<String ^>(numErrorLines);
		for (int i = 0; i < numErrorLines; i++)
		{
			CompilationDetails[i] = gcnew String("");
		}
		CompilationDetails[0] = String::Format("Compilation phase \tLine number \tDescription \t\t\tLine");
		CompilationDetails[1] = String::Format("--------------------------------------------------");

		cli::array <String^>^allErrors = err->Errors;

		for (int i = 2; i < numErrorLines - 1; i++)
		{
			CompilationDetails[i] = allErrors[i - 2];
		}

		CompilationDetails[numErrorLines - 1] = String::Format("Compile: failed, {0} errrors", err->NumErrors);

		return CompilationDetails;
	}
}