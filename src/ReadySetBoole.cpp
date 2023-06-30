#include "ReadySetBoole.hpp"

// ex00 Adder O(1) / O(1)
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

// ex01 Multiplier O(1) / O(1)
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

// ex02 Gray code
unsigned int RSB::grayCode(unsigned int n)
{
	// perform XOR operation between n and n shifted right by 1 bit
	return (n ^ (n >> 1));
};

static bool	evalOperator(char op, bool operand1, bool operand2)
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

static void	checkFormula(const std::string& formula)
{
	Tokenizer			tokenizer;
    std::vector<Token>	tokens = tokenizer.tokenize(formula);
    std::stack<char>	stack;
    char				op1, op2;

    //std::cout << "\n\t Formula syntax checking...\n";
    for (const Token& token : tokens)
	{
        switch (token.m_type)
		{
            case TokenType::VARIABLE:
				stack.push('1');
                break;
            case TokenType::BOOLEAN:
				stack.push(token.m_value);
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
					error_message << "Invalid syntax '" << token.m_value << "'";
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
					bool result = evalOperator(token.m_value, op1, op2);
					stack.push(result);
				}
				else
				{
					std::stringstream error_message;
					error_message << "Invalid syntax '" << token.m_value << "'";
					throw std::runtime_error(error_message.str());
				}
				break;
		}
	}
    if (stack.size() != 1)
		throw std::runtime_error("Invalid formula");
}

// ex03 Boolean evaluation O(n) / NA
bool	RSB::evalFormula(const std::string& formula)
{
	std::stack<bool>	eval_stack;
	
	checkFormula(formula);
	for (char c: formula)
	{
		if (std::isdigit(c))
		{
			bool m_value = c == '1';
			eval_stack.push(m_value);
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

			bool result = evalOperator(c, operand1, operand2);
			eval_stack.push(result);
		}
		else
			throw std::runtime_error("Invalid symbol");
	}
	return eval_stack.top();
};

static std::vector<std::pair<char, size_t> >	getVariables(const std::string& formula, bool ordered)
{
	std::vector<std::pair<char, size_t> > variables;
	size_t variable_count = 0;

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
	if (ordered)
	{
		std::sort(variables.begin(), variables.end(), [](auto& pair1, auto& pair2) {
			size_t temp;
	
			if (pair1.first < pair2.first)
			{
				temp = pair1.second;
				pair1.second = pair2.second;
				pair2.second = temp;
			}
			return pair1.first < pair2.first;
		});
	}
	return variables;
};

// ex04 Truth table  O(2^n) / NA
void	RSB::printTruthTable(const std::string& formula, bool ordered)
{
	std::vector<std::pair<char, size_t> > variables;
	std::string temp_formula;
	size_t variable_count = 0;
	size_t rows = 0;


	checkFormula(formula);
	variables = getVariables(formula, ordered);
	variable_count = variables.back().second;
	// print column headers
	std::cout << "| ";
	for (size_t i = 0; i <= variable_count - 1; ++i)
		std::cout << variables[i].first << " | ";
	std::cout << "= |\n";
	for (size_t i = 0; i <= variable_count; ++i)
		std::cout << "|---";
	std::cout << "|\n";
	rows = 1 << variable_count;

	for (size_t i = 0; i < rows; ++i)
	{
		std::cout << "| ";
		temp_formula = formula;
		for (const auto& variable : variables)
		{
			size_t m_value = (i >> (variable.second - 1)) & 1;
			std::cout << m_value << " | ";
			std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(m_value + '0'));
		}
		std::cout << evalFormula(temp_formula) << " |\n";
	}
};

static std::string	applyNegation(std::string& formula)
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

