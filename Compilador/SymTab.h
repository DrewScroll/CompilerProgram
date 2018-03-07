#pragma once
#include <map>

namespace Compilador
{
	enum ENODE_CLASS
	{
		UNDEF = 0,
		GLOBAL_VAR,
		PROC,
		FUNC,
		PARAM,
		LOCAL_VAR
	};

	class NodeVal
	{
	public:
		NodeVal();
		~NodeVal();

	private:

	};

	class LocalNode
	{
	public:
		LocalNode(ENODE_CLASS _nclass, std::string _typ, int _dimen, std::string _nproc_func);
		~LocalNode();

	private:
		ENODE_CLASS nclass;
		std::string typ;
		int dimen;
		std::string nproc_func;
		NodeVal* val;
		LocalNode* next;

	public:
		void setNext(LocalNode* n);
		LocalNode* getNext() { return next; }
		ENODE_CLASS getNodeClass() { return nclass; }
		std::string getnProcFunc() { return nproc_func; }
	};

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
	};

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