#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

namespace MathFunctions
{
	void print(double n)
	{
		std::cout << "Square root: " << std::sqrt(n) << std::endl;
	}
}


namespace StringFunctions
{
	void print(std::string s)
	{
		std::transform(s.begin(), s.end(), s.begin(), ::toupper);
		std::cout << s << std::endl;

	}
}


namespace ArrayFunctions
{
	void print(int* arr, int size)
	{
		for (int i = size - 1; i >= 0 ; i--)
		{
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;
	}
}

namespace DynamicAlloc
{
	void create2DArray(int** arr, int row, int col)
	{
		arr = new int* [row];
		for (int i = 0; i < row; i++)
		{
			arr[i] = new int[col];
		}
	}

	void delete2DArray(int** arr, int row, int col)
	{
		for (int i = 0; i < row; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;
	}


	void Print(int** arr, int row, int col)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				std::cout << arr[i][j] << " ";
			}
			std::cout << std::endl ;
		}
	}
}

int main() {
	double n = 15;
	std::string s = "mina magdy";
	int arr[5]{ 1, 2, 3, 4, 5 };
	
	MathFunctions::print(n);

	StringFunctions::print(s);

	ArrayFunctions::print(arr, 5);


	int** ar = nullptr;
	DynamicAlloc::create2DArray(ar, 5, 6);
	
	
	DynamicAlloc::delete2DArray(ar, 5, 6);

	return 0;
}