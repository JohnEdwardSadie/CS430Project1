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


static pixelImage *ReadWriteP3(const char *file, const char *outputFile){

    pixelImage *pixelImg;
    FILE *fh;
    int compareColor;
    int t = 0;
    int c, i,j,k;
    char buffer[4];

    //Open p3.ppm
    fh = fopen(file, "r");
    if(fh == 0){
       fh = fopen(file, "rb");
    }
    //If fh == 0 then file did not open, error out
    if(fh == 0){

        fprintf(stderr, "ERROR! The file: '%s' does not exist...\n", file);
        exit(1);
    }
    c = fgetc(fh);
    if (c!= 'P'){
        fprintf(stderr, "ERROR! This is not a P3 file!\n");
        exit(1);
    }
    //Allocating memory
     pixelImg = (pixelImage *)malloc(sizeof(pixelImage));
    if(pixelImg == 0){
        fprintf(stderr, "ERROR! Can't allocate memory \n");
        exit(1);
    }
    fgetc(fh);


    //Skipping the magic number
    while((c = fgetc(fh)) != '\n'){
    }
    //Parsing past the comments
    c = fgetc(fh);
    while (c=='#'){
        while (fgetc(fh) != '\n');
            c=fgetc(fh);
    }
    ungetc(c, fh);
    //Get input size
    if(fscanf(fh, "%d %d", &pixelImg->x, &pixelImg->y) !=2){
        fprintf(stderr, "A width or Height image dimensions is missing in the file.");
        exit(1);
    }
    fscanf(fh, "%d", &compareColor);
    pixelImg->data = (pixelData*)malloc((Color+1)*pixelImg->x*pixelImg->y);
    if(pixelImg->data == 0){
        fprintf(stderr, "Error: Memory could not be allocated.");
        exit(1);
    }
    fgetc(fh);
        j=0;
        i=0;
        //Iterates through file
        //If c is not a space, it puts it into buffer
        while ((c = fgetc(fh)) != EOF){
            if(isspace(c)){
                while(isspace(c = fgetc(fh))){
                }
                ungetc(c, fh);
                //ascii to int
                k = atoi(buffer);
                //Checking to see if pixel number is over a byte in size
                if(k > Color){
                    fprintf(stderr, "Error! Pixel number is too big.\n");
                    exit(1);
                }
                t++;
                if(t == 1){
                    pixelImg->data[j].r = k;
                }

                if(t == 2){
                    pixelImg->data[j].g = k;
                }

                if(t == 3){
                    pixelImg->data[j].b = k;
                    t = 0;
                }

                j++;
                i = 0;
                memset(buffer, '\0', sizeof(buffer));
            }
            else{
                buffer[i++] = c;
            }
        }
    ungetc(c, fh);
    fclose(fh);

    FILE *fp;

    fp = fopen(outputFile, "wb");
    fprintf(fp, "P3\n");
    fprintf(fp, "# John Sadie was here!\n");
    fprintf(fp, "%d %d\n", pixelImg->x, pixelImg->y);
    fprintf(fp, "%d\n", Color);
    fprintf(fp,"\n");
                for (j=0; j< sizeof(pixelData)*pixelImg->x*pixelImg->y; j++){
                    t++;
                    if(t == 1){
                       fprintf(fp, "%d", pixelImg->data[j].r);
                        fprintf(fp, "\n");
                    }
                    if(t == 2){
                       fprintf(fp, "%d", pixelImg->data[j].g);
                        fprintf(fp, "\n");
                    }
                    if(t == 3){
                       fprintf(fp, "%d", pixelImg->data[j].b);
                        fprintf(fp, "\n");
                        t = 0;
                    }
                }
fclose(fp);
}

