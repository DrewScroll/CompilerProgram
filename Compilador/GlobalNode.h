#pragma once
#include "LocalNode.h"

namespace Compilador
{
	class GlobalNode
	{
	public:
		GlobalNode(std::string _symbol, ENODE_CLASS _nclass, int _dimen, std::string _typ);
		~GlobalNode();

	private:
		std::string symbol;
		ENODE_CLASS nclass;
		NodeVal *val;
		int dimen;
		std::string typ;
		LocalNode* localNode;

	public:
		void setLocalNode(LocalNode* n);
		ENODE_CLASS getNodeClass() { return nclass; }
		std::string getSymbol() { return symbol; }
		LocalNode* const getLocalNode() { return localNode; }
		std::string getType() { return typ; }
	};
}