#include <iostream>



class DynamicArray
{
private:
	int* Array;
	int capacity;
	int currentSize;

	void resize()
	{
		capacity *= 2;
		int* newArray = new int[capacity];
		for (int i = 0; i < currentSize; i++)
		{
			newArray[i] = Array[i];
		}

		delete[]Array;
		Array = newArray;
	}

public:

	DynamicArray() :capacity(1), currentSize(0)
	{
		Array = new int[capacity];
	}
	DynamicArray(int size) :capacity(size), currentSize(0)
	{
		Array = new int[capacity];
	}
	DynamicArray(int size, int value) :capacity(size), currentSize(size)
	{
		Array = new int[capacity];
		for (int i = 0; i < capacity; i++)
		{
			Array[i] = value;
		}
	}
	DynamicArray(int size, const int* values) :capacity(size), currentSize(size)
	{
		Array = new int[capacity];
		for (int i = 0; i < capacity; i++)
		{
			Array[i] = values[i];
		}
	}

	DynamicArray(std::initializer_list<int> list) :capacity(list.size()), currentSize(list.size())
	{
		Array = new int[capacity];
		for (auto& i : list)
		{
			Array[i] = i;
		}
	}

	DynamicArray(const DynamicArray& obj): capacity(obj.capacity), currentSize(obj.currentSize)
	{
		Array = new int[capacity];
		for (int i = 0; i < currentSize; i++)
		{
			Array[i] = obj.Array[i];
		}
	}

	~DynamicArray()
	{
		delete[]Array;
	}


	void pushback(int data)
	{
		if (capacity <= currentSize)
		{
			resize();
		}
		Array[currentSize++] = data;

	}

	void popback()
	{
		--currentSize;
	}

	void removeAt(int indx)
	{
		if (indx > 0 && indx < currentSize)
		{
			for (int i = indx; i < currentSize - 1; i++)
			{
				Array[i] = Array[i + 1];
			}
			--currentSize;
		}
	}

	void insertAt(int indx, int value)
	{
		if (indx > 0 && indx <= currentSize)
		{
			if (capacity == currentSize)
			{
				resize();
			}
			for (int i = currentSize; i > indx; --i)
			{
				Array[i] = Array[i - 1];
			}
			Array[indx] = value;
			++currentSize;

		}
	}


	void removeMiddle()
	{
		int indx = currentSize / 2;
		removeAt(indx);
	}

	void insertMiddle(int value)
	{
		int indx = currentSize / 2;
		insertAt(indx, value);
	}


	int size()
	{
		return currentSize;
	}

	void print()
	{
		for (int i = 0; i < currentSize; i++)
		{
			std::cout << Array[i] << " ";
		}
		std::cout << "\n=================================\n";

	}

	

	


};

int main() {
	DynamicArray arr1;
	arr1.pushback(1);
	arr1.pushback(2);
	arr1.pushback(3);
	arr1.pushback(4);
	arr1.pushback(5);
	arr1.print();
	arr1.insertAt(1, 99);
	arr1.print();
	arr1.insertMiddle(31);
	arr1.print();
	arr1.removeMiddle();
	arr1.print();
	arr1.removeAt(1);
	arr1.print();
	arr1.popback();
	arr1.print();
	
	std::cout << "\n\n";


	DynamicArray arr2(5, 10);
	arr2.print();
	std::cout << "\n\n";

	int values[] = { 1, 2, 3, 4, 5 };
	DynamicArray arr3(5, values);
	arr3.print();
	std::cout << "\n\n";

	DynamicArray arr4(arr3);
	arr4.print();
	std::cout << "\n\n";

	std::initializer_list<int> list{ 1,2,3,4 };
	DynamicArray arr5(arr1);
	arr5.print();


	return 0;
}