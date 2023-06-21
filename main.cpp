#include "ReadySetBoole.hpp"
#include "RPNtree.hpp"

void	ex00()
{
	std::cout << "Running ex00 - adder..." << std::endl;
	RSB rsb;
	int number1, number2;

	std::cout << "Enter the first number: ";
	std::cin >> number1;
	
	std::cout << "Enter the second number: ";
	std::cin >> number2;
	
	std::cout << number1 << " + " << number2 << " = ";
	std::cout << rsb.adder(number1, number2) << std::endl;
}

void	ex01()
{
	std::cout << "Running ex01 - multiplier..." << std::endl;
	RSB rsb;
	int number1, number2;

	std::cout << "Enter the first number: ";
	std::cin >> number1;
	
	std::cout << "Enter the second number: ";
	std::cin >> number2;
	
	std::cout << number1 << " * " << number2 << " = ";
	std::cout << rsb.multiplier(number1, number2) << std::endl;
}

void	ex02()
{
	std::cout << "Running ex02 - gray code..." << std::endl;
	RSB rsb;
	std::cout << rsb.gray_code(0) << std::endl; // 0
	std::cout << rsb.gray_code(1) << std::endl; // 1
	std::cout << rsb.gray_code(2) << std::endl; // 3
	std::cout << rsb.gray_code(3) << std::endl; // 2
	std::cout << rsb.gray_code(4) << std::endl; // 6
	std::cout << rsb.gray_code(5) << std::endl; // 7
	std::cout << rsb.gray_code(6) << std::endl; // 5
	std::cout << rsb.gray_code(7) << std::endl; // 4
	std::cout << rsb.gray_code(8) << std::endl; // 12
}

void	ex03(const std::string& formula)
{
	std::cout << "Running ex03 - boolean evaluation..." << std::endl;
	RSB rsb;
	if (formula.empty())
	{
		std::cout << rsb.eval_formula("10&") << std::endl;     // false
   		std::cout << rsb.eval_formula("10|") << std::endl;     // true
   		std::cout << rsb.eval_formula("11>") << std::endl;     // true
   		std::cout << rsb.eval_formula("10=") << std::endl;     // false
   		std::cout << rsb.eval_formula("1011||=") << std::endl; // true
	}
	else
   		std::cout << rsb.eval_formula(formula) << std::endl;
}

void	ex04(const std::string& formula)
{
	std::cout << "Running ex04 - truth table..." << std::endl;
	RSB rsb;
	if (formula.empty())
		rsb.print_truth_table("AB&C|");
	else
		rsb.print_truth_table(formula);
}

void	ex05(const std::string& formula)
{
	std::cout << "Running ex05 - negation normal form..." << std::endl;
	RSB rsb;
	if (formula.empty())
	{
		std::cout << rsb.negation_normal_form("AB&!") << std::endl;
		std::cout << rsb.negation_normal_form("AB|!") << std::endl;
		std::cout << rsb.negation_normal_form("AB>") << std::endl;
		std::cout << rsb.negation_normal_form("AB=") << std::endl;
		std::cout << rsb.negation_normal_form("AB|C&!") << std::endl;
	}
	else
		std::cout << rsb.negation_normal_form(formula) << std::endl;
}

void	ex05(const RPNNode* node)
{
	std::cout << "Running ex05 - negation normal form..." << std::endl;
	RSB rsb;
	if (node != nullptr)
		std::cout << rsb.negation_normal_form(node) << std::endl;
}

void	ex06(const std::string& formula)
{
	std::cout << "Running ex06 - conjunctive normal form..." << std::endl;
	RSB rsb;
	if (formula.empty())
	{
		std::cout << rsb.conjunctive_normal_form("AB&!") << std::endl; // A!B!|
		std::cout << rsb.conjunctive_normal_form("AB|!") << std::endl; // A!B!&
		std::cout << rsb.conjunctive_normal_form("AB|C&") << std::endl; // AB|C&
		std::cout << rsb.conjunctive_normal_form("AB|C|D|") << std::endl; // ABCD|||
		std::cout << rsb.conjunctive_normal_form("AB&C&D&") << std::endl; // ABCD&&&
		std::cout << rsb.conjunctive_normal_form("AB&!C!|") << std::endl; // A!B!C!||
		std::cout << rsb.conjunctive_normal_form("AB|!C!&") << std::endl; // A!B!C!&&
	}
	else
		std::cout << rsb.conjunctive_normal_form(formula) << std::endl;
}

void	ex07(const std::string& formula)
{
	std::cout << "Running ex07 - sat..." << std::endl;
	RSB rsb;
	if (formula.empty())
	{
		std::cout << rsb.sat("AB|") << std::endl; // true
		std::cout << rsb.sat("AB&") << std::endl; // true
		std::cout << rsb.sat("AA!&") << std::endl; // false
		std::cout << rsb.sat("AA^") << std::endl; // false
	}
	else
		std::cout << rsb.sat(formula) << std::endl;
}

