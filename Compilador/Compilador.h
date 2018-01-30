// Compilador.h

#pragma once
#include "LexAnalizer.h"
#include "ErrorModule.h"

using namespace System;

namespace Compilador {

	public ref class Manager
	{
		// TODO: agregar aqu� los m�todos de la clase.
	public:
		Manager();
		~Manager();
		cli::array<String^>^compile(String^program);
		cli::array<String^>^ getAllTokens();
		cli::array<String^> ^ getCompilationDetails();

	private:
		LexAnalyzer * lex;
		ErrorsModule ^ err;
	};
}
