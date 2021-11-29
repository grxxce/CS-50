import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        data = []
        subsequence = []
        for row in reader:
            # Record each STR in the dataset into subsequence, skipping the name
            data.append(row)
            subsequence = list(row.keys())[1:]

    # Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()

    # Find longest match of each STR in DNA sequence
    match = []
    for i in range(len(subsequence)):
        match.append(longest_match(sequence, subsequence[i]))

    # Check database for matching profiles
    for row in data:
        is_match = True
        for i in range(len(subsequence)):
            if int(row[subsequence[i]]) != match[i]:
                is_match = False
                break

        # Return true if the match condition is met
        if is_match:
            print(row["name"])
            sys.exit(0)

    # Return no match if you have not exited yet
    print("No match")
    sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()