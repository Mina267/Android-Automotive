#include <iostream>

template <typename T>
class Pair
{
	T first;
	T second;
public:

	Pair() :first("Mina"), second("Mina") { }

	Pair(T first, T second): first(first), second(second) {	}

	void setFirst(T first)
	{
		this->first = first;
	}

	T getFirst()
	{
		return first;
	}

	void setSecond(T second)
	{
		this->second = second;
	}

	T getSecond()
	{
		return second;
	}

	

	void setPairs(T first, T second)
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
	Pair<std::string> P{ "Mina", "Magdy"};
	P.PrintPair();

	Pair<std::string> P1;
	P1.PrintPair();
	
	P1.setPairs("Ali", "Alex");
	P1.PrintPair();

	P1.setFirst("John");
	P1.PrintPair();

	P1.setSecond("Will");
	P1.PrintPair();

	Pair<std::string> ar[5];
	ar[0].setFirst("Mina");
	ar[0].setFirst("Magdy");
	ar[0].PrintPair();

}
