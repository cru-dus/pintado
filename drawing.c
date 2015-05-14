#include <stdio.h>
#include <stdlib.h>
#define WHITE 'O'
#define TERMINATE 'X'
#define INITIALIZE 'I'
#define CLEAR 'C'
#define COLOR 'L'
#define DISPLAY 'S'
#define VERTICAL 'V'
#define HORIZONTAL 'H'
#define KAHON 'K'
#define FILL 'F'

typedef struct{
	char** image;
	char filename[10];
	int rows;
	int cols;
}IMAGE;

/* function that creates rowsxcols image initially colored WHITE*/
char ** createImage(int rows, int cols){
	int i;
	char** image = (char**)malloc(rows * sizeof(char*));
	for(i=0; i<rows; i++){
		int j;
		image[i] = (char*)malloc(cols * sizeof(char));
		for(j=0; j<cols; j++) image[i][j] = WHITE;
	}
	return image;
}

/* function that resets each pixels of an image with WHITE*/
void clearImage(IMAGE image){
	int i, j;
	for(i=0; i<image.rows; i++)
		for(j=0; j<image.cols; j++)
			image.image[i][j] = WHITE;
}

/* function that colors a specified coordinate with color C*/
void colorPixel(char** image, int x, int y, char C){
	image[x-1][y-1] = C;
}

/* function that displays the image and its filename */
void displayImage(IMAGE image){
	int i, j;
	printf("%s\n", image.filename);
	for(i=0; i<image.rows; i++){
		for(j=0; j<image.cols; j++)
			printf("%c",image.image[i][j]);
		printf("\n");
	}
}

/* function that draws a vertical line in column X between rows y1 and y2*/
void drawVerticalLine(IMAGE image, int column, int row1, int row2, char C){
	int i, j;
	for(i=0; i<image.rows; i++)
		if(i>=row1-1 && i<=row2-1)
			image.image[i][column-1] = C;
}

/* function that draws a horizontal line in row X between cols y1 and y2*/
void drawHorizontalLine(IMAGE image, int row, int col1, int col2, char C){
	int i, j;
	for(i=0; i<image.cols; i++)
		if(i>=col1-1 && i<=col2-1)
			image.image[row-1][i] = C;
}

/* function that draws a rectangle givent two points */
void drawRectangle(IMAGE image, int x1, int y1, int x2, int y2, char C){
	int i;
	for(i=0; i<image.cols; i++)
		if(i>=y1 && i<=y2)
			drawVerticalLine(image, i, x1, x2, C);
}

/* function that fills */
void fillImage(IMAGE image, int x, int y, char C){
	char colour = image.image[x][y];
	image.image[x][y] = C;
	if(y-1 >= 0){
		/* CHECK TOP LEFT */
		if(x-1 >= 0 && image.image[x-1][y-1] == colour)fillImage(image, x-1, y-1, C);
		/* CHECK LEFT */
		if(image.image[x][y-1] == colour)fillImage(image, x, y-1, C);
		/* BOTTOM LEFT */
		if(x+1 < image.rows && image.image[x+1][y-1] == colour)fillImage(image, x+1, y-1, C);
	}

	if(y+1 < image.cols){
		/* CHECK TOP RIGHT */
		if(x-1 >= 0 && image.image[x-1][y+1] == colour)fillImage(image, x-1, y+1, C);
		/* CHECK RIGHT */
		if(image.image[x][y+1] == colour)fillImage(image, x, y+1, C);
		/* CHECK BOTTOM RIGHT */
		if(x+1 < image.rows && image.image[x+1][y+1] == colour)fillImage(image, x+1, y+1, C);
	}

	/* CHECK TOP */
	if(x-1 >= 0 && image.image[x-1][y] == colour)fillImage(image, x-1, y, C);
	/* CHECK BOTTOM */
	if(x+1 < image.rows && image.image[x+1][y] == colour)fillImage(image, x+1, y, C);
}

main(){
	
	FILE *fp;
	int i, j;
	char command;

	fp = fopen("input.txt", "r");
	if(fp == NULL){
		printf("Error in opening input file 'input.txt'!");
		exit(0);
	}

	fscanf(fp, "%c", &command);
	while(command != TERMINATE){
		IMAGE newImage;
		int w, x, y, z; // storage for coordinate inputs
		char c; //storage for color inputs
		char f[10]; //storage for file name
		switch(command){
			case INITIALIZE:
				fscanf(fp, " %d %d\n", &(newImage.rows), &(newImage.cols));
				newImage.image = createImage(newImage.rows, newImage.cols);
				break;
			case CLEAR:
				clearImage(newImage);
				break;
			case COLOR:
				fscanf(fp, " %d %d %c\n", &x, &y, &c);
				colorPixel(newImage.image, x, y, c);
				break;
			case DISPLAY:
				fscanf(fp, " %s", f);
				strcpy(newImage.filename, f);
				displayImage(newImage);
				break;
			case VERTICAL:
				fscanf(fp, " %d %d %d %c\n", &x, &y, &z, &c);
				drawVerticalLine(newImage, x, y, z, c);
				break;
			case HORIZONTAL:
				fscanf(fp, " %d %d %d %c\n", &x, &y, &z, &c);
				drawHorizontalLine(newImage, x, y, z, c);
				break;
			case KAHON:
				fscanf(fp," %d %d %d %d %c\n", &w, &x, &y, &z, &c);
				drawRectangle(newImage, w, x, y, z, c);
				break;
			case FILL:
				fscanf(fp, " %d %d %c\n", &x, &y, &c);
				fillImage(newImage, x-1, y-1, c);
				break;
		}
		fscanf(fp, "%c", &command);
	}
}