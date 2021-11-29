#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
void calculate_grade(int letters, int sentences, int words);

// Main
int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    // Call on functions to calculate and print number of letters, words, sentences and reading score
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    calculate_grade(letters, sentences, words);
}

// Methods

// Method that counts and returns the number of letters in the text
int count_letters(string text)
{
    int numLetters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            numLetters++;
        }
    }
    printf("%i letters\n", numLetters);
    return numLetters;
}

// Method that counts the number of words in the text
int count_words(string text)
{
    int numWords = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            numWords++;
        }
    }
    printf("%i words\n", numWords);
    return numWords;
}

// Method that counts and returns the number of sentences in the text
int count_sentences(string text)
{
    int numSentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            numSentences++;
        }
    }
    printf("%i sentences\n", numSentences);
    return numSentences;
}

// Method that calculates and outputs the grade of the text
void calculate_grade(int letters, int sentences, int words)
{
    float L = 100.0 * letters / words;
    float S = 100.0 * sentences / words;
    float score = (0.0588 * L) - (0.296 * S) - 15.8;

    if (score > 16)
    {
        printf("Grade 16+\n");
    }
    else if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %0.0f\n", score);
    }
}
