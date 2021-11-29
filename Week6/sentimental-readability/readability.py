# Include libraries
from cs50 import get_string

# Define global variables
num_words = 1
num_letters = num_sentences = 0


# Define main function


def main():
    text = get_string("Please input your text: ")

    # Call on compute level function to calculate the test level
    compute_level(text)


# Create compute level function


def compute_level(text):
    L = avg_letters(text)
    S = avg_sentences()

    # Calculate index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Interpret Index
    return interpret(index)


# Calculate avg letters per 100 words


def avg_letters(text):
    # Reference global variables
    global num_words, num_letters, num_sentences

    # Calculate number of words, letters, and sentences
    for i in text:
        if i == " ":
            num_words += 1
        elif (i).isalpha():
            num_letters += 1
        elif i in (".", "?", "!"):
            num_sentences += 1

    # Return average letters per 100 words
    return (num_letters / num_words) * 100


# Calcualte average sentences per 100 words


def avg_sentences():
    # Return average sentences per 100 words
    return (num_sentences / num_words) * 100


# Compute the final reading level


def interpret(index):
    # Use if/else statements to print the right grade, then return to main
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")
    return


# Call Main function
main()