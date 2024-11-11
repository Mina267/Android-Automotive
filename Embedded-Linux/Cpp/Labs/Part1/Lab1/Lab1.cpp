#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>



void ArrayOfString(void)
{
    int size;
    int len;
    char in[50];

    std::cout << "Size : ";
    std::cin >> size;

    char** strings = (char**)malloc(sizeof(char*) * size);

    

    for (int i = 0; i < size; i++)
    {
        std::cin >> in;
        len = strlen(in);
        strings[i] = (char*)malloc((sizeof(char) * len) + 1);


        for (int j = 0; in[j]; j++)
        {
            strings[i][j] = in[j];
        }
        strings[i][len] = '\0';

    }


    for (int i = 0; i < size; i++)
    {
        std::cout << strings[i] << std::endl;
    }

}





int main()
{
  
    ArrayOfString();

    
    return 0;
}