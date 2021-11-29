#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;

    // Ask the user for input and loop until a valid number between 1 and 8 has been provided
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Create a loop that determines the number of rows based on input
    for (int i = 0; i < height; i++)
    {
        // Print height - row spaces - 1
        for (int j = 0; j < height - i - 1; j++)
        {
            printf(" ");
        }
        // Print row number of hashes, as measured by k
        for (int k = 0; k <= i; k ++)
        {
            printf("#");
        }
        // Print a new line
        printf("\n");
    } 
}