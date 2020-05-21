from cs50 import get_string
from sys import exit


def check_number(number):
    i = len(number) - 1
    not_multiplied = 0
    multiplied = 0
    while i >= 0:
        not_multiplied = not_multiplied + int(number[i])
        i -= 2
    i = len(number) - 2
    while i >= 0:
        new_digit = int(number[i]) * 2
        if new_digit > 9:
            new_digit = str(new_digit)
            new_digit = int(new_digit[1]) + 1
        multiplied = multiplied + new_digit
        i -= 2
    if (multiplied + not_multiplied) % 10 == 0:    
        return True
    else:
        return False
    

card_number = get_string("Number: ")
length = len(card_number)
if check_number(card_number) == True:
    if ((card_number[0:2] == "34" or card_number[0:2] == "37")) and length == 15:
        print("AMEX\n")
    elif (length == 13 or length == 16) and (card_number[0] == '4'):
        print("VISA\n")
    elif length == 16 and int(card_number[0:2]) > 50 and int(card_number[0:2]) < 56:
        print("MASTERCARD\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")