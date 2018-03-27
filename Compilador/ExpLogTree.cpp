#include "stdafx.h"
#include "ExpLogTree.h"

bool Compilador::ExpLogTree::evaluate()
{
	if (root != nullptr)
	{
		return root->evaluate();
	}
	return false;
}
