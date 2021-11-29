// Implements a dictionary's functionality
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototype for free function
void free_word(node *cursor);

// Create a global size variable
int size_words = 0;

// Through trial and error experimentation, found N value that was most time-saving
const unsigned int N = 2000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Iterate through all indexes of hash table
    for (node *cursor = table[hash(word)]; cursor != NULL; cursor = cursor->next)
    {
        // If case insensitive words are equal, return true
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Fund the ASCII sum of the value as taking the mod of that is likely to give a more evenly distributed hash table
    int ASCII_sum = 0;

    // Iterate through all letters in teh word
    for (int i = 0; i < strlen(word); i++)
    {
        ASCII_sum += toupper(word[i]);
    }
    return ASCII_sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file and do a safety check for file contents
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Set the buffer array legnth to word length plus null
    char word[LENGTH + 1];

    // Read strings from file one at a time until EOF is reached
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word and do a safety check for n contents
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // Copy the word into n at word
        strcpy(n->word, word);
        n->next = NULL;

        // Call on hash function to obtain index
        int index = hash(word);

        // Insert node into hash table at correct location
        n->next = table[index];
        table[index] = n;

        // Call on size function to increase number of words in dictionary by 1
        size_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return word size
    return size_words;
}

// Create free word function
void free_word(node *cursor)
{
    // Iterate recursively to free all elements of the linked list
    if (cursor == NULL)
    {
        return;
    }
    free_word(cursor->next);
    free(cursor);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the buckets of the hash table
    for (int i = 0; i < N; i++)
    {
        // Call on free_word function to free every elemnt of the linked list recursively
        free_word(table[i]);
    }
    return true;
}
