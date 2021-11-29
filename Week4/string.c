#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s_one = get_string("First string: ");
    char *s_two = get_string("Second string: ");
    printf("%s\n", concatenate(s_one, s_two));
    return 0;
}

// Function that concatenates two strings and returns concatenated versions

char *concatenate(char *s1, char *s2)
{
    //typring "char *" will do the exact same thing as writing string
    char *s3 = malloc(strlen(s1) + strlen(s2) + 1); // Allocate the memory ot add the null value

    // Store the first string in the spaces
    for (int i = 0; i < strlen(s1); i++)
    {
        s3[i] = s1[i];
    }

    // Store the second string in the spaces
    for (int i = 0; i < strlen(s2); i++)
    {
        s3[strlen(s1) + i] = s1[i]; // Starts at the length of i
    }

    // Add terminating character
    s3[strlen(s1) + strlen(s2)] = '\0'; // This sets the last value of the string to null
    return s3;
}