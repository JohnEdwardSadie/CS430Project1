#include<stdio.h>
#include<stdlib.h>

//John E. Sadie
//CS430 Computer Graphics
//Project 1 Computer Images

//Character array for storing data
char BufferSize[999999];


//Defining data type pixelData
typedef struct pixelData{
     unsigned char r,g,b;
} pixelData;

//Defining data type pixelimage
typedef struct pixelImage{
     int x, y;
     pixelData *data;
} pixelImage;

pixelImage *img;

#define Color 255
int c, RGBColor;


static pixelImage *ReadWriteP3(const char *file){

         pixelImage *pixelImg;
         int c, RGBColor;

         //Opening the file
         FILE *fp;
         fp = fopen(file, "rb");
         if (!fp){
              fprintf(stderr, "ERROR! The file: '%s' does not exist...\n", file);
              exit(1);
         }

         //Reading the format of the file
         if (!fgets(BufferSize, sizeof(BufferSize), fp)){
              perror(file);
              exit(1);
         }

    //Checking if the file is not a P6 file
    if (BufferSize[0] != 'P' || BufferSize[1] != '3'){
         fprintf(stderr, "This is not a P3 file! \n");
         exit(1);
    }
    //Else print out that it is
    else{
        printf("This is a P3 file! \n");
    }

    pixelImg = (pixelImage *)malloc(sizeof(pixelImage));
    if (!pixelImg) {
        fprintf(stderr, "Error allocating memory\n");
        exit(1);
    }

    //Since I don't know how many characters comments are
    //Checking for comments
    c = getc(fp);
    while (c == '#') {
        while (getc(fp) != '\n') ;
        c = getc(fp);
    }

    ungetc(c, fp);

   //Reading the input size
    if (fscanf(fp, "%d %d", &pixelImg->x, &pixelImg->y) != 2){
         fprintf(stderr, "ERROR! Can't read input size\n");
         exit(1);

    }

    //Reading RGBColor
    if (fscanf(fp, "%d", &RGBColor) != 1){
         fprintf(stderr, "ERROR! Can't read RGBColor\n", file);
         exit(1);
    }

    //Checking RGB Depth
    if (RGBColor!= Color){
         fprintf(stderr, "ERROR! With RGB Depth of file:'%s'\n", file);
         exit(1);
    }


    while (fgetc(fp) != '\n');

    // read data
    fread(BufferSize, sizeof(BufferSize), 1, fp);

    //Reformatting outputp3.ppm
    fp = fopen("outputp3.ppm", "wb");
    fprintf(fp, "P3\n");
    fprintf(fp, "# John Sadie was here!\n");
    fprintf(fp, "%d %d\n", pixelImg->x, pixelImg->y);
    fprintf(fp, "%d\n", Color);
    fprintf(fp, "%s\n", BufferSize);
    fclose(fp);



}

static pixelImage *ReadWriteP6(const char *file){
        pixelImage *pixelImg;


         int c, RGBColor;

         //Opening the file
         FILE *fp;
         fp = fopen(file, "rb");
         if (!fp){
              fprintf(stderr, "ERROR! The file: '%s' does not exist...\n", file);
              exit(1);
         }

         //Reading the format of the file
         if (!fgets(BufferSize, sizeof(BufferSize), fp)){
              perror(file);
              exit(1);
         }

    //Checking if the file is not a P6 file
    if (BufferSize[0] != 'P' || BufferSize[1] != '6'){
         fprintf(stderr, "This is not a P6 file! \n");
         exit(1);
    }
    //Else print out that it is
    else{
        printf("This is a P6 file! \n");
    }


    //Allocating space to store pixelImage
    pixelImg = (pixelImage *)malloc(sizeof(pixelImage));
    if (!pixelImg){
         fprintf(stderr, "ERROR! CanpixelImage *pixelImg;'t allocate memory\n");
         exit(1);
    }

    //Since I don't know how many characters comments are
    //Checking for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }
    ungetc(c, fp);


    //Reading the input size
    if (fscanf(fp, "%d %d", &pixelImg->x, &pixelImg->y) != 2){
         fprintf(stderr, "ERROR! Can't read input size\n");
         exit(1);

    }

    //Reading RGBColor
    if (fscanf(fp, "%d", &RGBColor) != 1){
         fprintf(stderr, "ERROR! Can't read RGBColor\n", file);
         exit(1);
    }

    //Checking RGB Depth
    if (RGBColor!= Color){
         fprintf(stderr, "ERROR! With RGB Depth of file:'%s'\n", file);
         exit(1);
    }

    //Allocating memory to pixelData
    while (fgetc(fp) != '\n') ;
    pixelImg->data = (pixelData*)malloc(pixelImg->x * pixelImg->y * sizeof(pixelData));

    //Checking if allocating memory has gone wrong
    if (!pixelImg){
         fprintf(stderr, "ERROR! Can't allocate memory\n");
         exit(1);
    }

    //Reading the data from 'file'
    if (fread(pixelImg->data, 3 * pixelImg->x, pixelImg->y, fp) != pixelImg->y){
         fprintf(stderr, "Error loading image '%s'\n", file);
         exit(1);
    }

    fp = fopen("outputp6.ppm", "wb");
    if (!fp) {
         fprintf(stderr, "ERROR! Can't open file: '%s'\n", file);
         exit(1);
    }

    //Reformatting outputp6.ppm
    fprintf(fp, "P6\n");
    fprintf(fp, "# John Sadie Was Here!\n");
    fprintf(fp, "%d %d\n",pixelImg->x,pixelImg->y);
    fprintf(fp, "%d\n",Color);
    //Writing data
    fwrite(pixelImg->data, 3 * pixelImg->x, pixelImg->y, fp);
    fclose(fp);

}
int p3top6(){


}

