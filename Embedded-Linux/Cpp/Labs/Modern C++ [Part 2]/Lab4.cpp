#include <iostream>

class Pair
{
	int first;
	int second;
public:

	Pair():first(0),second(0) { }

	Pair(int first, int second): first(first), second(second) {	}

	void setFirst(int first)
	{
		this->first = first;
	}

	int getFirst()
	{
		return first;
	}

	void setSecond(int second)
	{
		this->second = second;
	}

	int getSecond()
	{
		return second;
	}

	void swap(void)
	{
		int tmp = first;
		first = second;
		second = tmp;
	}

	void setPairs(int first, int second)
	{
		this->first = first;
		this->second = second;
	}

	void PrintPair()
	{
		std::cout << "First: " << first;
		std::cout << "  Second: " << second << std::endl;
	}

	~Pair()
	{
	}



};


int main()
{
	Pair P{ 20, 50 };
	P.PrintPair();

	Pair P1;
	P1.PrintPair();
	
	P1.setPairs(23, 41);
	P1.PrintPair();

	P1.setFirst(99);
	P1.PrintPair();

	P1.setSecond(50);
	P1.PrintPair();

	P1.swap();
	P1.PrintPair();

	

	

}
