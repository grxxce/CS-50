#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Prototypes
void cipher(int k, string plaintext);
bool only_digits(string s);

// Main that accepts command line argument k
int main(int argc, string argv[])
{
    // Print an error message and return 1 if greater or fewer than 1 argument has been provided or k is not a decimal digit
    if ((argc != 2) || (!only_digits(argv[1])))
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);
        // Prompt user for plaintext
        string plaintext = get_string("plaintext:  ");
        // Call on ciphertext function to cipher the text and print to screen
        cipher(k, plaintext);
        return 0;
    }
}

// Function to cipher the plaintext
void cipher(int k, string plaintext)
{
    int i = 0;
    while (plaintext[i] != '\0')
    {
        // If the element of the string plaintext is alphabetical, shift by the key k%26
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z')
        {
            plaintext[i] = 'A' + (plaintext[i] - 'A' + k) % 26;
        }
        else if (plaintext[i] >= 'a' && plaintext[i] <= 'z')
        {
            plaintext[i] = 'a' + (plaintext[i] - 'a' + k) % 26;
        }
        // If the element of the string plaintext is not alphabetical, leave unchanged 
        i++;
    }
    // Print ciphered text to screen
    printf("ciphertext: %s\n", plaintext);
}

// Function to check if input is an integer
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}