#ifndef READYSETBOOLE_HPP
#define READYSETBOOLE_HPP
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <unordered_set>
#include "Tokenizer.hpp"
#include "RPNtree.hpp"

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
	// ex04 Truth table  O(2^n) / NA
	void	printTruthTable(const std::string& formula, bool ordered = false);
	// ex05 Negation Normal Form
	const std::string	negationNormalForm(const std::string& formula);
	// ex06 Conjunctive Normal Form
	const std::string	conjunctiveNormalForm(const std::string& formula);
	// ex07 SAT  O(2^n) / NA
	bool	sat(const std::string& formula);
	// ex08 Powerset  NA / O(2^n)
	t_powerset	powerset(t_set& set);
	// ex09 Set evaluation
	t_set	evalSet(const std::string& formula, const t_powerset& sets);
	// ex10 Curve
	double	map(unsigned short x, unsigned short y);
	// ex11 Inverse function
	t_vec2s	reverseMap(double n);
};

#endif
