#include <cs50.h>
#include <stdio.h>

typedef struct node
{
    int number;
    struct node struct;
} node

int main(void)
{
    int first_number = get_int("first number: ");
    int second_number = get_int("second number: ");
    int third_number = get_int("third number: ");

    node *n malloc(sizeof(node));
    n -> number = x;
    n -> next = NULL;
}