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
            //calculate the average
            float average = (float)(image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3;
            int rounded_average = (int)round(average);
            // make sure all three colours have the average amount
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
            //apply the calculations to make the colour sepia
            float sepia_red = .393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue;
            float sepia_green = .349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue;
            float sepia_blue = .272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue;
            // make sure we don't go over max total
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            // save to the image
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
        //make a new single line space in memory
        RGBTRIPLE *b = malloc(width * sizeof(RGBTRIPLE));
        for (int column = 0; column < width; column ++)
        {
            //new image pixel = pixel from other end of column
            b[column] = image[row][width - 1 - (column)];
        }
        //copy back to original image
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
    // initialise the toal variables
    float total_blue, total_red, total_green;
    int pixels_used;
    // make a new file for the blurred pic to be stored
    RGBTRIPLE blurred_image[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column ++)
        {
            // reset before looping through the next pixel
            pixels_used = 0;
            total_blue = 0;
            total_red = 0;
            total_green = 0;
            for (int y = row - 1; y <= row + 1; y++)
            {
                for (int x = column - 1; x <= column + 1; x++)
                {
                    //avoid all references outside of width and height
                    if (y >= 0 && y <= height - 1 && x >= 0 && x <= width - 1)
                    {
                        total_blue += image[y][x].rgbtBlue;
                        total_red += image[y][x].rgbtRed;
                        total_green += image[y][x].rgbtGreen;
                        //count how many pixels used so you can use as a divisor for the average
                        pixels_used += 1;
                    }
                }
            }
            // populate the new image with the averages
            blurred_image[row][column].rgbtBlue = (int)round(total_blue / pixels_used);
            blurred_image[row][column].rgbtRed = (int)round(total_red / pixels_used);
            blurred_image[row][column].rgbtGreen = (int)round(total_green / pixels_used);
        }
    }
    // copy the newly blurred file to the original image file
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column ++)
        {
            image[row][column] = blurred_image[row][column];
        }
    }
    return;
}
