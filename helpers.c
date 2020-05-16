#include <stdio.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column ++)
        {
            float average = (float)(image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed)/3;
            int rounded_average = (int)round(average);
            // printf("%x,%x,%x,%x", image[0][0].rgbtBlue, image[0][0].rgbtGreen, image[0][0].rgbtRed, rounded_average);
            
            image[row][column].rgbtBlue = rounded_average;
            image[row][column].rgbtGreen = rounded_average;
            image[row][column].rgbtRed = rounded_average;
            // printf("%x,%x,%x", image[0][0].rgbtBlue, image[0][0].rgbtGreen, image[0][0].rgbtRed);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
