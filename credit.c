#include <stdio.h>
#include <cs50.h>
#include <string.h>

//declare a function to count how many digits in the card number
int count_digits(long card_number);
// function to do the arithmetic calculations
string find_card_type(int length, long number_to_check);

int main(void)
{
    //get card number from user
    long number = get_long("Number: ");
    // count how many characters in the card number
    int digits = count_digits(number);
    // check what type of card we have
    printf("%s\n", find_card_type(digits, number));

}


// function to check the first digit of the number
int count_digits(long card_number)
{
    int count = 0;
    while (card_number != 0)
    {
        count++;
        card_number /= 10;
    }
    return count;
}



// function to seperate digits into two arrays - multiplied and not_multiplied
// then do arithmetic to check number is valid
// then check for card type
string find_card_type(int length, long number_to_check)
{
    //declare an array to keep the digits in
    int digits[length];
    int digit = 0;
    int second_digit = 0;
    int i = 0;
    while (number_to_check != 0)
    {
        digit = number_to_check % 10; 
        // populate array by isolating digits using modulus and division by ten
        number_to_check /= 10;
        digits[i] = digit;
        i++;
    }
    second_digit = digits[length - 2];
    
    //declare an array for the digits whiich have been multiplied
    int multiplied[8];
    // declare a variable for the sum of those whoch haven't
    int not_multiplied = 0;
    int a = 0;
    for (i = 0; i < length; i += 2)
    {
        // add to the variable of non_multiplied digits
        not_multiplied += digits[i];
        //populate the array of multiplied digits
        multiplied[a] = digits[i + 1] * 2;
        a++;
    }
    
    // decalre variable fort he sum of digits from the multplied array
    int multiplied_sum = 0;
    for (a = 0; a < 8; a++)
    {
        if (multiplied[a] > 9)
        {   
            //if 10 or more add 1 to the remainder of division by ten
            multiplied_sum += (multiplied[a] % 10) + 1;
        }
        else
        {   
            //if less than ten, just add
            multiplied_sum += multiplied[a];
        }
    }
    
    // check final sum is perfectly divisable by 10
    if ((multiplied_sum + not_multiplied) % 10 == 0)
    {
        //check length of input and first/second digit to assign type of card    
        if (length == 15 && digit ==  3 && (second_digit == 4 || second_digit == 7))
        {
            return "AMEX";
        }
        else if ((length == 16 || length == 13) && digit == 4)
        {
            return "VISA";
        }
        else if (length == 16 && digit == 5 && (second_digit > 0 && second_digit < 6))
        {
            return "MASTERCARD";
        }
        else
        {
            return "INVALID";
        } 
    }
    // if not divisable by ten return invalid
    else
    {
        return "INVALID";
    }
}