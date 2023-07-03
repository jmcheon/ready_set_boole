#include "exercise.hpp"

std::ostream&	operator<<(std::ostream& cout, const t_vec2s& tuple)
{
	return cout << "( " << tuple.x << ", " << tuple.y << " )";
}

void	ex00(int argc, char** argv)
{
	std::cout << "Running ex00 - adder..." << std::endl;
	RSB rsb;
	if (argc == 4)
	{
		std::cout << std::atoi(argv[2]) << " + " << std::atoi(argv[3]) << " = ";
		std::cout << GREEN << rsb.adder(std::atoi(argv[2]), std::atoi(argv[3])) << FIN << std::endl;
	}
}

void	ex01(int argc, char** argv)
{
	std::cout << "Running ex01 - multiplier..." << std::endl;
	RSB rsb;
	if (argc == 4)
	{
		std::cout << std::atoi(argv[2]) << " * " << std::atoi(argv[3]) << " = ";
		std::cout << GREEN << rsb.multiplier(std::atoi(argv[2]), std::atoi(argv[3])) << FIN << std::endl;
	}
}

void	ex02(int argc, char** argv)
{
	std::cout << "Running ex02 - gray code..." << std::endl;
	RSB rsb;
	if (argc == 2)
	{
		std::cout << "0 -> " <<  GREEN << rsb.grayCode(0) << FIN << std::endl; // 0
		std::cout << "1 -> " <<  GREEN << rsb.grayCode(1) << FIN << std::endl; // 1
		std::cout << "2 -> " <<  GREEN << rsb.grayCode(2) << FIN << std::endl; // 3
		std::cout << "3 -> " <<  GREEN << rsb.grayCode(3) << FIN << std::endl; // 2
		std::cout << "4 -> " <<  GREEN << rsb.grayCode(4) << FIN << std::endl; // 6
		std::cout << "5 -> " <<  GREEN << rsb.grayCode(5) << FIN << std::endl; // 7
		std::cout << "6 -> " <<  GREEN << rsb.grayCode(6) << FIN << std::endl; // 5
		std::cout << "7 -> " <<  GREEN << rsb.grayCode(7) << FIN << std::endl; // 4
		std::cout << "8 -> " <<  GREEN << rsb.grayCode(8) << FIN << std::endl; // 12
	}
	else
		std::cout << argv[2] << " -> " << GREEN << rsb.grayCode(std::atoi(argv[2])) << FIN << std::endl;
}

void	ex03(int argc, char** argv)
{
	std::cout << "Running ex03 - boolean evaluation..." << std::endl;
	std::string	formula;
	RSB			rsb;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (formula.empty())
	{
		std::cout << "10& -> " << GREEN << rsb.evalFormula("10&") << FIN << std::endl;     // false
   		std::cout << "10| -> " << GREEN << rsb.evalFormula("10|") << FIN << std::endl;     // true
   		std::cout << "11> -> " << GREEN << rsb.evalFormula("11>") << FIN << std::endl;     // true
   		std::cout << "10= -> " << GREEN << rsb.evalFormula("10=") << FIN << std::endl;     // false
   		std::cout << "1011||= -> " << GREEN << rsb.evalFormula("1011||=") << FIN << std::endl; // true
	}
	else
   		std::cout << formula << " -> " << GREEN << rsb.evalFormula(formula) << FIN << std::endl;
}

void	ex04(int argc, char** argv)
{
	std::cout << "Running ex04 - truth table...\n" << std::endl;
	std::string	formula;
	RSB			rsb;
	bool		ordered = false;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (argc == 4)
		ordered = argv[3];
	if (formula.empty())
	{
		std::cout << "formula: AB&C|\n" << std::endl;
		rsb.printTruthTable("AB&C|", ordered);
	}
	else
	{
		if (!checkFormula(formula, true, false))
			return ;
		rsb.printTruthTable(formula, ordered);
	}
}

void	ex05(int argc, char** argv)
{
	std::cout << "Running ex05 - negation normal form..." << std::endl;
	std::string	formula;
	RSB			rsb;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (formula.empty())
	{
		std::cout << "AB&! -> " << GREEN << rsb.negationNormalForm("AB&!") << FIN << std::endl;
		std::cout << "AB|! -> " << GREEN << rsb.negationNormalForm("AB|!") << FIN << std::endl;
		std::cout << "AB^ -> " << GREEN << rsb.negationNormalForm("AB>") << FIN << std::endl;
		std::cout << "AB= -> " << GREEN << rsb.negationNormalForm("AB=") << FIN << std::endl;
		std::cout << "AB|C&! -> " << GREEN << rsb.negationNormalForm("AB|C&!") << FIN << std::endl;
	}
	else
	{
		if (!checkFormula(formula))
			return ;
		std::cout << formula << " -> " << GREEN << rsb.negationNormalForm(formula) << FIN << std::endl;
	}
}

