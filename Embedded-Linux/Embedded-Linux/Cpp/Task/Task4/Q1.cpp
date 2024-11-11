#include <iostream>
#include <initializer_list>

template <typename T>
class DynamicArray
{
private:
    T* Array;
    int capacity;
    int currentSize;

    void resize()
    {
        capacity *= 2;
        T* newArray = new T[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            newArray[i] = Array[i];
        }

        delete[] Array;
        Array = newArray;
    }

public:
    DynamicArray() : capacity(1), currentSize(0)
    {
        Array = new T[capacity];
    }

    DynamicArray(int size) : capacity(size), currentSize(0)
    {
        Array = new T[capacity];
    }

    DynamicArray(int size, T value) : capacity(size), currentSize(size)
    {
        Array = new T[capacity];
        for (int i = 0; i < capacity; i++)
        {
            Array[i] = value;
        }
    }

    DynamicArray(int size, const T* values) : capacity(size), currentSize(size)
    {
        Array = new T[capacity];
        for (int i = 0; i < capacity; i++)
        {
            Array[i] = values[i];
        }
    }

    DynamicArray(std::initializer_list<T> list) : capacity(list.size()), currentSize(list.size())
    {
        Array = new T[capacity];
        int i = 0;
        for (const auto& val : list)
        {
            Array[i++] = val;
        }
    }

    DynamicArray(const DynamicArray& obj) : capacity(obj.capacity), currentSize(obj.currentSize)
    {
        Array = new T[capacity];
        for (int i = 0; i < currentSize; i++)
        {
            Array[i] = obj.Array[i];
        }
    }

    ~DynamicArray()
    {
        delete[] Array;
    }

    void pushback(T data)
    {
        if (capacity <= currentSize)
        {
            resize();
        }
        Array[currentSize++] = data;
    }

    void popback()
    {
        if (currentSize > 0)
        {
            --currentSize;
        }
    }

    void removeAt(int index)
    {
        if (index >= 0 && index < currentSize)
        {
            for (int i = index; i < currentSize - 1; i++)
            {
                Array[i] = Array[i + 1];
            }
            --currentSize;
        }
    }

    void insertAt(int index, T value)
    {
        if (index >= 0 && index <= currentSize)
        {
            if (capacity == currentSize)
            {
                resize();
            }
            for (int i = currentSize; i > index; --i)
            {
                Array[i] = Array[i - 1];
            }
            Array[index] = value;
            ++currentSize;
        }
    }

    void removeMiddle()
    {
        int index = currentSize / 2;
        removeAt(index);
    }

    void insertMiddle(T value)
    {
        int index = currentSize / 2;
        insertAt(index, value);
    }

    int size() const
    {
        return currentSize;
    }

    void print() const
    {
        for (int i = 0; i < currentSize; i++)
        {
            std::cout << Array[i] << " ";
        }
        std::cout << "\n=================================\n";
    }
};

int main()
{
    DynamicArray<int> arr1;
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

    DynamicArray<int> arr2(5, 10);
    arr2.print();
    std::cout << "\n\n";

    int values[] = { 1, 2, 3, 4, 5 };
    DynamicArray<int> arr3(5, values);
    arr3.print();
    std::cout << "\n\n";

    DynamicArray<int> arr4(arr3);
    arr4.print();
    std::cout << "\n\n";

    // std::initializer_list<int> list{ 1, 2, 3, 4 };
    DynamicArray<int> arr5(list);
    arr5.print();

    DynamicArray<char> charArr;
    charArr.pushback('a');
    charArr.pushback('b');
    charArr.pushback('c');
    charArr.print();

    DynamicArray<double> doubleArr;
    doubleArr.pushback(1.1);
    doubleArr.pushback(2.2);
    doubleArr.pushback(3.3);
    doubleArr.print();

    return 0;
}
