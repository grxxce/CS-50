#include <cs50.h>
#include <stdio.h>

int factorial(int num);

int main (void)
{
    // Get Input
    int num = get_int("Input your integer: ");

    // Print Result
    printf("The factorial of %i is %i\n", num, factorial(num));
}

// Factorial function

int factorial(int num)
{
    // Base case: 0! = 1, 1! = 1
    if (num == 0)
    {
        return 1;
    }
    
    // Recursive step: return n * factorial(n-1)
    return num * factorial(num - 1);
}