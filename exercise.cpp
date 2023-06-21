#include "ReadySetBoole.hpp"
#include "RPNtree.hpp"
#include "exercise.hpp"

static bool	parse_formula(const std::string& formula)
{
	std::unique_ptr<RPNNode> rpn;
	try
	{
 		rpn = build_tree(formula);
		std::cout << "formula: ";
        print_node(rpn.get());

        print_tree(rpn.get());
		std::cout << std::endl;
    } catch (const std::runtime_error& e)
	{
        std::cerr << "Error: " << e.what() << std::endl;
		return false;
    }
	return true;
}

void	ex00(int argc, char** argv)
{
	std::cout << "Running ex00 - adder..." << std::endl;
	RSB rsb;
	if (argc == 4)
	{
		std::cout << GREEN << std::atoi(argv[2]) << " + " << std::atoi(argv[3]) << " = ";
		std::cout << rsb.adder(std::atoi(argv[2]), std::atoi(argv[3])) << FIN << std::endl;
	}
}

void	ex01(int argc, char** argv)
{
	std::cout << "Running ex01 - multiplier..." << std::endl;
	RSB rsb;
	if (argc == 4)
	{
		std::cout << GREEN << std::atoi(argv[2]) << " * " << std::atoi(argv[3]) << " = ";
		std::cout << rsb.multiplier(std::atoi(argv[2]), std::atoi(argv[3])) << FIN << std::endl;
	}
}

void	ex02(int argc, char** argv)
{
	std::cout << "Running ex02 - gray code..." << std::endl;
	RSB rsb;
	if (argc == 2)
	{
		std::cout << GREEN << rsb.gray_code(0) << FIN << std::endl; // 0
		std::cout << GREEN << rsb.gray_code(1) << FIN << std::endl; // 1
		std::cout << GREEN << rsb.gray_code(2) << FIN << std::endl; // 3
		std::cout << GREEN << rsb.gray_code(3) << FIN << std::endl; // 2
		std::cout << GREEN << rsb.gray_code(4) << FIN << std::endl; // 6
		std::cout << GREEN << rsb.gray_code(5) << FIN << std::endl; // 7
		std::cout << GREEN << rsb.gray_code(6) << FIN << std::endl; // 5
		std::cout << GREEN << rsb.gray_code(7) << FIN << std::endl; // 4
		std::cout << GREEN << rsb.gray_code(8) << FIN << std::endl; // 12
	}
	else
		std::cout << GREEN << rsb.gray_code(std::atoi(argv[2])) << FIN << std::endl;
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
		std::cout << GREEN << rsb.eval_formula("10&") << FIN << std::endl;     // false
   		std::cout << GREEN << rsb.eval_formula("10|") << FIN << std::endl;     // true
   		std::cout << GREEN << rsb.eval_formula("11>") << FIN << std::endl;     // true
   		std::cout << GREEN << rsb.eval_formula("10=") << FIN << std::endl;     // false
   		std::cout << GREEN << rsb.eval_formula("1011||=") << FIN << std::endl; // true
	}
	else
   		std::cout << GREEN << rsb.eval_formula(formula) << FIN << std::endl;
}

void	ex04(int argc, char** argv)
{
	std::cout << "Running ex04 - truth table..." << std::endl;
	std::string	formula;
	RSB			rsb;

	if (argc >= 3)
 		formula = (std::string)argv[2];
	if (formula.empty())
		rsb.print_truth_table("AB&C|");
	else
	{
		if (!parse_formula(formula))
			return ;
		rsb.print_truth_table(formula);
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
		std::cout << GREEN << rsb.negation_normal_form("AB&!") << FIN << std::endl;
		std::cout << GREEN << rsb.negation_normal_form("AB|!") << FIN << std::endl;
		std::cout << GREEN << rsb.negation_normal_form("AB>") << FIN << std::endl;
		std::cout << GREEN << rsb.negation_normal_form("AB=") << FIN << std::endl;
		std::cout << GREEN << rsb.negation_normal_form("AB|C&!") << FIN << std::endl;
	}
	else
	{
		if (!parse_formula(formula))
			return ;
		std::cout << GREEN << rsb.negation_normal_form(formula) << FIN << std::endl;
	}
}

void	ex05(const RPNNode* node)
{
	std::cout << "Running ex05 - negation normal form..." << std::endl;
	RSB rsb;
	if (node != nullptr)
		std::cout << GREEN << rsb.negation_normal_form(node) << FIN << std::endl;
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
		std::cout << GREEN << rsb.conjunctive_normal_form("AB&!") << FIN << std::endl; // A!B!|
		std::cout << GREEN << rsb.conjunctive_normal_form("AB|!") << FIN << std::endl; // A!B!&
		std::cout << GREEN << rsb.conjunctive_normal_form("AB|C&") << FIN << std::endl; // AB|C&
		std::cout << GREEN << rsb.conjunctive_normal_form("AB|C|D|") << FIN << std::endl; // ABCD|||
		std::cout << GREEN << rsb.conjunctive_normal_form("AB&C&D&") << FIN << std::endl; // ABCD&&&
		std::cout << GREEN << rsb.conjunctive_normal_form("AB&!C!|") << FIN << std::endl; // A!B!C!||
		std::cout << GREEN << rsb.conjunctive_normal_form("AB|!C!&") << FIN << std::endl; // A!B!C!&&
	}
	else
	{
		if (!parse_formula(formula))
			return ;
		std::cout << GREEN << rsb.conjunctive_normal_form(formula) << FIN << std::endl;
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
		std::cout << GREEN << rsb.sat("AB|") << FIN << std::endl; // true
		std::cout << GREEN << rsb.sat("AB&") << FIN << std::endl; // true
		std::cout << GREEN << rsb.sat("AA!&") << FIN << std::endl; // false
		std::cout << GREEN << rsb.sat("AA^") << FIN << std::endl; // false
	}
	else
	{
		if (!parse_formula(formula))
			return ;
		std::cout << GREEN << rsb.sat(formula) << FIN << std::endl;
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

static std::vector<int>	parse_set(const char* str)
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

static bool	check_sets(const std::string& formula, const t_powerset sets, std::vector<char>& variables)
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
		sets.push_back(parse_set(argv[i]));	
	if (!parse_formula(formula))
		return ;
	if (!check_sets(formula, sets, variables))
		return ;
	for (size_t i = 0; i < sets.size(); ++i)
	{
		if (sets.size())
			std::cout << variables[i] << ": " << sets[i] << std::endl;
	}
	std::cout << GREEN << rsb.eval_set(formula, sets) << FIN << std::endl;
}

void	ex10(int argc, char** argv)
{
	std::cout << "Running ex10 - curve..." << std::endl;
	(void)argc; (void)argv;
}

void	ex11(int argc, char** argv)
{
	std::cout << "Running ex11 - inverse function..." << std::endl;
	(void)argc; (void)argv;
}
