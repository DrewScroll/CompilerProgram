#pragma once
#include <string>

namespace Compilador 
{
	enum TOKEN_TYPE
	{
		UNDEFINED = 0,
		ID,
		INT,
		FLOAT,
		STRING,
		LOGICAL_CONSTANT,
		KEYWORD,
		SEPARATOR,
		RELATIONAL_OPERATOR,
		ARITHMETIC_OPERATOR,
		LOGICAL_OPERATOR,
		LOGICAL_UNARY_OPERATOR,
		ASSIGN_OPERATOR,
		GROUPING_OPERATOR,
		DIMENSION_OPERATOR
	};

	class Token
	{
	private:
		std::string m_Lex;
		TOKEN_TYPE m_Type;
		int m_LineNumber;
	public:
		Token(std::string lex, TOKEN_TYPE type, int lineNum);
		~Token();

		std::string getLex() const { return m_Lex; }
		std::string getTypeStr();
		TOKEN_TYPE getType() const { return m_Type; }
		int getLineNumber() const { return m_LineNumber; }
	};
}