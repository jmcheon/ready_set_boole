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
	//Tokenizer			tokenizer;
    //std::vector<Token>	tokens = tokenizer.tokenize(formula);
	
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
				if (stack.size() >= 2)
				{
					std::stringstream error_message;
					error_message << "Invalid operand '" << token.value << "'";
					throw std::runtime_error(error_message.str());
				}
                //std::cout << "Variable";
		//stack.push(token.value);
				stack.push('1');
                break;
            case TokenType::BOOLEAN:
				if (stack.size() >= 2)
				{
					std::stringstream error_message;
					error_message << "Invalid operand '" << token.value << "'";
					throw std::runtime_error(error_message.str());
				}
                //std::cout << "Boolean";
				stack.push(token.value);
                break;
            case TokenType::NEGATION:
	    		if (stack.size() >= 1)
				{
	    			op1 = stack.top();
					stack.pop();
					stack.push(!op1);
                	//std::cout << "Negation";
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
					//std::cout << "OPERATOR";
				}
				else
				{
					std::stringstream error_message;
					error_message << "Invalid syntax '" << token.value << "'";
					throw std::runtime_error(error_message.str());
				}
				break;
		}
		//std::cout << ", " << token.value << std::endl;
	}
    if (stack.size() != 1)
		throw std::runtime_error("Invalid formula");
    //return tokens;
}
/*
void	RSB::check_formula(const std::string& formula)
{
	size_t operand_count = 0;
	size_t operator_count = 0;

	for (char c : formula)
	{
		if (c == '!' || c == '&' || c == '|' || c == '^' || c == '>' || c == '=')
			operator_count++;
		else
			operand_count++;
	}
	if (operand_count - operator_count != 1)
		throw std::runtime_error("Invalid formula");
};
*/
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

bool	isOperand(const char* c)
{
	while (*c != '\0')
		c++;
	c--;
	if (*c >= 'A' && *c <= 'Z')
	{
		//std::cout << *c << std::endl;
		return true;
	}
	return false;
}

const std::string	RSB::negation_normal_form(const std::string& formula)
{
	std::stack<std::string> stack;

	for (char c : formula)
	{
		if (c == '!' || c == '&' || c == '|' || c == '>' || c == '=')
		{
			std::string operand1, operand2;
			switch (c) {
        			case '&': {
        			    operand1 = stack.top(); stack.pop();
        			    operand2 = stack.top(); stack.pop();
				    if (isOperand(operand2.c_str())) 
					    operand2.insert(operand2.size(), 1, '!');
				    if (isOperand(operand1.c_str())) 
					    operand1.insert(operand1.size(), 1, '!');
        			    stack.push(operand2 + operand1 + "|");
        			    break;
        			}
        			case '|': {
        			    operand1 = stack.top(); stack.pop();
        			    operand2 = stack.top(); stack.pop();
				    if (isOperand(operand2.c_str())) 
					    operand2.insert(operand2.size(), 1, '!');
				    if (isOperand(operand1.c_str())) 
					    operand1.insert(operand1.size(), 1, '!');
        			    stack.push(operand2 + operand1 + "&");
        			    break;
        			}
        			case '>': {
        			    operand1 = stack.top(); stack.pop();
        			    operand2 = stack.top(); stack.pop();
        			    stack.push(operand2 + "!" + operand1 + "|");
        			    break;
        			}
        			case '=': {
        			    operand1 = stack.top(); stack.pop();
        			    operand2 = stack.top(); stack.pop();
        			    std::string nnf = operand2 + operand1 + "&" + operand2 + "!" + operand1 + "!&|";
        			    stack.push(nnf);
        			    break;
        			}
			}
		}
		else
			stack.push(std::string(1, c));
	}
	return stack.top();
};
