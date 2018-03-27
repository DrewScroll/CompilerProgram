#pragma once
#include "GlobalNode.h"
#include <map>

namespace Compilador
{
	class SymTab
	{
	public:
		SymTab();
		~SymTab();

	private:
		std::map<std::string, GlobalNode*> m_nodes;

	public:
		bool SymbolExists(std::string symbol, ENODE_CLASS nclass, std::string nproc_func);
		bool SymbolExists(std::string symbol);
		bool AddSymbol(std::string symbol, ENODE_CLASS nclass, int dimen, std::string typ, std::string nproc_func);
		ENODE_CLASS getSymbolClass(std::string symbol);
		std::string getSymbolType(std::string symbol, ENODE_CLASS nclass, std::string nproc_func);
	};
}