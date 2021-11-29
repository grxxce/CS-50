#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Ask the user for the number of cents they have, looping until they give a non-zero number
    int cents = 0;
    do
    {
        cents = get_int("How many cents do you have? ");
    } 
    while (cents < 0);

    return cents;
}

int calculate_quarters(int cents)
{
    // Divide remaining cents by 25 (quarter) and round down
    return floor(cents / 25);
}

int calculate_dimes(int cents)
{
    // Divide remaining cents by 10 (dime) and round down
    return floor(cents / 10);

}

int calculate_nickels(int cents)
{
    // Divide remaining cents by 5 (nickel) and round down
    return floor(cents / 5);
}

int calculate_pennies(int cents)
{
    // Divide remaining cents by 1 (penny) and round down
    return cents;
}