void	ex06(int argc, char** argv)
{
	std::cout << "Running ex06 - conjunctive normal form..." << std::endl;
	std::string	formula;
	RSB			rsb;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (formula.empty())
	{
		std::cout << "AB&! -> " << GREEN << rsb.conjunctiveNormalForm("AB&!") << FIN << std::endl; // A!B!|
		std::cout << "AB|! -> " << GREEN << rsb.conjunctiveNormalForm("AB|!") << FIN << std::endl; // A!B!&
		std::cout << "AB|C& -> " << GREEN <<  rsb.conjunctiveNormalForm("AB|C&") << FIN << std::endl; // AB|C&
		std::cout << "AB|C|D| -> " << GREEN << rsb.conjunctiveNormalForm("AB|C|D|") << FIN << std::endl; // ABCD|||
		std::cout << "AB&C&D& -> " << GREEN << rsb.conjunctiveNormalForm("AB&C&D&") << FIN << std::endl; // ABCD&&&
		std::cout << "AB&!C!| -> " << GREEN << rsb.conjunctiveNormalForm("AB&!C!|") << FIN << std::endl; // A!B!C!||
		std::cout << "AB|!C!& -> " << GREEN << rsb.conjunctiveNormalForm("AB|!C!&") << FIN << std::endl; // A!B!C!&&
	}
	else
	{
		if (!checkFormula(formula))
			return ;
		//formula = "A!BC!||AB!C!||A!B!C!||&&";
		if (argc == 4)
			std::cout << rsb.conjunctiveNormalForm(formula) << std::endl;
		else
			std::cout << formula << " -> " << GREEN << rsb.conjunctiveNormalForm(formula) << FIN << std::endl;
	}
}

void	ex07(int argc, char** argv)
{
	std::cout << "Running ex07 - sat..." << std::endl;
	std::string	formula;
	RSB			rsb;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (formula.empty())
	{
		std::cout << "AB| -> " << GREEN << rsb.sat("AB|") << FIN << std::endl; // true
		std::cout << "AB& -> " << GREEN << rsb.sat("AB&") << FIN << std::endl; // true
		std::cout << "AA!& -> " << GREEN << rsb.sat("AA!&") << FIN << std::endl; // false
		std::cout << "AA^ -> " << GREEN << rsb.sat("AA^") << FIN << std::endl; // false
	}
	else
	{
		if (!checkFormula(formula))
			return ;
		std::cout << formula << " -> " << GREEN << rsb.sat(formula) << FIN << std::endl;
	}
}

void	ex08(int argc, char** argv)
{
	std::cout << "Running ex08 - powerset..." << std::endl;
	RSB rsb;
	//std::cout << "argc:" << argc << std::endl;
	std::vector<int> set(argc - 2);
	for (int i = 2; i < argc; ++i)
		set[i - 2] = std::atoi(argv[i]);
	std::vector<std::vector<int> > powerset = rsb.powerset(set);
	std::cout << set.size() << " - " << set << std::endl;
	std::cout << powerset.size() << " - " << powerset << std::endl;
}

static std::vector<int>	parseSet(const char* str)
{
	t_set set;

	while(*str)
	{
		set.push_back(std::atoi(str));
		while (*str && *str != ',')
			str++;
		if (*str == ',')
			str++;
	}
	return set;
}

static bool	checkSets(const std::string& formula, const t_powerset sets, std::vector<char>& variables)
{
	size_t variable_count = 0;

	for (char c : formula)
	{
		if (isalpha(c))
		{
			bool exist = false;
			for (size_t j = 0; j < variables.size(); ++j)
			{
				if (variables[j] == c)
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				variable_count++;
				variables.emplace_back(c);
			}
		}
	}
	if (sets.size() != variable_count)
	{
		std::cout << RED << "Error: Sets size and variable numbers don't match." << FIN << std::endl;
		return false;
	}
	return true;
}

void	ex09(int argc, char** argv)
{
	std::cout << "\nRunning ex09 - set evaluation..." << std::endl;
	const std::string	formula = (std::string)argv[2];
	t_powerset			sets;
	std::vector<char>	variables;
	RSB					rsb;

	for (int i = 3; i < argc; ++i)
		sets.push_back(parseSet(argv[i]));	
	if (!checkFormula(formula))
		return ;
	if (!checkSets(formula, sets, variables))
		return ;
	for (size_t i = 0; i < sets.size(); ++i)
	{
		if (sets.size())
			std::cout << variables[i] << ": " << sets[i] << std::endl;
	}
	std::cout << GREEN << rsb.evalSet(formula, sets) << FIN << std::endl;
}

void	ex10_11(int argc, char** argv)
{
	std::cout << "Running ex10, ex11 - curve & inverse function..." << std::endl;
	RSB		rsb;
	t_vec2s	input;
	t_vec2s	reversed;
	double	n;

	if (argc == 4)
	{
		input.x = std::atoi(argv[2]);
		input.y = std::atoi(argv[3]);

		std::cout << "( " << argv[2] << ", " << argv[3] << " )" << std::endl;

		n = rsb.map(input.x, input.y);
		reversed = rsb.reverseMap(n);
		if (n >=0 && n <=1)
			std::cout << GREEN << "range:   " << n << FIN << std::endl;
		else
			std::cout << RED << "range: " << n << " NOT OK" << FIN << std::endl;
		if (reversed.x == input.x && reversed.y == input.y)
			std::cout << GREEN << "reverse: " << reversed << FIN << std::endl;
		else
			std::cout << RED << "reverse: " << reversed << " NOT OK" << FIN << std::endl;
	}
}
