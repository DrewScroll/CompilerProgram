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
		bool AddSymbol(std::string symbol, ENODE_CLASS nclass, int dimen, std::string typ, std::string nproc_func);
	};
}