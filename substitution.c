#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//declare two functions
bool chars_are_valid(string text);
bool no_duplicate_chars(string text);

int main(int argc, string argv[])
{
    // check for arguments
    if (argc != 2)
    {
        printf("missing command-line argument\n");
        return 1;
    }
    string cypherkey = argv[1];
    //checck that there are 26 chars
    if (strlen(cypherkey) != 26)
    {
        printf("You need 26 characters");
        return 1;
    }
    //check for duplicates
    if (!no_duplicate_chars(cypherkey))
    {
        printf("Key contains duplicates");
        return 1;
    }
    //check all chars are valid
    if (!chars_are_valid(cypherkey))
    {
        printf("Not a valid key");
        return 1;
    }
    //get the plaintext string
    string plaintext = get_string("plaintext: ");
    int length = strlen(plaintext);
    char cyphertext[length];
    
    //loop through the characters in the plaintext
    for (int ch = 0; ch < length; ch++)
    {
        int letter;
        if (plaintext[ch] >= 'a' && plaintext[ch] <= 'z')
        {
            // reduce ascii value to equal place in the alphabet
            letter = plaintext[ch] - 97;
            cyphertext[ch] = tolower(cypherkey[letter]);
        }
        else if (plaintext[ch] >= 'A' && plaintext[ch] <= 'Z')
        {
            // reduce ascii value to equal place in the alphabet
            letter = plaintext[ch] - 65;
            cyphertext[ch] = toupper(cypherkey[letter]);
        }
        else
        {
            //if a punctuation mark, leave it the same
            cyphertext[ch] = plaintext[ch];
        }
    }	
    printf("ciphertext: ");
    for (int ch = 0; ch < length; ch++)
    {
        printf("%c", cyphertext[ch]);
    }
    printf("\n");
    return 0;
}

// check all chars are letters and return true or false
bool chars_are_valid(string text)
{
    int length_of_string = strlen(text);
    for (int a = 0; a < length_of_string; a++)
    {
        if (isalpha(text[a]))
        {
        }
        else
        {
            return false;
        }
    }
    return true;
}

//check there are no duplicates and return true or false
bool no_duplicate_chars(string text)
{
    int length_of_string = strlen(text);
    for (int a = 0; a < length_of_string - 1; a++)
    {
        int i = a + 1;
        for (i = a + 1; i < length_of_string; i++)
        {
            if (tolower(text[a]) == tolower(text[i]))
            {
                return false;
            }
        }
    }
    return true;
}