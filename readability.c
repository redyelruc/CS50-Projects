#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int words = 0;
    int letters = 0;
    int sentences = 0;
    string text;
    float letters_per_hundred = 0.0;
    float sentences_per_hundred = 0.0;
    float cole_liau = 0.0;
    
    text = get_string("Text: ");
    for (int i=0;i<strlen(text); i++)
    {
        if (text[i] == 33 ||  text[i] == 46 ||  text[i] == 63)
        {
            sentences ++;
        }
        if (text[i] == 32)
        {
            words++;
        }
        if ((text[i] >= 65 && text[i] <= 90)  || (text[i] >= 97 && text [i] <= 122))
        {
            letters++;
        }
    }
    words++;
    letters_per_hundred = 100 * (float)letters/words;
    sentences_per_hundred = 100 * (float)sentences/words;
    cole_liau = 0.0588 * letters_per_hundred - 0.296 * sentences_per_hundred - 15.8;
    cole_liau = round(cole_liau);
    if (cole_liau < 1)
    {
    	printf ("Before Grade 1\n");
    }
    else if (cole_liau > 16)
    {
    	printf ("Grade 16+\n");
    }
    else
    {
    	printf ("Grade %d\n", (int)cole_liau);
    }
}