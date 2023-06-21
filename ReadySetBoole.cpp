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
		//std::cout << c << std::endl;
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
			throw std::runtime_error("e Invalid symbol");
	}
	return eval_stack.top();
};

bool	RSB::eval_operator(char op, bool operand1, bool operand2)
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
			throw std::runtime_error("o Invalid symbol");
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
	std::vector<std::pair<char, size_t> > variables;

	check_formula(formula);
	// print column headers
	std::cout << "| ";
	for (char c : formula)
	{
		if (isalpha(c))
		{
			bool exist = false;
			for (size_t j = 0; j < variables.size(); ++j)
			{
				if (variables[j].first == c)
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				std::cout << c << " | ";
				variable_count++;
				variables.emplace_back(c, variable_count);
			}
		}
		else if (c == '0' || c == '1')
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
		temp_formula = formula;
		for (const auto& variable : variables)
		{
			size_t value = (i >> (variable.second - 1)) & 1;
			std::cout << value << " | ";
			std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(value + '0'));
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
					temp = stack.top(); stack.pop();
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

const std::string	RSB::negation_normal_form(const RPNNode* node, bool negate)
{
	std::string converted = "";

	if (node == nullptr)
		return "";
	if (const VariableNode* variable_node = dynamic_cast<const VariableNode*>(node))
	{
		std::cout << std::endl;
		std::cout << variable_node->get_variable() << std::endl;
		converted += variable_node->get_variable();
		if (negate)
			converted += '!';
	}
	else if (const UnaryOperatorNode* unary_node = dynamic_cast<const UnaryOperatorNode*>(node))
	{
		const RPNNode* operand = unary_node->get_operand();
        if (const VariableNode* operandVariableNode = dynamic_cast<const VariableNode*>(operand))
		{
            converted += operandVariableNode->get_variable();
            converted += unary_node->get_operator();
		}
        else if (const BinaryOperatorNode* operandBinaryNode = dynamic_cast<const BinaryOperatorNode*>(operand))
		{
			std::cout << std::endl;
			std::cout << operandBinaryNode->get_operator() << std::endl;
            converted += negation_normal_form(operandBinaryNode, true);
            converted += unary_node->get_operator();
		}
        else if (const UnaryOperatorNode* operandUnaryNode = dynamic_cast<const UnaryOperatorNode*>(operand))
		{
        	converted += negation_normal_form(operandUnaryNode, true);
            converted += unary_node->get_operator();
		}
		//std::cout << std::endl;
		//std::cout << unary_node->get_operand() << std::endl;
		//temp_node = unary_node->get_operand()
		//if (const VariableNode* operand_node = dynamic_cast<const VariableNode*>(unary_node->get_operand()))
		//{
        //    converted += operand_node->get_variable();
		//	std::cout << std::endl;
		//	std::cout << operand_node->get_variable() << std::endl;
		//}
        //else
        //    converted += negation_normal_form(unary_node->get_operand());
		//std::cout << std::endl;
		//std::cout << unary_node->get_operator() << std::endl;
		converted += unary_node->get_operator();
		//converted += negation_normal_form(unary_node->get_operand());
	}
	else if (const BinaryOperatorNode* binary_node = dynamic_cast<const BinaryOperatorNode*>(node))
	{
		//std::cout << std::endl;
		//std::cout << binary_node->get_left() << std::endl;
		std::string left = negation_normal_form(binary_node->get_left());
		std::cout << "left:" << left << std::endl;
		std::string right = negation_normal_form(binary_node->get_right());
		if (negate) {
            converted += left + '!';
        } else {
            converted += left;
        }
		converted += binary_node->get_operator();
        converted += right;
	}
	return converted;
};

const std::string	RSB::conjunctive_normal_form(const std::string& formula)
{
	check_formula(formula);
	std::string temp_formula = negation_normal_form(formula);
	return NULL;
};

bool	RSB::sat(const std::string& formula)
{
	size_t variable_count = 0;
	size_t rows = 0;
	std::string temp_formula = formula;
	std::vector<std::pair<char, size_t> > variables;

	check_formula(formula);
	for (char c : formula)
	{
		if (isalpha(c))
		{
			bool exist = false;
			for (size_t j = 0; j < variables.size(); ++j)
			{
				if (variables[j].first == c)
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				variable_count++;
				variables.emplace_back(c, variable_count);
			}
		}
		else if (c == '0' || c == '1')
		{
			std::stringstream error_message;
			error_message << "Invalid symbol '" << c << "'";
			throw std::runtime_error(error_message.str());
		}
	}
	rows = 1 << variable_count;

	for (size_t i = 0; i < rows; ++i)
	{
		temp_formula = formula;
		for (const auto& variable : variables)
		{
			size_t value = (i >> (variable.second - 1)) & 1;
			std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(value + '0'));
		}
		if (eval_formula(temp_formula))
			return true;
	}
	return false;
};

void	RSB::generate_powerset(const std::vector<int>& set, std::vector<int>& current_set, int index, std::vector<std::vector<int> >& powerset)
{
	powerset.push_back(current_set);
	for (size_t i = index; i < set.size(); ++i)
	{
		current_set.push_back(set[i]);
		generate_powerset(set, current_set, i + 1, powerset);
		current_set.pop_back();
	}
};

std::vector<std::vector<int> >	RSB::powerset(std::vector<int>& set)
{
	std::vector<std::vector<int> > powerset;
	std::vector<int> current_set;

	generate_powerset(set, current_set, 0, powerset);
	return powerset;
};
/*
std::vector<int>	RSB::eval_set(const std::string& formula, const std::vector<std::vector<int> >& sets)
{

};
*/
