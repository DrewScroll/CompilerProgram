#include "stdafx.h"
#include "GlobalNode.h"

Compilador::GlobalNode::GlobalNode(std::string _symbol, ENODE_CLASS _nclass, int _dimen, std::string _typ)
{
	symbol = _symbol;
	nclass = _nclass;
	dimen = _dimen;
	typ = _typ;
	val = NULL;
	localNode = NULL;
}

Compilador::GlobalNode::~GlobalNode()
{
	if (val)
		delete val;
	if (localNode)
	{
		delete localNode;
		localNode = nullptr;
	}
}

void Compilador::GlobalNode::setLocalNode(LocalNode * n)
{
	if (localNode == nullptr)
	{
		localNode = n;
	}
	else
	{
		LocalNode* temp = localNode;
		localNode = n;
		n->setNext(temp);
	}
}