int p6top3(const char *file){



         int c, RGBColor;

         //Opening the file
         FILE *fp;
         fp = fopen(file, "rb");
         if (!fp){
              fprintf(stderr, "ERROR! The file: '%s' does not exist...\n", file);
              exit(1);
         }

         //Reading the format of the file
         if (!fgets(BufferSize, sizeof(BufferSize), fp)){
              perror(file);
              exit(1);
         }

    //Checking if the file is not a P6 file
    if (BufferSize[0] != 'P' || BufferSize[1] != '6'){
         fprintf(stderr, "This is not a P6 file! \n");
         exit(1);
    }
    //Else print out that it is
    else{
        printf("This is a P6 file! \n");
    }

    pixelImage *pixelImg;
    //Allocating space to store pixelImage
    pixelImg = (pixelImage *)malloc(sizeof(pixelImage));
    if (!pixelImg){
         fprintf(stderr, "ERROR! \n");
         exit(1);
    }

    //Since I don't know how many characters comments are
    //Checking for comments
    c = getc(fp);
    while (c == '#') {
    while (getc(fp) != '\n') ;
         c = getc(fp);
    }
    ungetc(c, fp);


    //Reading the input size
    if (fscanf(fp, "%d %d", &pixelImg->x, &pixelImg->y) != 2){
         fprintf(stderr, "ERROR! Can't read input size\n");
         exit(1);

    }

    //Reading RGBColor
    if (fscanf(fp, "%d", &RGBColor) != 1){
         fprintf(stderr, "ERROR! Can't read RGBColor\n", file);
         exit(1);
    }

    //Checking RGB Depth
    if (RGBColor!= Color){
         fprintf(stderr, "ERROR! With RGB Depth of file:'%s'\n", file);
         exit(1);
    }

    //allocating memory for buffer
    pixelImg->data = (pixelData*)malloc(pixelImg->x * pixelImg->y * sizeof(pixelData));

    //Checking if allocating memory has gone wrong
    if (!pixelImg){
         fprintf(stderr, "ERROR! Can't allocate memory\n");
         exit(1);
    }

    //Reading the data from 'file'
    if (fread(pixelImg->data, 3 * pixelImg->x, pixelImg->y, fp) != pixelImg->y){
         fprintf(stderr, "Error loading image '%s'\n", file);
         exit(1);
    }

    fp = fopen("p6top3.ppm", "wb");
    if (!fp) {
         fprintf(stderr, "ERROR! Can't open file: '%s'\n", file);
         exit(1);
    }
    int i;
                fprintf(fp, "P3\n");
                fprintf(fp, "# John Sadie was here!\n");
                fprintf(fp, "%d %d\n", pixelImg->x, pixelImg->y);
                fprintf(fp, "%d\n", Color);

    for(i = 0; i < pixelImg->x * pixelImg->y; i++){
        if(i = 0)

                fprintf(fp, "%d", pixelImg->data[i].r);
                fprintf(fp, "\n");
                fprintf(fp, "%d", pixelImg->data[i].g);
                fprintf(fp, "\n");
                fprintf(fp, "%d", pixelImg->data[i].b);
                fprintf(fp, "\n");

    }



}





int main(int argc, char *argv[]){

    pixelImage *image;

    //Reading/Writing a p3 ppm file
    image = ReadWriteP3("p3.ppm");

    //Reading/Write a P6 ppm file
    image = ReadWriteP6("p6.ppm");

    image = p6top3("p6.ppm");






    //Testing print statement
    printf("Did it work?");
    //Check if arguments are not equal to 4
    if(argc != 4){
        fprintf(stderr, "ERROR\n");
        return 1;
    }
    getchar();
}
