#include <stdio.h>
#include <stdlib.h>

#include "./headers/dibdump.h"

#define image_S 4 // side length of the image (must be square)

int image[image_S][image_S];
int *imageFlattened;
int *traversed;

void traverse(int, int, int, int, int);

int main(void)
{
    char *bitmapFileInput = "./Rainbow.bmp";
    char *dumpLocation = "./dump.txt";

    imageFlattened = readBitmap(bitmapFileInput, dumpLocation);

    traversed = calloc(image_S * image_S, sizeof(int));

    int curr = 0;
    for (int r = 0; r < image_S; r++)
    {
        for (int c = 0; c < image_S; c++)
        {
            image[r][c] = imageFlattened[curr];
            curr++;
        }
    }

    traverse(1, image_S, 0, 0, 0);

    for(int i=0;i<image_S*image_S;i++) {
        int value = traversed[i];

        int blue = value & 0x00FF;
        int green = (value >> 8) & 0x00FF;
        int red = (value >> 16) & 0x00FF;
        
        printf("%d %d %d\n", red, green, blue);
    }
}

/**
 * Recursively traverses a square of values
 * Base case: dimension = 1 (just 1 single pixel)
 * 
 * configuration - the way in which to traverse the 4 quadrants of the current square
 *  1 - u-shaped (counter-clockwise)
 *  2 - backwards c-shaped (clockwise)
 *  3 - c-shaped (clockwise)
 *  4 - n-shaped (counter-clockwise)
 * dimension - the dimension (side lenght) of the current square (goes down by a factor of 2 each time)
 * startR - starting r coordinate (0 is at the "bottom")
 * startC - starting c coordinate (0 is at the "left")
 * ind - current index of the traversed array to assign to
 *  calculated and passed down; not used until the base case
 * 
 */ 
void traverse(int configuration, int dimension, int startR, int startC, int ind)
{

    if (dimension == 1)
    {
        traversed[ind] = image[startR][startC];
        return;
    }

    int topLeft = image[startR + 1][startC];
    int topRight = image[startR + 1][startC + 1];
    int bottomLeft = image[startR][startC];
    int bottomRight = image[startR][startC + 1];

    int nextDim = dimension / 2;

    int topLeftR = startR + nextDim;
    int topLeftC = startC;

    int topRightR = startR + nextDim;
    int topRightC = startC + nextDim;

    int bottomLeftR = startR;
    int bottomLeftC = startC;

    int bottomRightR = startR;
    int bottomRightC = startC + nextDim;

    int nextInd = dimension * dimension / 4;

    int index1 = ind;
    int index2 = ind + nextInd;
    int index3 = ind + 2 * nextInd;
    int index4 = ind + 3 * nextInd;

    switch (configuration)
    {
    case (1):
        traverse(2, nextDim, topLeftR, topLeftC, index1);
        traverse(1, nextDim, bottomLeftR, bottomLeftC, index2);
        traverse(1, nextDim, bottomRightR, bottomRightC, index3);
        traverse(3, nextDim, topRightR, topRightC, index4);
        break;
    case (2):
        traverse(1, nextDim, topLeftR, topLeftC, index1);
        traverse(2, nextDim, topRightR, topRightC, index2);
        traverse(2, nextDim, bottomRightR, bottomRightC, index3);
        traverse(4, nextDim, bottomLeftR, bottomLeftC, index4);
        break;
    case (3):
        traverse(4, nextDim, bottomRightR, bottomRightC, index1);
        traverse(3, nextDim, bottomLeftR, bottomLeftC, index2);
        traverse(3, nextDim, topLeftR, topLeftC, index3);
        traverse(1, nextDim, topRightR, topRightC, index4);
        break;
    case (4):
        traverse(3, nextDim, bottomRightR, bottomRightC, index1);
        traverse(4, nextDim, topRightR, topRightC, index2);
        traverse(4, nextDim, topLeftR, topLeftC, index3);
        traverse(2, nextDim, bottomLeftR, bottomLeftC, index4);
        break;
    }
}