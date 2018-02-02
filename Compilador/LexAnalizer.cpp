#include "stdafx.h"
#include "LexAnalizer.h"
#include "Token.h"

#include <algorithm>
#include <iterator>

/*
*/
Compilador::LexAnalyzer::LexAnalyzer(ErrorsModule ^ errorsModule)
{
	managedRef_errorsModule = errorsModule;

	m_Keywords.insert(std::make_pair("var", ""));
	m_Keywords.insert(std::make_pair("int", ""));
	m_Keywords.insert(std::make_pair("float", ""));
	m_Keywords.insert(std::make_pair("string", ""));
	m_Keywords.insert(std::make_pair("bool", ""));
	m_Keywords.insert(std::make_pair("function", ""));
	m_Keywords.insert(std::make_pair("procedure", ""));
	m_Keywords.insert(std::make_pair("main", ""));
	m_Keywords.insert(std::make_pair("for", ""));
	m_Keywords.insert(std::make_pair("while", ""));
	m_Keywords.insert(std::make_pair("if", ""));
	m_Keywords.insert(std::make_pair("else", ""));
	m_Keywords.insert(std::make_pair("switch", ""));
	m_Keywords.insert(std::make_pair("default", ""));
	m_Keywords.insert(std::make_pair("print", ""));
	m_Keywords.insert(std::make_pair("read", ""));
	m_Keywords.insert(std::make_pair("return", ""));
}

/*
*/
Compilador::LexAnalyzer::~LexAnalyzer()
{
}