template <class T>
std::ostream&	operator<<(std::ostream& cout, const std::vector<T>& vec){
	cout << "{ ";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (i)
			cout << ", ";
		cout << vec[i];
	}

	cout << " }";
	return cout;
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
	std::vector<int> result;

	//std::cout << *str << "|" << std::endl;
	while(*str)
	{
		result.push_back(std::atoi(str));
		while (*str && *str != ',')
			str++;
		if (*str == ',')
			str++;
	}
	//std::cout << result << std::endl;
	return result;
}

bool	parse_formula(const std::string& formula)
{
	std::unique_ptr<RPNNode> rpn;
	try
	{
		//std::cout << "check formula...\n";
 		rpn = build_tree(formula);
		std::cout << "formula: ";
        print_node(rpn.get());
		//std::cout << std::endl;

        print_tree(rpn.get());
		//std::cout << std::endl;

		//std::cout << "reversed formula:";
		//reverse_traversal(rpn.get());
		std::cout << std::endl;
    } catch (const std::runtime_error& e)
	{
        std::cerr << "Error: " << e.what() << std::endl;
		return false;
    }
	return true;
}

bool	check_sets(const std::string& formula, const std::vector<std::vector<int> > sets, std::vector<char>& variables)
{
	//std::vector<char> variables;
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
	const std::string formula = (std::string)argv[2];
	std::vector<std::vector<int> > sets;
	std::vector<char> variables;
	RSB rsb;

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

/*
	for (int i = 2; i < argc; ++i)
		set[i - 2] = std::atoi(argv[i]);
	std::vector<std::vector<int> > powerset = rsb.powerset(set);
	std::cout << set.size() << " - " << set << std::endl;
	std::cout << powerset.size() << " - " << powerset << std::endl;

	std::vector<int> sets = { {0, 1, 2}, {0, 3, 4} };
	std::cout << rsb.eval_set("AB&", &sets) << std::endl; // [0]

	sets = { {0, 1, 2}, {3, 4, 5} };
	std::cout << rsb.eval_set("AB|", &sets) << std::endl; // [0, 1, 2, 3, 4, 5]

	sets = {{0, 1, 2}};
	std::cout << rsb.eval_set("A!", &sets) << std::endl; // []
*/
}

void	ex10()
{
	std::cout << "Running ex10 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
}

void	ex11()
{
	std::cout << "Running ex11 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
}

void	execute_exercises(int argc, char** argv)
{
	std::string formula;
	std::unique_ptr<RPNNode> rpn;
	if (argc == 3)
	{
		formula = argv[2];
		try
		{
			std::cout << "check formula...\n";
			std::cout << "parsed formula:";
 			rpn = build_tree(formula);
    	    print_node(rpn.get());
			std::cout << std::endl;
    	    print_tree(rpn.get());
			std::cout << std::endl;
			std::cout << "reversed formula:";
			reverse_traversal(rpn.get());
			std::cout << std::endl;
    	    //print_tree(rpn.get());
    	} catch (const std::runtime_error& e)
		{
    	    std::cerr << "Error: " << e.what() << std::endl;
    	}
	}
	switch (atoi(argv[1]))
	{
		case 0:
			ex00();
			break;
		case 1:
			ex01();
			break;
		case 2:
			ex02();
			break;
		case 3:
			ex03(formula);
			break;
		case 4:
			ex04(formula);
			break;
		case 5:
			ex05(formula);
			//ex05(rpn.get());
			break;
		case 6:
			ex06(formula);
			break;
		case 7:
			ex07(formula);
			break;
		case 8:
			ex08(argc, argv);
			break;
		case 9:
			ex09(argc, argv);
			break;
		case 10:
			ex10();
			break;
		case 11:
			ex11();
			break;
		default:
			std::cout << "Usage: " << argv[0] << " [0 ~ 11]" << std::endl;
	}
}

void	execute_exercise(int argc, char** argv)
{
	std::string formula;
	std::string exercise;
	//std::function<void(const std::string&)> func_ptr;

	if (argc >= 2)
		exercise = argv[1];
	if (exercise == "ex03" || exercise == "ex04" || exercise == "ex05" || exercise == "ex06" || exercise == "ex07")
	{
		if (argc >= 3)
		{
			formula = argv[2];
			if (exercise != "ex03" && !parse_formula(formula))
				return ;
		}
		if (exercise == "ex03")
			ex03(formula);
		else if (exercise == "ex04")
			ex04(formula);
		else if (exercise == "ex05")
			ex05(formula);
		else if (exercise == "ex06")
			ex06(formula);
		else if (exercise == "ex07")
			ex07(formula);
	}
	else if (exercise == "ex08")
		ex08(argc, argv);
	else if (exercise == "ex09")
		ex09(argc, argv);
	else
		std::cout << "Usage: " << argv[0] << " [0 ~ 11]" << std::endl;
}

int	main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " [0 ~ 11]" << std::endl;
		return (0);
	}
	try {
		execute_exercise(argc, argv);
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	return (0);
}