static pixelImage *ReadWriteP6(const char *file, const char *outputFile){
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

    fp = fopen(outputFile, "wb");
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
static pixelImage *p3top6(const char *file, const char *outputFile){
    pixelImage *pixelImg;
    FILE *fh;
    int max_color, width, height;
    int t = 0;
    int c, i,j,k;
    char buffer[4];

    //Opening p3.ppm
    fh = fopen(file, "r");
    if(fh == 0){
       fh = fopen(file, "rb");
    }
    //Error Checking
    if(fh == 0){
        fclose(fh);
        fprintf(stderr, "ERROR! Can't open the file: '%s' \n", file);
        exit(1);
    }
    c = fgetc(fh);
    if (c!= 'P'){
        fprintf(stderr, "ERROR! This is not a p6 file! \n");
        exit(1);
    }
    ungetc(c, fh);
    //Allocating memory
     pixelImg = (pixelImage *)malloc(sizeof(pixelImage));
    if(pixelImg == 0){
        fprintf(stderr, "Unable to allocate memory \n");
        exit(1);
    }
    c = fgetc(fh);
    c = fgetc(fh);
    //Skipping over header number
    while((c = fgetc(fh)) != '\n'){
    }
    //Parsing past the comments
    c = fgetc(fh);
    while (c=='#'){
        while (fgetc(fh) != '\n');
            c=fgetc(fh);
    }
    ungetc(c, fh);
    //Get input size
    if(fscanf(fh, "%d %d", &pixelImg->x, &pixelImg->y) !=2){
        fprintf(stderr, "A width or Height image dimensions is missing in the file.");
        exit(1);
    }
    //Grabbing color
    fscanf(fh, "%d", &max_color);
    //Allocating space for buffer to store data
    pixelImg->data = (pixelData*)malloc((Color+1)*pixelImg->x*pixelImg->y);
    if(pixelImg->data == 0){
        fprintf(stderr, "Error: Memory could not be allocated.");
        exit(1);
    }
    fgetc(fh);
        j=0;
        i=0;
        //Iterates through file
        //If c is not a space, it puts it into buffer
        while ((c = fgetc(fh)) != EOF){
            if(isspace(c)){
                while(isspace(c = fgetc(fh))){
                }
                ungetc(c, fh);
                //Convert ascii to int
                k = atoi(buffer);
                //Checking to see if pixel number is over a byte in size
                if(k > Color){
                    fprintf(stderr, "Error! Pixel number is too big.\n");
                    exit(1);
                }
                t++;
                if(t == 1){
                    pixelImg->data[j].r = k;
                }

                if(t == 2){
                    pixelImg->data[j].g = k;
                }

                if(t == 3){
                    pixelImg->data[j].b = k;
                    t = 0;
                }

                j++;
                i = 0;
                memset(buffer, '\0', sizeof(buffer));
            }
            else{
                buffer[i++] = c;
            }
        }
                ungetc(c, fh);
    fclose(fh);

    FILE *fp;

    fp = fopen(outputFile, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "# John Sadie was here!\n");
    fprintf(fp, "%d %d\n", pixelImg->x, pixelImg->y);
    fprintf(fp, "%d\n", Color);
            for (j=0; j< sizeof(pixelData)*pixelImg->x*pixelImg->y; j++){
                    t++;
                    if(t == 1){
                       fwrite(&pixelImg->data[j].r,1,1, fp);
                    }

                    if(t == 2){
                       fwrite(&pixelImg->data[j].g,1,1, fp);
                    }

                    if(t == 3){
                      fwrite(&pixelImg->data[j].b,1,1, fp);
                        t = 0;
                    }
            }
    return 0;
    fclose(fp);
}

static pixelImage *p6top3(const char *file, const char *outputFile){
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

    fp = fopen(outputFile, "wb");
    if (!fp){
         fprintf(stderr, "ERROR! Can't open file: '%s'\n", file);
         exit(1);
    }
                int i;
                fprintf(fp, "P3\n");
                fprintf(fp, "# John Sadie was here!\n");
                fprintf(fp, "%d %d\n", pixelImg->x, pixelImg->y);
                fprintf(fp, "%d\n", Color);

                for(i = 0; i < pixelImg->x * pixelImg->y; i++){
                fprintf(fp, "%d", pixelImg->data[i].r);
                fprintf(fp, "\n");
                fprintf(fp, "%d", pixelImg->data[i].g);
                fprintf(fp, "\n");
                fprintf(fp, "%d", pixelImg->data[i].b);
                fprintf(fp, "\n");
                }
    fclose(fp);
}

int main(int argc, char *argv[]){
    int c;

    pixelImage *image;
      //Check if arguments are not equal to 4
       if(argc != 4){
        fprintf(stderr, "ERROR\n");
        return 1;
    }
    char *outputType = argv[1];
    int input = atoi(outputType);
    char *inputType = argv[2];
    char *outputFile = argv[3];

    FILE *fp;
    fp = fopen(inputType, "r");
    if(fp == 0){
        fp = fopen(inputType, "rb");
    }
    fgetc(fp);
    c = fgetc(fp);
    ungetc(c, fp);
    //P3
    if(c == 51){
        if(input == 3){
        image = ReadWriteP3(inputType, outputFile);
        }
        if(input  == 6){
        image = p3top6(inputType, outputFile);
        }
    }
    //P6
      if(c == 54){
        if(input == 3){
        image = p6top3(inputType, outputFile);
        }
        if(input  == 6){
        image = ReadWriteP6(inputType, outputFile);
        }
    }



    //Reading/Writing a p3 ppm file
    //image = ReadWriteP3("p3.ppm", "outputp3.ppm");
    //Reading/Write a P6 ppm file
   // image = ReadWriteP6("p6.ppm", "outputp6.ppm");
    //Reading/Writing from P6 to P3
    //image = p6top3("p6.ppm", "p6top3.ppm");
    //Reading/Writing from P3 to P3
    //image = p3top6("p3.ppm", "p3top6.ppm");
    //Testing print statement
    printf("Did it work?");

}
