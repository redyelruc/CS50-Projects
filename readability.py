from cs50 import get_string

text = input("Get text: ")

letters = 0
words = 1  # because the last sentence doesn't have a space after it.
sentences = 0

for character in text:
    if character == "." or character == "?" or character == "!":
        sentences += 1
    elif character == " ":
        words += 1
    elif (character >= "A" and character <= "Z") or (character >= "a" and character <= "z"):
        letters += 1

letters_per_hundred = 100 * (letters / words)
sentences_per_hundred = 100 * (sentences / words)
cole_liau = 0.0588 * letters_per_hundred - 0.296 * sentences_per_hundred - 15.8
cole_liau = round(cole_liau)

if cole_liau < 1:
    print("Before Grade 1\n")
elif cole_liau > 16:
    print("Grade 16+\n")
else:
    print("Grade " + str(cole_liau) + "\n")
