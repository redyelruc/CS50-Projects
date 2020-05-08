#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // declaring all variables for the programme
    int words = 0;
    int letters = 0;
    int sentences = 0;
    string text;
    float letters_per_hundred = 0.0;
    float sentences_per_hundred = 0.0;
    float cole_liau = 0.0;
    
    //ask the user for input
    text = get_string("Text: ");
    // loop through each character of the string
    for (int i = 0; i < strlen(text); i++)
    {
        //if the character is ! . or ?
        if (text[i] == 33 ||  text[i] == 46 ||  text[i] == 63)
        {
            sentences ++;
        }
        // if the character is a space
        if (text[i] == 32)
        {
            words++;
        }
        // if the character is a letter of the alphabet, small or CAPITAL
        if ((text[i] >= 65 && text[i] <= 90)  || (text[i] >= 97 && text [i] <= 122))
        {
            letters++;
        }
    }
    //add an extra word as there is no space after the final word in the text
    words++;
    // calculate letters and sentences per hundred words
    letters_per_hundred = 100 * (float)letters / words;
    sentences_per_hundred = 100 * (float)sentences / words;
    // calculate the Coleman-Liau value
    cole_liau = 0.0588 * letters_per_hundred - 0.296 * sentences_per_hundred - 15.8;
    //round to an integer
    cole_liau = round(cole_liau);
    
    //print out the appropriate grade
    if (cole_liau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (cole_liau > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", (int)cole_liau);
    }
}