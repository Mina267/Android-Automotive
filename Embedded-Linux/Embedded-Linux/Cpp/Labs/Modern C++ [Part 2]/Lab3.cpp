#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

namespace ArrayPair
{
	std::pair<int, int> *createArray(int size)
	{
		std::pair<int, int>* p = new std::pair<int, int>[size];
		return p;
	}
	void deleteArray(std::pair<int, int>* p)
	{
		delete[] p;
	}
	void setPair(std::pair<int, int>* p, int indx, int first, int second)
	{
		(p[indx]).first = first;
		p[indx].second = second;
	}

	std::pair<int, int> getPair(std::pair<int, int>* p, int indx)
	{
		return p[indx];
	}

	void printArray(std::pair<int, int>* p, int size)
	{
		for (auto i : p.begin())
		{

		}
		for (int i = 0; i < size; i++)
		{
			std::cout << " \n============\n";
			std::cout << i << " :First:  " << p[i].first;
			std::cout << std::endl;
			std::cout << i << " :Second: " << p[i].second;
			std::cout << std::endl;
			std::cout << " \n============\n";

		}


	}

}

int main() {

	std::pair<int, int>* p = ArrayPair::createArray(2);
	ArrayPair::setPair(p, 0, 1, 2);
	ArrayPair::setPair(p, 1, 5, 9);

	std::pair<int, int> n = ArrayPair::getPair(p, 0);
	std::cout << "First: " << n.first;
	std::cout << std::endl;
	std::cout << "Second: " << n.second;
	std::cout << std::endl;

	ArrayPair::printArray(p, 2);

	ArrayPair::deleteArray(p);

	return 0;
}