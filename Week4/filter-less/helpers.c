#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixel rows and columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find average value for grayscale
            float avg = round(((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0));

            // Replace original colors with this new value
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixel rows and columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate new sepia color value, ensuring new value is an int between 0 and 255, inculsive
            float sepia_red = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) + (image[i][j].rgbtBlue * 0.189));
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            float sepia_green = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) + (image[i][j].rgbtBlue * 0.168));
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            float sepia_blue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) + (image[i][j].rgbtBlue * 0.131));
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            // Set new sepia colors to new image
            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all pixel rows
    for (int i = 0; i < height; i++)
    {
        // Since integers floor the value, a row with odd units will not swap the middle integer
        for (int j = 0; j < width / 2; j++)
        {
            // Create a temporary rbgtriple structure to store the value of the swapping pixels, then wwap pixels in each row
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create an OG color value set of pixels
    RGBTRIPLE OGImage[height][width];
    // Loop through all pixel rows and columns to create a duplicate
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            OGImage[i][j] = image[i][j];
        }
    }

    // Check if value exists 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int numPixels = 0;
            float total_red, total_green, total_blue;
            total_red = total_green = total_blue = 0;

            // Check if values exists in surrounding rows
            for (int k = -1; k < 2; k++)
            {
                // Check if value exists in surrounding columns
                for (int l = -1; l < 2; l++)
                {
                    // Leave if outside of rows scope
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Leave it outside of column scope
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Else, this pixel is in scope so increase counter
                    total_red += OGImage[i + k][j + l].rgbtRed;
                    total_green += OGImage[i + k][j + l].rgbtGreen;
                    total_blue += OGImage[i + k][j + l].rgbtBlue;
                    numPixels++;
                }
            }
            //replace image[i][j] with new average
            image[i][j].rgbtRed = round(total_red / numPixels);
            image[i][j].rgbtGreen = round(total_green / numPixels);
            image[i][j].rgbtBlue = round(total_blue / numPixels);
        }
    }
    return;
}
