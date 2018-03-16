#pragma once
#include "NodeVal.h"
#include <string>


using namespace std;

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
}