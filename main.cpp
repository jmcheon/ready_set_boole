#include "ReadySetBoole.hpp"

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

void	ex06()
{
	std::cout << "Running ex06 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
}

void	ex07()
{
	std::cout << "Running ex07 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
}

void	ex08()
{
	std::cout << "Running ex08 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
}

void	ex09()
{
	std::cout << "Running ex09 - truth table..." << std::endl;
	RSB rsb;
	rsb.print_truth_table("AB&C|");
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
	if (argc == 3)
		formula = argv[2];
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
			break;
		case 6:
			ex06();
			break;
		case 7:
			ex07();
			break;
		case 8:
			ex08();
			break;
		case 9:
			ex09();
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

int	main(int argc, char** argv)
{
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " [0 ~ 11]" << std::endl;
		return (0);
	}
	try {
		execute_exercises(argc, argv);
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	return (0);
}
