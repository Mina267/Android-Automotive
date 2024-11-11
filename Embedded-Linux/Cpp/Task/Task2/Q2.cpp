#include <iostream>
#include <string>


class Calculator
{
	double Add(double n1, double n2){
		return n1 + n2;
	}
	double Substruction(double n1, double n2){
		return n1 - n2;
	}
	double Multiplication(double n1, double n2){
		return n1 - n2;
	}
	double Division(double n1, double n2){
		if (n2 == 0) {
			std::cerr << "Error: Division by zero!" << std::endl;
			return 0;
		}
		return n1 / n2;
	}
	double power(double n1, double n2) {
		return std::pow(n1, n2);
	}
	double square_root(double a) {
		if (a < 0) {
			std::cerr << "Error: Negative value for square root!" << std::endl;
			return 0;
		}
		return std::sqrt(a);
	}
public:
	void Calculate(double n1, double n2, char Op)
	{
		switch (Op)
		{
		case '+':
			std::cout << "Result: " << Add(n1, n2) << std::endl;
			break;
		case '-':
			std::cout << "Result: " << Substruction(n1, n2) << std::endl;
			break;
		case '*':
			std::cout << "Result: " << Multiplication(n1, n2) << std::endl;
			break;
		case '/':
			std::cout << "Result: " << Division(n1, n2) << std::endl;
			break;
		case '^':
			std::cout << "Result: " << power(n1, n2) << std::endl;
			break;
		default:
			std::cerr << "Error: Invalid operator!" << std::endl;
			break;
		}
	}

	void Calculate(double n1, char Op)
	{
		switch (Op)
		{
		case 's':
			std::cout << "Result: " << square_root(n1) << std::endl;
			break;
		default:
			std::cerr << "Error: Invalid operator!" << std::endl;
			break;
		}
	}
	
};

int main() {
	Calculator calc;

	calc.Calculate(5, 3, '+');
	calc.Calculate(5, 3, '-');
	calc.Calculate(5, 3, '*');
	calc.Calculate(5, 3, '/');
	calc.Calculate(5, 3, '^');

	calc.Calculate(9, 's');

	return 0;
}