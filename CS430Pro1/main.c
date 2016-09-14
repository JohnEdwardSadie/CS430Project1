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

static PPMFormat *readPPM(const char *file){
         char BufferSize[16];
         PPMFormat *image;
         FILE *fp;

         //Opening the file
         fp = fopen(file, "rb");
         if (!fp){
              fprintf(stderr, "ERROR! The file: '%s' does not exist...'\n", file);
              exit(1);
         }

         //Reading the file format
         if (!fgets(BufferSize, sizeof(BufferSize), fp)){
              perror(file);
              exit(1);
         }

    //check the image format for P6.ppm
    if (BufferSize[0] != 'P' || BufferSize[1] != '3'){
         fprintf(stderr, "ERROR: This is not a p3 file! \n");
         exit(1);
    }
    else{
        printf("This is a P3 file.\n");
    }
}

int main(int argc, char *argv[]){
    printf("Testing 123...\n");
    PPMFormat *image;
    image = readPPM("p3.ppm");
    printf("Did it work?\n");
    //Check if arguments are not equal to 4
    if(argc != 4){
        fprintf(stderr, "ERROR\n");
        return 1;
    }
    return 0;

}
