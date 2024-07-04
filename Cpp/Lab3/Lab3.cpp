#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>





typedef int (OperationCallback)(int*, int);
typedef int* (*CallbackFunction)(int** arr_2d, int arr_size, int* row_sizes, OperationCallback);


int* arr2D_Proccess(int** arr_2d, int arr_size, int* row_sizes, OperationCallback Local_Operation)
{
    int* result_arr = (int*)malloc(sizeof(int) * arr_size);

    for (int i = 0; i < arr_size; i++)
    {
        result_arr[i] = Local_Operation(arr_2d[i], row_sizes[i]);
    }

    return result_arr;
}


int OperationFunc(int* arr, int size)
{
    int Max = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (Max < arr[i])
        {
            Max = arr[i];
        }
    }
    return Max;
}



int main()
{
   
    int arr1[4] = { 1, 2, 3, 4 };
    int arr2[5] = { 1, 2, 3, 4, 5 };
    int arr3[3] = { 1, 2, 3 };
    int arr4[6] = { 1, 2, 3, 4, 5, 6 };

    int* arr[4] = {arr1, arr2, arr3, arr4};
    int arr_sizes[] = {4, 5, 3, 6};

    CallbackFunction Local_CallBackFuncrion = arr2D_Proccess;

    int* result_arr = Local_CallBackFuncrion(arr, 4, arr_sizes, OperationFunc);
    for (int i = 0; i < 4; i++)
    {
        std::cout << result_arr[i] << "  ";
    }
    std::cout << std::endl;

    free(result_arr);

    return 0;
}