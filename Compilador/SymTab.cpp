#include "stdafx.h"
#include "SymTab.h"

Compilador::SymTab::SymTab()
{
}

Compilador::SymTab::~SymTab()
{
	for (auto it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		delete it->second;
	}
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

bool Compilador::SymTab::SymbolExists(std::string symbol)
{
	if (m_nodes.find(symbol) != m_nodes.end())
	{
		return true;
	}
	return false;
}

bool Compilador::SymTab::AddSymbol(std::string symbol, ENODE_CLASS nclass, int dimen, std::string typ, std::string nproc_func)
{
	if (!SymbolExists(symbol, nclass, nproc_func))
	{
		if (nclass == GLOBAL_VAR || nclass == LOCAL_VAR || nclass == PARAM)
		{
			if (SymbolExists(symbol, PROC, nproc_func))
			{
				//addError()
				return false;
			}
			if (SymbolExists(symbol, FUNC, nproc_func))
			{
				return false;
			}
		}
		else if (nclass == PROC)
		{
			if (SymbolExists(symbol, FUNC, nproc_func))
			{
				//adderror
				return false;
			}
		}
		else if (nclass == FUNC)
		{
			if (SymbolExists(symbol, PROC, nproc_func))
			{
				//addError
				return false;
			}
		}
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
		return true;
	}
	return false;
}

Compilador::ENODE_CLASS Compilador::SymTab::getSymbolClass(std::string symbol)
{
	if (SymbolExists(symbol))
	{
		auto it = m_nodes.find(symbol);
		GlobalNode* g_node = it->second;
		ENODE_CLASS nclass = g_node->getNodeClass();
		if (nclass == UNDEF)
		{
			LocalNode* l_node = g_node->getLocalNode();
			nclass = l_node->getNodeClass();
		}
		return nclass;
	}
	return UNDEF;
}

std::string Compilador::SymTab::getSymbolType(std::string symbol, ENODE_CLASS nclass, std::string nproc_func)
{
	return std::string();
}
