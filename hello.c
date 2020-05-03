#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name?\n"); //decares a variable name of the string type and asks the user to input a string
    printf("hello, %s.\n", name);  // prints hello + name
}