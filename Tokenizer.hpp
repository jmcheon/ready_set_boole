#ifndef TOKEN_HPP
#define TOKEN_HPP
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

enum class TokenType
{
    VARIABLE,
    NEGATION,
    OPERATOR,
	BOOLEAN,
};

class Token
{
	public:
    	TokenType	type;
    	char		value;
};

class Tokenizer
{
	public:
		std::vector<Token>	tokenize(const std::string& formula);
};

#endif
