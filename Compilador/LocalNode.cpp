#include "stdafx.h"
#include "LocalNode.h"

Compilador::LocalNode::LocalNode(ENODE_CLASS _nclass, std::string _typ, int _dimen, std::string _nproc_func)
{
	nclass = _nclass;
	typ = _typ;
	dimen = _dimen;
	nproc_func = _nproc_func;
	val = NULL;
	next = NULL;
}

Compilador::LocalNode::~LocalNode()
{
	if (val)
		delete val;

	if (next)
	{
		LocalNode* temp = next;
		LocalNode* aux;
		while (temp != nullptr)
		{
			aux = temp->getNext();
			delete temp;
			temp = aux;
		}
	}
}

void Compilador::LocalNode::setNext(LocalNode * n)
{
	next = n;
}
