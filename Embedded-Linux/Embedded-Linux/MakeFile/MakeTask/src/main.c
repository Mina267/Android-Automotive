#include <stdio.h>
#include "calculator.h"  // Include the header file for the calculator

int main() {
    int a = 10, b = 5;
    printf("Sum: %d\n", add(a, b));
    printf("Difference: %d\n", subtract(a, b));
    printf("Product: %d\n", multiply(a, b));
    printf("Quotient: %d\n", divide(a, b));
    return 0;
}
