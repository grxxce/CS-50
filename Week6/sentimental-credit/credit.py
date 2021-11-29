# import get_string from cs50
from cs50 import get_string

# Define main function


def main():
    # Ask user to input credit card number and store as string
    number = get_string("Number: ")

    # If the card is a valid number, check the card type
    while check_valid(number):
        check_card(number)
        break

# Define a function to check luhn validity of function


def check_valid(number):
    # Store number string to an int list, then multiply every other from reversed list by 2 and reconcatenate to string
    list_num = [int(i) for i in number]
    every_other = [i * 2 for i in list_num[-2::-2]]
    every_other = [str(i) for i in every_other]
    every_other_str = "".join(every_other)

    # Separate string to int list and add that list to non-multiplied numbers
    every_other_digit = [int(i) for i in every_other_str]
    final = sum(every_other_digit[::]) + sum(list_num[::-2])

    # Return true if last digit is 0
    if final % 10 == 0:
        return True
    # Print invalid if not an return false
    print("INVALID\n")
    return False

# Define a function to determind card type


def check_card(number):

    # Use if-else statements to print card type and return to main
    if int(number[:2]) in (34, 37):
        print("AMEX\n")
        return
    elif int(number[:2]) in (51, 52, 53, 54, 55):
        print("MASTERCARD\n")
        return
    elif number[0] == "4":
        print("VISA\n")
        return

    # Print invalid if no conditions are met and return to main
    print("INVALID\n")
    return


# Call on main function
main()