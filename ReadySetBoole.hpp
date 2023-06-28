#ifndef READYSETBOOLE_HPP
#define READYSETBOOLE_HPP
#include <iostream>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <vector>
#include "Tokenizer.hpp"
#include "RPNtree.hpp"
#include "exercise.hpp"

# define YELLOW "\033[0;38;5;220m"
# define GREEN "\033[0;38;5;42m"
# define RED "\033[0;38;5;196m"
# define BLUE "\033[0;38;5;21m"
# define PINK "\033[0;38;5;205m"
# define PURPLE "\033[0;38;5;93m"
# define ORANGE "\033[38;5;202m"
# define FIN "\033[0m"

# define MAX_EXERCISE_NUM 11

typedef std::vector<int> t_set;
typedef std::vector<std::vector<int> > t_powerset;
typedef struct s_vec2s
{
	unsigned short x;
	unsigned short y;
} t_vec2s;

class RSB
{
	public:
	// ex00 Adder O(1) / O(1)
	unsigned int adder(unsigned int a, unsigned int b);
	// ex01 Multiplier O(1) / O(1)
	unsigned int multiplier(unsigned int a, unsigned int b);
	// ex02 Gray code
	unsigned int grayCode(unsigned int n);
	// ex03 Boolean evaluation O(n) / NA
	bool	evalFormula(const std::string& formula);
	bool	evalOperator(char op, bool operand1, bool operand2);
	void	checkFormula(const std::string& formula);
	// ex04 Truth table  O(2^n) / NA
	void	printTruthTable(const std::string& formula);
	// ex05 Negation Normal Form
	std::string	negationNormalForm2(const std::string& formula);
	const std::string	simplifyForm(const std::string& formula);
	const std::string	negationNormalForm(const std::string& formula);
	const std::string	negationNormalForm(const RPNNode* node, bool negate=false);
	// ex06 Conjunctive Normal Form
	const std::string	conjunctiveNormalForm(const std::string& formula);
	// ex07 SAT  O(2^n) / NA
	bool	sat(const std::string& formula);
	// ex08 Powerset  NA / O(2^n)
	t_powerset	powerset(t_set& set);
	void	generatePowerset(const t_set& set, t_set& current_set, int index, t_powerset& powerset);
	// ex09 Set evaluation
	t_set	evalSet(const std::string& formula, const t_powerset& sets);
	// ex10 Curve
	double	map(unsigned short x, unsigned short y);
	// ex11 Inverse function
	t_vec2s	reverseMap(double n);
};

#endif