static const std::string	simplifyForm(const std::string& formula)
{
	std::stack<std::string> stack;
	std::string temp, temp2;

	for (char c : formula)
	{
		if (isalpha(c))
			stack.push(std::string(1, c));
		else if (c == '^' || c == '>' || c == '=')
		{
        	if (c == '^')
			{
        	    temp = stack.top(); stack.pop();
        	    temp2 = stack.top(); stack.pop();
        	    stack.push(temp2 + temp + "!&" + temp2 + "!" + temp + "&|");
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
		else if (c == '|' || c == '&')
		{
        	temp = stack.top(); stack.pop();
        	temp2 = stack.top(); stack.pop();
			stack.push(temp2 + temp + c);
		}
		else if (c == '!')
		{
        	temp = stack.top(); stack.pop();
			stack.push(temp + "!");
		}
	}
	return stack.top();
};

// ex05 Negation Normal Form
const std::string	RSB::negationNormalForm(const std::string& formula)
{
	std::stack<std::string> stack;
	std::string temp, temp2, temp_formula;

	checkFormula(formula);
	temp_formula = simplifyForm(formula);
	for (char c : temp_formula)
	{
		if (isalpha(c))
			stack.push(std::string(1, c));
		else if (c == '!')
		{
			if (!stack.empty())
			{
				temp = stack.top(); stack.pop();
				temp2 = applyNegation(temp);
				stack.push(temp2);
			}
		}
        else if (c == '&' || c == '|')
		{
        	temp = stack.top(); stack.pop();
        	temp2 = stack.top(); stack.pop();
        	stack.push(temp2 + temp + c);
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

bool is_operator(const char c)
{
    return c == '&' || c == '|';
}

int get_operator_priority(const char op)
{
    int priority = 0;

    if (op == '&')
        priority = 2;
    else if (op == '|')
        priority = 1;
    return priority;
}
static std::string 	rearrange(const std::string& formula)
{
    std::string result, disjunctions, conjunctions;

    for (char c : formula)
	{
        if (c == '&')
            conjunctions.push_back(c);
        else if (c == '|')
            disjunctions.push_back(c);
        else 
            result.push_back(c);
    }

    result += disjunctions + conjunctions;
    return result;
}

static std::string 	rearrange_formula(const std::string& formula)
{
	bool	disjunction, conjunction;

    for (char c : formula)
	{
        if (c == '&')
			conjunction = true;
        else if (c == '|')
			disjunction = true;
    }

	if (conjunction && !disjunction)
		return rearrange(formula);
	else if (!conjunction && disjunction)
		return rearrange(formula);
	return formula;
}

// ex06 Conjunctive Normal Form
const std::string	RSB::conjunctiveNormalForm(const std::string& formula)
{
	std::vector<std::pair<char, size_t> > variables;
	std::string temp_formula;
	std::string dnf;
	size_t variable_count = 0;
	size_t rows = 0;
	size_t zeros = 0;

	checkFormula(formula);
	variables = getVariables(formula, false);
	variable_count = variables.back().second;
	rows = 1 << variable_count;
	std::cout << std::endl;
	for (size_t i = 0; i < rows; ++i)
	{
		//std::cout << "| ";
		temp_formula = formula;
		std::string	temp;
		for (const auto& variable : variables)
		{
			size_t m_value = (i >> (variable.second - 1)) & 1;
			temp.push_back(m_value + '0');
			//std::cout << m_value << " | ";
			std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(m_value + '0'));
		}
		if (!evalFormula(temp_formula))
		{
			zeros++;
			size_t	i = 0;
			for (char c : temp)
			{
				if (isdigit(c))
				{
					if (c == '1')
						dnf += variables[i].first;
					else if (c == '0')
					{
						dnf += (variables[i].first);
						dnf += "!";
					}
					i++;
					if (i == variables.back().second)
						i = 0;
				}
			}
			for (size_t i = 0; i < variable_count - 1; ++i)
				dnf += "&";
		}
		//std::cout << evalFormula(temp_formula) << " |\n";
	}
	for (size_t i = 1; i < zeros; ++i)
		dnf += "|";
	dnf += "!";
	//std::cout << "dnf : " << dnf << std::endl;
	temp_formula = negationNormalForm(dnf);
	rearrange_formula(temp_formula);
	//return conjunctive_normal_form(temp_formula);
	//return rearrange_rpn(temp_formula);
	return temp_formula;
};

// ex07 SAT  O(2^n) / NA
bool	RSB::sat(const std::string& formula)
{
	std::vector<std::pair<char, size_t> > variables;
	std::string temp_formula = formula;
	size_t rows = 0;

	checkFormula(formula);
	variables = getVariables(formula, false);
	rows = 1 << variables.back().second;

	for (size_t i = 0; i < rows; ++i)
	{
		temp_formula = formula;
		for (const auto& variable : variables)
		{
			size_t m_value = (i >> (variable.second - 1)) & 1;
			std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(m_value + '0'));
		}
		if (evalFormula(temp_formula))
			return true;
	}
	return false;
};

static void	generatePowerset(const t_set& set, t_set& current_set, int index, t_powerset& powerset)
{
	powerset.push_back(current_set);
	for (size_t i = index; i < set.size(); ++i)
	{
		current_set.push_back(set[i]);
		generatePowerset(set, current_set, i + 1, powerset);
		current_set.pop_back();
	}
};

// ex08 Powerset  NA / O(2^n)
t_powerset	RSB::powerset(t_set& set)
{
	t_powerset	powerset;
	t_set		current_set;

	generatePowerset(set, current_set, 0, powerset);
	return powerset;
};

// ex09 Set evaluation
t_set	RSB::evalSet(const std::string& formula, const t_powerset& sets)
{
	std::stack<t_set>	stack;
	std::vector<char>	variables;
	std::string			temp_formula;
	t_set				universal_set;
	size_t				variable_count = 0;

	for (const t_set& set : sets)
	{
		for (int element : set)
		{
			if (std::find(universal_set.begin(), universal_set.end(), element) == universal_set.end())
                universal_set.push_back(element);
		}
	}

	temp_formula = negationNormalForm(formula);
	for (char c : temp_formula)
	{
		if (isalpha(c))
		{
			bool exist = false;
			for (size_t j = 0; j < variables.size(); ++j)
			{
				if (variables[j] == c)
				{
					exist = true;
					//std::cout << "sets[" << j << "]" << " - "; 
					//std::cout << c << ":" << sets[j] << std::endl; // debugging
					stack.push(sets[j]);
					break;
				}
			}
			if (!exist)
			{
				//std::cout << "sets[" << variable_count << "]" << " - ";
				//std::cout << c << ":" << sets[variable_count] << std::endl; // debugging
				stack.push(sets[variable_count]);
				variables.emplace_back(c);
				variable_count++;
			}
		}
		else if (c == '!') // Negation
		{
            t_set operand = stack.top(); stack.pop();
            t_set result;

            for (int element : universal_set)
			{
                if (std::find(operand.begin(), operand.end(), element) == operand.end())
                    result.push_back(element);
            }
			//std::cout << "\t mid neg result:" << result << std::endl; // debugging
            stack.push(result);
		}
		else if (c == '&' || c == '|' || c == '^' || c == '=' || c == '>')
		{
			t_set operand2 = stack.top(); stack.pop();
			t_set operand1 = stack.top(); stack.pop();
			t_set result;
			if (c == '&') // Intersection
			{
				std::unordered_map<int, bool> set1_elements;
				for (int element : operand1)
					set1_elements[element] = true;
				for (int element : operand2)
				{
					if (set1_elements[element])
						result.push_back(element);
				}
			}
			else if (c == '|') // Union
			{
				result = operand1;
				for (int element : operand2)
				{
					if (std::find(result.begin(), result.end(), element) == result.end())
						result.push_back(element);
				}
			}
			else if (c == '^') // Symmetric difference
			{
				std::unordered_map<int, bool> set1_elements;
				std::unordered_map<int, bool> set2_elements;

				for (int element : operand1)
					set1_elements[element] = true;
				for (int element : operand2)
				{
					if (!set1_elements[element])
						result.push_back(element);
				}
				for (int element : operand2)
					set2_elements[element] = true;
				for (int element : operand1)
				{
					if (!set2_elements[element])
						result.push_back(element);
				}
			}
			//std::cout << "\t mid result:" << result << std::endl; // debugging
			stack.push(result);
		}
	}
	return stack.top();
};
