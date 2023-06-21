#ifndef EXERCISE_HPP
#define EXERCISE_HPP

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
void	ex10(int argc, char** argv);
void	ex11(int argc, char** argv);

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
#endif
