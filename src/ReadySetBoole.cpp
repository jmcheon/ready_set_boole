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

// ex03 Boolean evaluation O(n) / NA
bool	RSB::evalFormula(const std::string& formula)
{
	std::stack<bool>	eval_stack;
	
	if (!checkFormula(formula, false, false))
		return false;
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


	if (!checkFormula(formula, true, false))
		return ;
	variables = getVariables(formula, ordered);
	variable_count = std::max_element(variables.begin(), variables.end(),
	[](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs) {
	    return lhs.second < rhs.second;
	})->second;
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
		//for (const auto& variable : variables)
		for (int j = variables.size() - 1; j >= 0; --j)
		{
			//size_t m_value = (i >> (variable.second - 1)) & 1;
			size_t m_value = (i >> (variables[j].second - 1)) & 1;
			std::cout << m_value << " | ";
			//std::replace(temp_formula.begin(), temp_formula.end(), variable.first, (char)(m_value + '0'));
			std::replace(temp_formula.begin(), temp_formula.end(), variables[j].first, (char)(m_value + '0'));
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
        	    //stack.push(temp2 + temp + "!&" + temp2 + "!" + temp + "&|");
        	    stack.push(temp2 + temp + "!|" + temp2 + "!" + temp + "|&");
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
        	    //std::string nnf = temp2 + temp + "&" + temp2 + "!" + temp + "!&|";
        	    std::string nnf = temp2 + "!" + temp + "|" + temp2 + temp + "!|&";
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

	if (!checkFormula(formula, true, false))
		return formula;
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

static std::string 	rearrangeOnlyAndOr(const std::string& formula)
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

static bool checkAndBeforeOr(const std::string& formula)
{
	bool	or_op = false;
	bool	and_op = false;

	(void)or_op;
	for (char c : formula)
	{
		if (c == '&')
			and_op = true;
		if (c == '|')
		{
			if (and_op)
				return true;
			or_op = true;
		}

	}
    return false;
}

// ex06 Conjunctive Normal Form
const std::string	RSB::conjunctiveNormalForm(const std::string& formula)
{
	std::unique_ptr<RPNNode>	cnf;
	std::string temp_formula;
	std::string result;

	if (!checkFormula(formula, true, false))
		return formula;
	temp_formula = negationNormalForm(formula);
	temp_formula = rearrangeOnlyAndOr(temp_formula);
	//std::cout << temp_formula << std::endl;
	cnf = buildTree(temp_formula);
	//printTree(cnf.get(), true);
	if (checkAndBeforeOr(temp_formula))
	{
		cnf = buildTree(temp_formula);
		cnf = applyDistributiveLaw(cnf);
		//std::cout << std::endl;
		//printTree(cnf.get(), true);
		result = preorder(cnf);
	}
	else
		result = temp_formula;
	cnf = apply(cnf);
	if (cnf != nullptr)
		result = preorder(cnf);

	return result;
};

// ex07 SAT  O(2^n) / NA
bool	RSB::sat(const std::string& formula)
{
	std::vector<std::pair<char, size_t> > variables;
	std::string temp_formula = formula;
	size_t variable_count = 0;
	size_t rows = 0;

	if (!checkFormula(formula, true, false))
		return false;
	variables = getVariables(formula, false);
	variable_count = std::max_element(variables.begin(), variables.end(),
	[](const std::pair<char, size_t>& lhs, const std::pair<char, size_t>& rhs) {
	    return lhs.second < rhs.second;
	})->second;
	rows = 1 << variable_count;

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

// ex10 Curve
double	RSB::map(unsigned short x, unsigned short y)
{
	// combine x and y into a 64-bit value
	unsigned long long value = (static_cast<unsigned long long>(x) << 16) | y;
	// map the value to the range [0; 1]
    double result = static_cast<double>(value) / MAX_VALUE;

    return result;
};

// ex11 Inverse function
t_vec2s	RSB::reverseMap(double n)
{
	// reverse normalize the value
    unsigned long long value = static_cast<unsigned long long>(n * MAX_VALUE);
	// extract the x coordinate
    unsigned short x = static_cast<unsigned short>(value >> 16);
	// extract the y coordinate
    unsigned short y = static_cast<unsigned short>(value & 0xFFFF);
	
	t_vec2s result;
	result.x = x;
	result.y = y;
	
	return result;
};
