#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <stdlib.h>
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
            image[row][column].rgbtBlue = rounded_average;
            image[row][column].rgbtGreen = rounded_average;
            image[row][column].rgbtRed = rounded_average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column ++)
        {
            float sepia_red = .393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue;
            float sepia_green = .349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue;
            float sepia_blue = .272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue;
            if (sepia_red > 255)
                sepia_red = 255;
            if (sepia_blue > 255)
                sepia_blue = 255;
            if (sepia_green >255)
                sepia_green = 255;
            image[row][column].rgbtBlue = (int)round(sepia_blue);
            image[row][column].rgbtGreen = (int)round(sepia_green);
            image[row][column].rgbtRed = (int)round(sepia_red);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    
    for (int row = 0; row < height; row++)
    {
        RGBTRIPLE *b = malloc(width *sizeof(RGBTRIPLE));
        for (int column = 0; column < width; column ++)
        {
            b[column] = image[row][width - 1 - (column)];
        }
        for (int column = 0; column < width; column ++)
        {
            image[row][column] = b[column];
        }
        free(b);
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
