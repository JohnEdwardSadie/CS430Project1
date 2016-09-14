#include <stdlib.h>
#include <stdio.h>

int width;
int height;
int c;

//defining structure variables
typedef struct RGBPixel{
     unsigned char r,g,b;
} RGBPixel;

typedef struct PPMFormat{
     int x, y;
     RGBPixel *data;
} PPMFormat;


static PPMFormat *Read(const char *file){

         char BufferSize[30];

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


    if (BufferSize[0] != 'P' || BufferSize[1] != '3'){
         fprintf(stderr, "This is not a p3 file! \n");
         exit(1);
    }
    else if (BufferSize[0] == 'P' || BufferSize[1] == '3'){
        printf("This is a p3 file!\n");
        exit(1);
    }

    if (BufferSize[0] != 'P' || BufferSize[1] != '6'){
         fprintf(stderr, "This is not a p6 file! \n");
         exit(1);
    }

    else if (BufferSize[0] == 'P' || BufferSize[1] == '6'){
        printf("This is a p6 file!\n");
        exit(1);
    }


    //Since I don't know how many characters comments are
    //Checking for comments
    c = getc(fp);
    while (c == '#'){
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }
    ungetc(c, fp);
    //Reading the dimensions of the image
    if (fscanf(fp, "%d %d", &image->x, &image->y) != 2){
         fprintf(stderr, "ERROR on file: %s\n", file);
         exit(1);
    }




}

void Write(const char *file, PPMFormat *image){
    FILE *fp;

    fp = fopen(file, "wb");
    if(!fp){
        fprintf(stderr, "I was unable to find the file: %s'\n", file);
        exit(1);
    }
    //writing P3 data
    //Using fprintf as advised by Dr. Palmer
    fprintf(fp, "# John Sadie Was Here!\n");
    fwrite(image->data, 3 * image->x, image->y, fp);
    fclose(fp);

}




int main(int argc, char *argv[]){
    printf("Testing 123...\n");

    PPMFormat *image;
    image = Read("p3.ppm");
    Write("OutputP3.ppm", image);


    printf("Did it work?\n");
    //Check if arguments are not equal to 4
    if(argc != 4){
        fprintf(stderr, "ERROR\n");
        return 1;
    }
    return 0;

}
