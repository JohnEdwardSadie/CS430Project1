#include <stdlib.h>
#include <stdio.h>

int width;
int height;

//defining structure variables
typedef struct RGBPixel{
     unsigned char r,g,b;
} RGBPixel;
//defining structure variables
typedef struct PPMFormat{
     int x, y;
     RGBPixel *data;
} PPMFormat;



int main(int argc, char *argv[]){
    printf("Did it work?\n");

    printf("Testing 123...\n");

    return 0;

}
