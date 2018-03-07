#include "stdafx.h"
#include "SymTab.h"

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
}

void Compilador::LocalNode::setNext(LocalNode * n)
{
	next = n;
}

Compilador::SymTab::SymTab()
{
}

Compilador::SymTab::~SymTab()
{
}

bool Compilador::SymTab::SymbolExists(std::string symbol, ENODE_CLASS nclass, std::string nproc_func)
{
	if (nclass == GLOBAL_VAR || nclass == PROC || nclass == FUNC)
	{
		if(m_nodes.find(symbol)!= m_nodes.end())
		{
			return true;
		}
		else if (nclass == PARAM || nclass == LOCAL_VAR)
		{
			auto it = m_nodes.find(symbol);
			if (it != m_nodes.end())
			{
				GlobalNode* gnode = it->second;
				if (gnode != nullptr)
				{
					LocalNode* lnode = gnode->getLocalNode();
					while (lnode != nullptr)
					{
						if (lnode->getNodeClass() == nclass && lnode->getnProcFunc().compare(nproc_func) == 0)
						{
							return true;
						}
						lnode = lnode->getNext();
					}
				}
			}
		}
	}
	return false;
}

bool Compilador::SymTab::AddSymbol(std::string symbol, ENODE_CLASS nclass, int dimen, std::string typ, std::string nproc_func)
{
	if (!SymbolExists(symbol, nclass, nproc_func))
	{
		if (nclass == GLOBAL_VAR || nclass == PROC || nclass == FUNC)
		{
			m_nodes.insert(std::make_pair(symbol, new GlobalNode(symbol, nclass, dimen, typ)));
		}
		else if (nclass == PARAM || nclass == LOCAL_VAR)
		{
			LocalNode *lnode = new LocalNode(nclass, typ, dimen, nproc_func);
			auto it = m_nodes.find(symbol);
			if (it != m_nodes.end())
			{
				GlobalNode * gnode = it->second;
				gnode->setLocalNode(lnode);
			}
			else
			{
				GlobalNode *gnode = new GlobalNode(symbol, UNDEF, dimen, typ);
				gnode->setLocalNode(lnode);
			}
		}
	}
	return false;
}

Compilador::NodeVal::NodeVal()
{
}

Compilador::NodeVal::~NodeVal()
{
}