/*
*/
bool Compilador::LexAnalyzer::parseCode(const char * src)
{
	int currentLineNumber = 1;
	int numCharsInLine = 0;
	int firstLineComment = 0;
	const char * currentChar = src;
	const char* currentLine = src;
	std::string tokenBuffer;
	std::string firstCommentLine;
	char lexSrcEof = '\0';
	bool stringNotClosed = false;
	TOKEN_TYPE tokenType = TOKEN_TYPE::UNDEFINED;

	m_Succeeded = true;
	m_State = S_START;
	clearTokens();

	while (*currentChar != lexSrcEof)
	{
		switch (m_State)
		{
		case S_START:
			if (isAlpha(currentChar) || *currentChar == '_')
			{
				tokenBuffer.clear();
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_ID;
				currentChar++;
			}
			else if (isDigit(currentChar))
			{
				tokenBuffer.clear();
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_INT;
				currentChar++;
			}
			else if (isSpace(currentChar))
			{
				if (isNewLine(currentChar) && *currentChar == '\n')
				{
					currentLineNumber++;
					currentLine = currentChar + 1;
				}
				currentChar++;
			}
			else if (isArithmeticOp(currentChar))
			{
				if (*currentChar == '/')
				{
					currentChar++;
					if (*currentChar == '*')
					{
						m_State = S_PARSING_COMMENT;
						currentChar++;
						break;
					}
					currentChar--;
				}
				tokenBuffer.clear();
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_ARITHMETICOP;
				currentChar++;
			}
			else if (isRelationalOp(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == '<')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_LESSTHAN;
					currentChar++;
				}
				else if (*currentChar == '>')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_GREATERTHAN;
					currentChar++;
				}
				else if (*currentChar == '=')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_ASSIGN;
					currentChar++;
				}
			}
			else if (isLogicalOp(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == '&')
				{
					tokenBuffer.append(currentChar, 1);
					currentChar++;
					if (*currentChar == '&')
					{
						tokenBuffer.append(currentChar, 1);
						m_State = S_PARSING_LOGICAL_OP_AND;
						currentChar++;
					}
					else
					{
						addError(currentLineNumber, LEX_ERROR_INVALID_LOGICAL_OP_AND, currentLine);
					}
				}
				else if (*currentChar == '|')
				{
					tokenBuffer.append(currentChar, 1);
					currentChar++;
					if (*currentChar == '|')
					{
						tokenBuffer.append(currentChar, 1);
						m_State = S_PARSING_LOGICAL_OP_OR;
						currentChar++;
					}
					else
					{
						addError(currentLineNumber, LEX_ERROR_INVALID_LOGICAL_OP_OR, currentLine);
					}
				}
				else if (*currentChar == '!')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_LOGICAL_OP_NOT;
					currentChar++;
				}
			}
			else if (isSeparator(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == ',')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_COMMA;
					currentChar++;
				}
				else if (*currentChar == ':')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_COLON;
					currentChar++;
				}
				else if (*currentChar == ';')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_SEMICOLON;
					currentChar++;
				}
			}
			else if (isGroupingChar(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == '(')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_OPENPARENTHESIS;
					currentChar++;
				}
				else if (*currentChar == ')')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_CLOSEPARENTHESIS;
					currentChar++;
				}
			}
			else if (isBlockChar(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == '{')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_OPENCURLYBRACKET;
					currentChar++;
				}
				else if (*currentChar == '}')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_CLOSECURLYBRACKET;
					currentChar++;
				}
			}
			else if (isDimensionChar(currentChar))
			{
				tokenBuffer.clear();
				if (*currentChar == '[')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_OPENBRACKET;
					currentChar++;
				}
				else if (*currentChar == ']')
				{
					tokenBuffer.append(currentChar, 1);
					m_State = S_PARSING_CLOSEBRACKET;
					currentChar++;
				}
			}
			else if (isStringLiteral(currentChar))
			{
				tokenBuffer.clear();
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_STRING;
				currentChar++;
			}
			else if (*currentChar == '.')
			{
				addError(currentLineNumber, LEX_ERROR_INVALID_FLOAT, currentLine);
				currentChar++;
			}
			break;
		case S_PARSING_ID:
			if (isAlpha(currentChar) || *currentChar == '_' || isDigit(currentChar))
			{
				tokenBuffer.append(currentChar, 1);
				currentChar++;
				if (*currentChar == lexSrcEof)
				{
					if (m_Keywords.find(tokenBuffer) != m_Keywords.end())
					{
						addToken(tokenBuffer.c_str(), TOKEN_TYPE::KEYWORD, currentLineNumber);
					}
					else if (tokenBuffer.compare("true") == 0 || tokenBuffer.compare("false") == 0)
					{
						addToken(tokenBuffer.c_str(), TOKEN_TYPE::LOGICAL_CONSTANT, currentLineNumber);
					}
					else
					{
						addToken(tokenBuffer.c_str(), TOKEN_TYPE::ID, currentLineNumber);
					}
				}
			}
			else
			{
				if (m_Keywords.find(tokenBuffer) != m_Keywords.end())
				{
					addToken(tokenBuffer.c_str(), TOKEN_TYPE::KEYWORD, currentLineNumber);
				}
				else if (tokenBuffer.compare("true") == 0 || tokenBuffer.compare("false") == 0)
				{
					addToken(tokenBuffer.c_str(), TOKEN_TYPE::LOGICAL_CONSTANT, currentLineNumber);
				}
				else
				{
					addToken(tokenBuffer.c_str(), TOKEN_TYPE::ID, currentLineNumber);
				}
				m_State = S_START;
			}
			break;
		case S_PARSING_INT:
			if (isDigit(currentChar))
			{
				tokenBuffer.append(currentChar, 1);
				currentChar++;
				if (*currentChar == lexSrcEof)
				{
					addToken(tokenBuffer.c_str(), TOKEN_TYPE::INT, currentLineNumber);
				}
			}
			else if (*currentChar == '.')
			{
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_FLOAT;
				currentChar++;
			}
			else if (isSeparator(currentChar) || isNewLine(currentChar))
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::INT, currentLineNumber);
				m_State = S_START;
			}
			else
			{
				addError(currentLineNumber, LEX_ERROR_INVALID_CHARACTER, currentLine);
			}
			break;
		case S_PARSING_FLOAT:
			if (isDigit(currentChar))
			{
				tokenBuffer.append(currentChar, 1);
				currentChar++;
				if (*currentChar == lexSrcEof)
				{
					if (m_Keywords.find(tokenBuffer) != m_Keywords.end())
					{
						addToken(tokenBuffer.c_str(), TOKEN_TYPE::FLOAT, currentLineNumber);
					}
				}
			}
			else
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::FLOAT, currentLineNumber);
				m_State = S_START;
				if (!isDigit(currentChar - 1))
				{
					addError(currentLineNumber, LEX_ERROR_INVALID_CHARACTER, currentLine);
				}
			}
			break;
		case S_PARSING_STRING:
			if (!isStringLiteral(currentChar))
			{
				if (*currentChar == lexSrcEof)
				{
					addError(currentLineNumber, LEX_ERROR_STRING_NOT_CLOSED, currentLine);
				}
				tokenBuffer.append(currentChar, 1);
				currentChar++;
			}
			else
			{
				tokenBuffer.append(currentChar, 1);
				currentChar++;
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::STRING, currentLineNumber);
				m_State = S_START;
			}
			break;
		case S_PARSING_LESSTHAN:
			if(*currentChar == '=')
			{
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_LESSTHANOREQUAL;
				currentChar++;
			}
			else
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
				m_State = S_START;
			}
			break;
		case S_PARSING_LESSTHANOREQUAL:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_GREATERTHAN:
			if (*currentChar == '=')
			{
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_GREATERTHANOREQUAL;
				currentChar++;
			}
			else
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
				m_State = S_START;
			}
			break;
		case S_PARSING_GREATERTHANOREQUAL:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_ASSIGN:
			if (*currentChar == '=')
			{
				tokenBuffer.append(currentChar, 1);
				m_State = S_PARSING_EQUAL;
				currentChar++;
			}
			else
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::ASSIGN_OPERATOR, currentLineNumber);
				m_State = S_START;
			}
			break;
		case S_PARSING_EQUAL:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_NOTEQUAL:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::RELATIONAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_OPENPARENTHESIS:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::GROUPING_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_CLOSEPARENTHESIS:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::GROUPING_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_ARITHMETICOP:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::ARITHMETIC_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_LOGICAL_OP_AND:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::LOGICAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_LOGICAL_OP_OR:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::LOGICAL_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_LOGICAL_OP_NOT:
			if (*currentChar == '=')
			{
				tokenBuffer.append(currentChar, 1);
				currentChar++;
				m_State = S_PARSING_NOTEQUAL;
			}
			else
			{
				addToken(tokenBuffer.c_str(), TOKEN_TYPE::LOGICAL_UNARY_OPERATOR, currentLineNumber);
				m_State = S_START;
			}
			break;
		case S_PARSING_OPENBRACKET:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::DIMENSION_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_CLOSEBRACKET:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::DIMENSION_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_OPENCURLYBRACKET:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::GROUPING_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_CLOSECURLYBRACKET:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::GROUPING_OPERATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_SEMICOLON:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::SEPARATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_COMMA:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::SEPARATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_COLON:
			addToken(tokenBuffer.c_str(), TOKEN_TYPE::SEPARATOR, currentLineNumber);
			m_State = S_START;
			break;
		case S_PARSING_COMMENT:
			while (*currentChar != lexSrcEof)
			{
				if (*currentChar == '*')
				{
					currentChar++;
					if (*currentChar == '/')
					{
						currentChar++;
						m_State = S_START;
						break;
					}
				}
				else
				{
					currentChar++;
				}
			}
			if (*currentChar == lexSrcEof)
			{
				addError(currentLineNumber, LEX_ERROR_COMMENT_NOT_CLOSED, currentLine);
				break;
			}
		default:
			break;
		}
	}
	return m_Succeeded;
}


