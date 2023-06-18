#include "ReadySetBoole.hpp"

unsigned int RSB::adder(unsigned int a, unsigned int b)
{
	unsigned int carry = 0;

	while (b != 0)
	{
		carry = a & b;
		a = a ^ b;
		b = carry << 1;
	}
	return (a);
};

unsigned int RSB::multiplier(unsigned int a, unsigned int b)
{
	unsigned int result = 0;

	while (b != 0)
	{
		// check the least significant bit of b
		if (b & 1)
			result = adder(result, a);
		a <<= 1;
		b >>= 1;
	}
	return (result);
};

unsigned int RSB::gray_code(unsigned int n)
{
	// perform XOR operation between n and n shifted right by 1 bit
	return (n ^ (n >> 1));
};

bool	RSB::eval_formula(const std::string& formula)
{
	std::stack<bool>	eval_stack;
	
	check_formula(formula);
	for (char c: formula)
	{
		if (std::isdigit(c))
		{
			bool value = c == '1';
			eval_stack.push(value);
		}
		else if (c == '!')
		{
			bool operand = eval_stack.top();
			eval_stack.pop();
			eval_stack.push(!operand);
		}
		else if (c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
		{
			bool operand2 = eval_stack.top();
			eval_stack.pop();
			bool operand1 = eval_stack.top();
			eval_stack.pop();

			bool result = eval_operator(c, operand1, operand2);
			eval_stack.push(result);
		}
		else
			throw std::runtime_error("Invalid symbol");
	}
	return eval_stack.top();
};

bool	RSB::eval_operator(char op, char operand1, char operand2)
{
	switch (op)
	{
		case '!':
			return !operand2;
		case '&':
			return operand1 && operand2;
		case '|':
			return operand1 || operand2;
		case '^':
			return operand1 != operand2;
		case '>':
			return !operand1 || operand2;
		case '=':
			return operand1 == operand2;
		default:
			throw std::runtime_error("Invalid symbol");
	}
};

void	RSB::check_formula(const std::string& formula)
{
	Tokenizer			tokenizer;
    std::vector<Token>	tokens = tokenizer.tokenize(formula);
    std::stack<char>	stack;
    char				op1, op2;

	//print_tokens(tokens);
    //std::cout << "\n\t Formula syntax checking...\n";
    for (const Token& token : tokens)
	{
        switch (token.type)
		{
            case TokenType::VARIABLE:
				stack.push('1');
                break;
            case TokenType::BOOLEAN:
				stack.push(token.value);
                break;
            case TokenType::NEGATION:
	    		if (stack.size() >= 1)
				{
	    			op1 = stack.top();
					stack.pop();
					stack.push(!op1);
				}
				else
				{
					std::stringstream error_message;
					error_message << "Invalid syntax '" << token.value << "'";
					throw std::runtime_error(error_message.str());
				}
				break;
			case TokenType::OPERATOR:
			    if (stack.size() >= 2)
				{
					op1 = stack.top();
					stack.pop();
			    	op2 = stack.top();
					stack.pop();
					bool result = eval_operator(token.value, op1, op2);
					stack.push(result);
				}
				else
				{
					std::stringstream error_message;
					error_message << "Invalid syntax '" << token.value << "'";
					throw std::runtime_error(error_message.str());
				}
				break;
		}
	}
    if (stack.size() != 1)
		throw std::runtime_error("Invalid formula");
}

void	RSB::print_truth_table(const std::string& formula)
{
	size_t variable_count = 0;
	size_t rows = 0;
	std::string temp_formula = formula;
	// store all variable indice to replace them with boolen value for eval_formula()
	std::vector<size_t> variable_indice;

	check_formula(formula);
	// print column headers
	std::cout << "| ";
	for (size_t i = 0; i < formula.length(); ++i)
	{
		char c = formula[i];
		if (isalpha(c))
		{
			std::cout << c << " | ";
			variable_indice.push_back(i);
			variable_count++;
		}
		else
		{
			std::stringstream error_message;
			error_message << "Invalid symbol '" << c << "'";
			throw std::runtime_error(error_message.str());
		}
	}
	std::cout << "= |\n";
	for (size_t i = 0; i <= variable_count; ++i)
		std::cout << "|---";
	std::cout << "|\n";
	rows = 1 << variable_count;
	/*
	* to display all variable indice
	for (auto it = variable_indice.begin(); it != variable_indice.end(); ++it)
		std::cout << *it << std::endl;
	*/

	for (size_t i = 0; i < rows; ++i)
	{
		std::cout << "| ";
		size_t index = 0;
		for (int j = variable_count - 1; j >= 0; --j)
		{
			size_t value = (i >> j) & 1;
			std::cout << value << " | ";
			temp_formula[variable_indice[index++]] = value + '0';
		}
		std::cout << eval_formula(temp_formula) << " |\n";
	}
};

static std::string	apply_negation(std::string& formula)
{
	std::stack<std::string> stack;
	std::string				temp;

	for (char c : formula)
	{
		if (isalpha(c))
		{
			if (!stack.empty())
			{
				temp = stack.top();
				stack.pop();
				stack.push(temp + c + "!");
			}
			else
				stack.push(std::string(1, c) + "!");
		}
		else if (c == '!' || c == '&' || c == '|')
		{
			switch (c)
			{
        		case '!':
					temp = stack.top();
					stack.pop();
        		    stack.push(temp.substr(0, temp.length() - 1));
        		    break;
        		case '&':
					temp = stack.top();
					stack.pop();
        		    stack.push(temp + "|");
        		    break;
        		case '|':
					temp = stack.top();
					stack.pop();
        		    stack.push(temp + "&");
        		    break;
			}
		}
	}
	return stack.top();
};

const std::string	RSB::negation_normal_form(const std::string& formula)
{
	std::stack<std::string> stack;
	std::string temp, temp2;

	check_formula(formula);
	for (char c : formula)
	{
		if (isalpha(c))
			stack.push(std::string(1, c));
		else if (c == '!' || c == '&' || c == '|' || c == '>' || c == '=')
		{
			if (c == '!')
			{
				if (!stack.empty())
				{
					temp = stack.top();
					temp2 = apply_negation(temp);
					stack.push(temp2);
				}
			}
        	else if (c == '&' || c == '|')
			{
        	    temp = stack.top(); stack.pop();
        	    temp2 = stack.top(); stack.pop();
        	    stack.push(temp2 + temp + c);
        	}
        	else if (c == '>')
			{
        	    temp = stack.top(); stack.pop();
        	    temp2 = stack.top(); stack.pop();
        	    stack.push(temp2 + "!" + temp + "|");
        	}
        	else if (c == '=')
			{
        	    temp = stack.top(); stack.pop();
        	    temp2 = stack.top(); stack.pop();
        	    std::string nnf = temp2 + temp + "&" + temp2 + "!" + temp + "!&|";
        	    stack.push(nnf);
			}
		}
		else
		{
			std::stringstream error_message;
			error_message << "Invalid symbol '" << c << "'";
			throw std::runtime_error(error_message.str());
		}
	}
	return stack.top();
};

const std::string	RSB::conjunctive_normal_form(const std::string& formula)
{
	check_formula(formula);
	std::string temp_formula = negation_normal_form(formula);
};
