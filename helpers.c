#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
	{
	   for (int j = 0; j < width; j++)
	   {
	      int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
		  image[i][j].rgbtRed = average;
		  image[i][j].rgbtBlue = average;
		  image[i][j].rgbtGreen = average;
	   }
    }
    return;
}
int limit(int RGB)
{
    if (RGB > 255)
	{
	  RGB = 255;
	}
    return RGB;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed;
	int sepiaGreen;
	int sepiaBlue;
	for (int i = 0; i < height; i++)
	{
	  for (int j = 0; j < width; j++)
	  {
	     sepiaRed = limit(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));

         sepiaGreen =  limit(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));

         sepiaBlue = limit(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue)); 

		 image[i][j].rgbtRed = sepiaRed;
		 image[i][j].rgbtGreen = sepiaGreen;
		 image[i][j].rgbtBlue = sepiaBlue;

      }
    }
	return ;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
	{
	   for (int j = 0; j < width; j++)
	   {
	       RGBTRIPLE temp = image[i][j];
		   image[i][j] = image[i][width - j - 1];
		   image[i][width - j - 1] = temp;
	   }
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
	int sumGreen;
	int sumRed;
	float counter;
	RGBTRIPLE temp[height][width];
    for (int i = 0; i < width; i++)
	{
	   for (int j = 0; j < height; j++)
	   {
	      sumGreen = 0;
          sumBlue = 0;
		  sumRed = 0;
		  counter = 0.0;
	      for (int l = -1; l < 2; l++)
		  {
		     if (j + l < 0 || j + l > height - 1)
			 {
			    continue;
			 }
			 for (int h = -1; h < 2; h++)
			 {
			    if (i + h < 0 || i + h > width - 1)
				{
				   continue;
				}
			    sumBlue += image[j + l][i + h].rgbtBlue;
				sumGreen += image[j + l][i + h].rgbtGreen;
				sumRed += image[j + l][i + h].rgbtRed;
				counter++;
			}
		  }
		temp[j][i].rgbtBlue = round(sumBlue / counter);
		temp[j][i].rgbtGreen = round(sumGreen / counter);
		temp[j][i].rgbtRed = round(sumRed / counter);
      }
	}
	 for (int i = 0; i < width; i++)
	 {
	   for (int j = 0; j < height; j++)
	   {
	     image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
		 image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
		 image[j][i].rgbtRed = temp[j][i].rgbtRed;
       }
	 }
    return;
}
