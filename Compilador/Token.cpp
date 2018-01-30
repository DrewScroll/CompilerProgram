#include "stdafx.h"
#include "Token.h"



Compilador::Token::Token(std::string lex, TOKEN_TYPE type, int lineNum) : m_Lex(lex), m_Type(type), m_LineNumber(lineNum)
{
}

Compilador::Token::~Token()
{
}

std::string Compilador::Token::getTypeStr()
{
	std::string typeStr = "";
	static const char * EnumStrings[] = {
		"UNDEFINED",
		"ID",
		"INT",
		"FLOAT",
		"STRING",
		"LOGICAL_CONSTANT",
		"KEYWORD",
		"SEPARATOR",
		"RELATIONAL_OPERATOR",
		"ARITHMETIC_OPERATOR",
		"LOGICAL_OPERATOR",
		"LOGICAL_UNARY_OPERATOR",
		"ASSIGN_OPERATOR",
		"GROUPING_OPERATOR",
		"DIMENSION_OPERATOR"
	};
	typeStr = EnumStrings[m_Type];
	return typeStr;
}
