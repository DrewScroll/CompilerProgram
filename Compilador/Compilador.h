// Compilador.h

#pragma once
#include "LexAnalizer.h"
#include "SyntaxAnalyzer.h"
#include "ErrorModule.h"
#include "SymTab.h"

using namespace System;

namespace Compilador {

	public ref class Manager
	{
		// TODO: agregar aquí los métodos de la clase.
	public:
		Manager();
		~Manager();
		cli::array<String^>^compile(String^program);
		cli::array<String^>^ getAllTokens();
		cli::array<String^> ^ getCompilationDetails();

	private:
		LexAnalyzer * lex;
		ErrorsModule ^ err;
		SyntaxAnalyzer * syn;
		SymTab* symbol;
	};
}
