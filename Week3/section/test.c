#include <stdio.h>
#include <cs50.h>

// Create the structure person
typedef struct
{
    string name;
    int age;
}
person;

int main(void)
{
    person people[2];

    // Fill the structure for people
    people[0].name = "Janny";
    people[0].age = 3;
    people[1].name = "Clara";
    people[1].age = 18;

    // Print out the results of name and age
    for (int i = 0; i < 2; i++)
    {
        printf("Name: %s ", people[i].name);
        printf("Age: %i\n", people[i].age);
    }

}