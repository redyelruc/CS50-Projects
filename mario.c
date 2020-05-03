#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height = 0;  
    // declares an int variable called height
    do    
        //runs a loop to ensure that the user input is above zero and below 9
    {
        height = get_int("Height: "); 
        // asks user for height of pyramid
    }
    while (height <= 0 || height > 8);

    int row, column;  
    // declares int variables to count through loops

    for (row = 1; row <= height; row++)  
        // loops through each row of the pattern
    {
        for (column = 0; column < height; column++)  
            // prints a character for each column on the left half
        {
            if (column < (height - row))
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }

        }

        printf("  "); 
        //prints the space between the two sides

        for (column = 0; column < row; column++)    
            // prints a character for each column on the right half
        {
            printf("#");
        }
        printf("\n");   
        //passes to a new line
    }
}