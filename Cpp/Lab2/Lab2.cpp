#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>


typedef struct
{
    int* Arr;
    int size;
    int Actualsize;

}Vector_t;


void DynamicArray(Vector_t *pV, int Size)
{
    pV->size = Size;
    pV->Actualsize = pV->size + 10;

    pV->Arr = (int*)malloc(sizeof(int) * pV->Actualsize);
    std::cout << "Enter data : ";
    for (int i = 0; i < pV->size; i++)
    {
        std::cin >> pV->Arr[i];
    }
}


int insert(Vector_t* pV, int index, int n)
{
    int Status = 1;
    if (index < pV->size)
    {
        pV->size++;
        if (pV->Actualsize < pV->size)
        {
            pV->Actualsize += 5;
            pV->Arr = (int*)realloc(pV->Arr, sizeof(int) * pV->Actualsize);
        }


        for (int i = pV->size; i >= index; i--)
        {
            pV->Arr[i] = pV->Arr[i - 1];
        }

        pV->Arr[index] = n;
    }
    else
    {
        Status = 0;
    }
    return Status;
}

int Delete(Vector_t* pV, int index)
{

    int Status = 1;
    if (index < pV->size)
    {
        for (int i = index; i < pV->size; i++)
        {
            pV->Arr[i] = pV->Arr[i + 1];
        }
        pV->size--;
    }
    else
    {
        Status = 0;
    }
    return Status;
    
    
}


void PrintArray(Vector_t* pV)
{
    for (int i = 0; i < pV->size; i++)
    {
        std::cout << pV->Arr[i] << " ";
    }

    std::cout << "\n---------------------------\n ";

}

int PrintIndex(Vector_t* pV, int index)
{
    int Status = 1;

    if (index < pV->size)
    {
        std::cout << pV->Arr[index] << "\n";
    }
    else
    {
        Status = 0;
    }
    return Status;
}




int main()
{
    int index;
    int n;
    Vector_t V;
    Vector_t V2;

    DynamicArray(&V, 5);
    
    std::cout << "Index to insert: ";
    std::cin >> index;
    std::cout << "Enter new Number: ";
    std::cin >> n;
    insert(&V, index, n);
    PrintArray(&V);
    
    std::cout << "Index to delete: ";
    std::cin >> index;
    Delete(&V, index);
    PrintArray(&V);
    
    std::cout << "Index: ";
    std::cin >> index;
    PrintIndex(&V, index);
    
    std::cout << "\n\n ===================== \n\n ";

    DynamicArray(&V2, 5);

    std::cout << "Index to insert: ";
    std::cin >> index;
    std::cout << "Enter new Number: ";
    std::cin >> n;
    insert(&V, index, n);
    PrintArray(&V2);

    std::cout << "Index to delete: ";
    std::cin >> index;
    Delete(&V, index);
    PrintArray(&V2);

    std::cout << "Index: ";
    std::cin >> index;
    PrintIndex(&V2, index);
    
 
    return 0;
}