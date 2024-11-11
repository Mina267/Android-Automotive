#include <iostream>

template <typename T1, typename T2>
class KeyValuePair
{
	T1 Key;
	T2 Value;
public:

	KeyValuePair() = delete;
	KeyValuePair(T1 Key, T2 Value) : Key(Key), Value(Value) { }

	T1 getKey() { return Key; }
	T2 getValue() { return Value; }

	void setKey(T1 Key) { this->Key = Key; }
	void setValue() { this->Value = Value; }


	~KeyValuePair()
	{
	}


};



int main()
{
	KeyValuePair<int, std::string> a(100, "Mina");
	KeyValuePair<std::string, std::string> a("Mina", "Magdy");
	KeyValuePair<int, double> a(55, 5.5);



}