/*
*/
int Compilador::LexAnalyzer::getNumTokens() const
{
	return m_Tokens.size();
}

/*
*/
void Compilador::LexAnalyzer::getTokens(std::vector<Token *> *tokensVec) const
{
	std::copy(m_Tokens.begin(), m_Tokens.end(), std::back_inserter(*tokensVec));
}

/*
*/
void Compilador::LexAnalyzer::addError(int lineNum, const char *desc, const char *line)
{
	
	String ^ strDesc = gcnew String(desc);
	String ^ strLine = gcnew String(line);
	managedRef_errorsModule->addError(Compilador::ERROR_PHASE::LEX_ANALYZER, lineNum, strDesc, strLine);
	m_Succeeded = false;
}

/*
*/
void Compilador::LexAnalyzer::addToken(const char * lex, TOKEN_TYPE type, int lineNum)
{
	m_Tokens.push_back(new Token(std::string(lex), type, lineNum));
}

/*
*/
void Compilador::LexAnalyzer::clearTokens()
{
	if (m_Tokens.size() > 0)
	{
		for (int i = 0; i < (int)m_Tokens.size(); i++)
		{
			if (m_Tokens[i] != NULL)
			{
				delete m_Tokens[i];
				m_Tokens[i] = NULL;
			}
		}
		m_Tokens.clear();
	}
}

/*
*/
bool Compilador::LexAnalyzer::isAlpha(const char * c) const
{
	if ((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isDigit(const char * c) const
{
	if (*c >= '0' && *c <= '9')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isSpace(const char * c) const
{
	if (*c == ' ' || *c == '\t' || isNewLine(c))
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isNewLine(const char * c) const
{
	if (*c == '\n' || *c == '\r')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isArithmeticOp(const char * c) const
{
	if (*c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '%' || *c == '^')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isRelationalOp(const char * c) const
{
	if (*c == '<' || *c == '>' || *c == '=')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isLogicalOp(const char * c) const
{
	if (*c == '&' || *c == '|' || *c == '!')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isSeparator(const char * c) const
{
	if (*c == ';' || *c == ',' || *c == ':')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isGroupingChar(const char * c) const
{
	if (*c == '(' || *c == ')')
	{
		return true;
	}

	return false;
}

bool Compilador::LexAnalyzer::isBlockChar(const char * c) const
{
	if (*c == '{' || *c == '}')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isDimensionChar(const char * c) const
{
	if (*c == '[' || *c == ']')
	{
		return true;
	}

	return false;
}

/*
*/
bool Compilador::LexAnalyzer::isStringLiteral(const char * c) const
{
	if (*c == '\"')
	{
		return true;
	}

	return false;
}