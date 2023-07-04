#ifndef EXERCISE_HPP
#define EXERCISE_HPP
#include <iostream>
#include <vector>
#include "ReadySetBoole.hpp"
#include "RPNtree.hpp"

# define YELLOW "\033[0;38;5;220m"
# define GREEN "\033[0;38;5;42m"
# define RED "\033[0;38;5;196m"
# define BLUE "\033[0;38;5;21m"
# define PINK "\033[0;38;5;205m"
# define PURPLE "\033[0;38;5;93m"
# define ORANGE "\033[38;5;202m"
# define FIN "\033[0m"

# define MAX_EXERCISE_NUM 11

void	ex00(int argc, char** argv);
void	ex01(int argc, char** argv);
void	ex02(int argc, char** argv);
void	ex03(int argc, char** argv);
void	ex04(int argc, char** argv);
void	ex05(int argc, char** argv);
void	ex06(int argc, char** argv);
void	ex07(int argc, char** argv);
void	ex08(int argc, char** argv);
void	ex09(int argc, char** argv);
void	ex10_11(int argc, char** argv);

void	runtimeException(const std::string& str, const std::string& value = std::string());
//std::ostream&	operator<<(std::ostream& cout, const t_vec2s& tuple);
template <class T>
std::ostream&	operator<<(std::ostream& cout, const std::vector<T>& vec)
{
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

#endif
