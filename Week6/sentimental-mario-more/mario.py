# Import get_int from cs50 library
from cs50 import get_int

# Define main function


def main():
    # Ask user for a valid pyramid height bewteen 1 and 8
    while True:
        height = get_int("Input pyramid height, between 1 and 8: ")
        if height > 0 and height < 9:
            break
    # Call on pyramid function to print
    pyramid(height)

# Print the pyramid


def pyramid(height):
    for i in range(height):
        for j in range(height - i - 1):
            print(" ", end='')
        for j in range(i + 1):
            print("#", end='')
        print("  ", end='')
        for j in range(i + 1):
            print("#", end='')
        print("\n", end='')


# Call main function
main()