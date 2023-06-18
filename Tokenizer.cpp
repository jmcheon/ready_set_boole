#include "Tokenizer.hpp"

std::vector<Token>	Tokenizer::tokenize(const std::string& formula)
{
    std::vector<Token> tokens;

    for (char c : formula)
	{
        if (c == ' ')
            continue;
        if (c == '!')
            tokens.push_back({TokenType::NEGATION, '!'});
        else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
            tokens.push_back({TokenType::OPERATOR, c});
		else if (c >= 'A' && c <= 'Z')
            tokens.push_back({TokenType::VARIABLE, c});
		else if (c == '1' || c == '0')
            tokens.push_back({TokenType::BOOLEAN, c});
		else
		{
			std::stringstream error_message;
			error_message << "Invalid symbol '" << c << "'";
			throw std::runtime_error(error_message.str());
		}
    }
    return tokens;
}
