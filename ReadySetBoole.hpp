#ifndef READYSETBOOLE_HPP
#define READYSETBOOLE_HPP
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include "Tokenizer.hpp"
#include "RPNtree.hpp"

# define YELLOW "\033[0;38;5;220m"
# define GREEN "\033[0;38;5;42m"
# define RED "\033[0;38;5;196m"
# define BLUE "\033[0;38;5;21m"
# define PINK "\033[0;38;5;205m"
# define PURPLE "\033[0;38;5;93m"
# define ORANGE "\033[38;5;202m"
# define FIN "\033[0m"

# define NUMBER_OF_EXERCISE 11
//static const char* sExerciseStrings[] = {};

typedef std::vector<int> t_set;
typedef std::vector<std::vector<int> > t_powerset;

class RSB
{
	public:
	// ex00 Adder
	unsigned int adder(unsigned int a, unsigned int b);
	// ex01 Multiplier
	unsigned int multiplier(unsigned int a, unsigned int b);
	// ex02 Gray code
	unsigned int gray_code(unsigned int n);
	// ex03 Boolean evaluation
	bool	eval_formula(const std::string& formula);
	bool	eval_operator(char op, bool operand1, bool operand2);
	void	check_formula(const std::string& formula);
	// ex04 Truth table
	void	print_truth_table(const std::string& formula);
	// ex05 Negation Normal Form
	const std::string	negation_normal_form(const std::string& formula);
	const std::string	negation_normal_form(const RPNNode* node, bool negate=false);
	// ex06 Conjunctive Normal Form
	const std::string	conjunctive_normal_form(const std::string& formula);
	// ex07 SAT
	bool	sat(const std::string& formula);
	// ex08 Powerset
	t_powerset	powerset(t_set& set);
	void	generate_powerset(const t_set& set, t_set& current_set, int index, t_powerset& powerset);
	// ex09 Set evaluation
	t_set	eval_set(const std::string& formula, const t_powerset& sets);
	// ex10 Curve
	//f64	map(x: u16, y: u16);
	// ex11 Inverse function
	//(u16, u16)	reverse_map(n: f64);
};

#endif
