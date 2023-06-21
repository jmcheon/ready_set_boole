#include "ReadySetBoole.hpp"
#include "RPNtree.hpp"
#include "exercise.hpp"

void	execute_exercise(int argc, char** argv)
{
	void (*func_ptr[12])(int, char**);
	std::string exercise;
	size_t		exercise_number;

	func_ptr[0] = ex00;
	func_ptr[1] = ex01;
	func_ptr[2] = ex02;
	func_ptr[3] = ex03;
	func_ptr[4] = ex04;
	func_ptr[5] = ex05;
	func_ptr[6] = ex06;
	func_ptr[7] = ex07;
	func_ptr[8] = ex08;
	func_ptr[9] = ex09;
	func_ptr[10] = ex10;
	func_ptr[11] = ex11;

	exercise = argv[1];
	exercise_number = std::stoi(exercise.substr(2));
	if (exercise_number <= MAX_EXERCISE_NUM)
		func_ptr[exercise_number](argc, argv);
	else
		std::cout << "Usage: " << argv[0] << " [ex00 ~ ex11]" << std::endl;
}

int	main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " [ex00 ~ ex11]" << std::endl;
		return (0);
	}
	try
	{
		execute_exercise(argc, argv);
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
	return (0);
}
