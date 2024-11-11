#include <iostream>


enum class DataType
{
	INTEGER,
	DOUBLE,
	CHAR,
};

class VPointerArray
{
	void** Parray;
	int size;
public:
	VPointerArray(int size): size(size)
	{
		Parray = new void* [size];
	}

	void SetValue(void *data, int indx)
	{
		if (indx < size)
		{
			Parray[indx] = data;
		}
	}
	
	void *getValue(int indx)
	{
		if (indx < size)
		{
			return Parray[indx];
		}
	}
	
	int getSize()
	{
		return size;
	}

	DataType getDataType(int indx)
	{
		if (typeid(Parray[indx]) == typeid(int)) {
			return DataType::INTEGER;
		}
		else if (typeid(Parray[indx]) == typeid(double)) {

			return DataType::DOUBLE;
		}
		else if (typeid(Parray[indx]) == typeid(char)) {

			return DataType::CHAR;
		}

	}

	

	~VPointerArray()
	{
		delete[]Parray;
	}



};



int main()
{
	VPointerArray v(3);
	int n = 5;
	double d = 5.3;
	char n2 = 2;

	v.SetValue(&n, 0);
	v.SetValue(&d, 1);
	v.SetValue(&n2, 2);




	 void *r = v.getValue(0);
	 DataType a = v.getDataType(0);
	 switch (a)
	 {
	 case DataType::INTEGER:
		 std::cout << *((int*)r) << std::endl;
		 break;
	 case DataType::DOUBLE:
		 std::cout << *((double*)r) << std::endl;
		 break;
	 case DataType::CHAR:
		 std::cout << *((char*)r) << std::endl;
		 break;
	 default:
		 break;
	 }


}
