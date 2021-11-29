#include <cs50.h>
#include <stdio.h>

// prototype
int increment(int n);

// print main function
int main (void)
{
    printf("This is your first number: %i\n", increment(3));
    printf("This is your second number: %i\n", increment(5));
    printf("This is your third number: %i\n", increment(7));
}

// increment function
int increment(int n)
{
    return ++n; // make sure you add the ++ before the n
} 