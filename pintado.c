#include "../../sdk/dexsdk.h"

/*----MOVEMENTS-----*/
#define RIGHT 'd'
#define LEFT 'a'
#define TOP 'w'
#define BOTTOM 's'
#define TL 'q'
#define TR 'e'
#define BL 'z'
#define BR 'c'
#define EXIT 'p'
#define FILL 'f'
/*----COLORS-----*/
#define _BLACK '1'
#define _BLUE '2'
#define _GREEN '3'
#define _RED '4'
#define _BROWN '5'
#define _YELLOW '6'
#define _WHITE '7'
#define _ERASE _WHITE
#define _CLEAR '0'
/*----DIMENSION-----*/
#define MIN_X 165
#define MIN_Y 45
#define MAX_X MIN_X+150-1
#define MAX_Y MIN_Y+150-1
/*----SIZE-----*/
#define TOOL_FONT_SIZE 0



typedef struct _POINT{
	int x;
	int y;
}POINT;

void exit_pintado();
void erase(int, int, int, int);
void clear_screen();
void clear_canvas();
void set_up_workarea();
void set_up_home();
void draw_line(int, int, int, int, int);
void draw_vertical_line(int, int, int, int);
void draw_horizontal_line(int, int, int, int);
void reset_points();
void display_readme();

/*matrix operations for virtual canvas*/
void initialize_pixel_matrix();
void color_pixel(POINT, int);
void fill_pixel_matrix(int, int, int);
void reset_pixel_matrix();

POINT end;
int **image = NULL;


int main(){
	int i, color = BLACK, flag=1;
	char keypress;
	
	set_graphics(VGA_320X200X256);
	set_up_home();
	reset_points();
	while(flag){
		keypress = (char)getch();
		switch(keypress){
			case '0':
				exit_pintado();
				return;
			case '1':
				flag=0;
				break;
		}
	}
	set_up_workarea();
	initialize_pixel_matrix();
	while(1){
		flag=0;
	get_key:
		keypress = (char)getch();
		switch(keypress){
			case RIGHT:
				if(end.x < MAX_X) end.x++;
				break;
			case LEFT:
				if(end.x > MIN_X) end.x--;
				break;
			case TOP:
				if(end.y > MIN_Y) end.y--;
				break;
			case BOTTOM:
				if(end.y < MAX_Y) end.y++;
				break;
			case TL:
				if(end.x > MIN_X && end.y > MIN_Y){
					end.x--;
					end.y--;
				}
				break;
			case TR:
				if(end.x < MAX_X && end.y > MIN_Y){
					end.x++;
					end.y--;
				}
				break;
			case BL:
				if(end.x > MIN_X && end.y < MAX_Y){
					end.x--;
					end.y++;
				}
				break;
			case BR:
				if(end.x < MAX_X && end.y < MAX_Y){
					end.x++;
					end.y++;
				}
				break;
			case FILL:
				flag=1;
				goto get_key;

			case _BLACK:
				color = BLACK;
				flag++;
				break;
			case _BLUE:
				color = BLUE;
				flag++;
				break;
			case _GREEN:
				color = GREEN;
				flag++;
				break;
			case _RED:
				color = RED;
				flag++;
				break;
			case _BROWN:
				color = BROWN;
				flag++;
				break;
			case _YELLOW:
				color = YELLOW;
				flag++;
				break;
			case _ERASE:
				color = WHITE;
				flag++;
				break;
			case _CLEAR:
				clear_canvas();
				reset_pixel_matrix();
				reset_points();
				color = BLACK;
				break;
			case EXIT:
				exit_pintado();
				return;
		}
		if(flag==2){
			fill_pixel_matrix(end.x - MIN_X, end.y - MIN_Y, color);
		}
		color_pixel(end, color);
		write_pixel(end.x, end.y, color);
	}
}

void initialize_pixel_matrix(){
	int i,j;

	image = (int**)malloc(sizeof(int)*150);
		
	for(i=0;i<150;i++){
		image[i]=(int*)malloc(sizeof(int)*150);
		for(j=0;j<150;j++)
			image[i][j] = WHITE;
	}
}

void reset_pixel_matrix(){
	int i,j;
		
	for(i=0;i<150;i++){
		for(j=0;j<150;j++)
			image[i][j] = WHITE;
	}
}

//color the pixel in the matrix, not the canvas
void color_pixel(POINT p, int c){
	//adjust points, with reference to the canvas
	int x, y;
	x = p.x - MIN_X;
	y = p.y - MIN_Y;
	if(x>=0 && x<150 && y>=0 && y<150)
		image[x][y] = c;
}

//fill feature; colors the current pixel and every pixel adjacent to it 
//(iff have the same color) with the specified color
//parameters must already be adjusted
void fill_pixel_matrix(int x, int y, int c){
	int colour = image[x][y];
	image[x][y] = c;
	write_pixel(x+MIN_X,y+MIN_Y,c);
	//check all points in the left of the current pixel
	if(y-1>=0){
		/* RECURSE TOP LEFT */
		//if(x-1 >= 0 && image[x-1][y-1] == colour)fill_pixel_matrix(x-1, y-1, c);
		/* RECURSE LEFT */
		if(image[x][y-1] == colour)fill_pixel_matrix(x, y-1, c);
		/* RECURSE TOPRIGHT */
		//if(x+1 < 150 && image[x+1][y-1] == colour)fill_pixel_matrix(x+1, y-1, c);
	}
	//check all points in the right of the current pixel
	if(y+1 < 150){
		/* CHECK TOP RIGHT */
		//if(x-1 >= 0 && image[x-1][y+1] == colour)fill_pixel_matrix(x-1, y+1, c);
		/* CHECK RIGHT */
		if(image[x][y+1] == colour)fill_pixel_matrix(x, y+1, c);
		/* CHECK BOTTOM RIGHT */
		//if(x+1 < 150 && image[x+1][y+1] == colour)fill_pixel_matrix(x+1, y+1, c);
	}
	/* CHECK TOP */
	if(x-1 >= 0 && image[x-1][y] == colour)fill_pixel_matrix(x-1, y, c);
	/* CHECK BOTTOM */
	if(x+1 < 150 && image[x+1][y] == colour)fill_pixel_matrix(x+1, y, c);

}

void reset_points(){
	end.x = (MAX_X+MIN_X)/2, end.y = (MAX_Y+MIN_Y)/2;
}

void exit_pintado(){
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

//basically covers an area with a black rectangle 
void erase(int x, int y, int w, int h){ 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,100);
}

void clear_screen(){
	erase(0, 0, 400, 220);
}

void clear_canvas(){
	int i,j;
	int x=MIN_X,y=MIN_Y,w=150,h=150;
   for (i=y;i<(y+h);i++)
      for (j=x;j<(x+w);j++)
         write_pixel(j,i,WHITE);
}

void set_up_home(){
	int i,j;
	for(i=-320,j=0; i<0; i+=20,j+=20){
			draw_line(i,0,j,200,RED);
			draw_line(i+6,0,j+6,200,GREEN);
			draw_line(i+12,0,j+12,200,BLUE);
	}
	
	write_text("PINTADO", 125, 90, WHITE, 1);
	write_text("1 - Start", 120, 150, WHITE, 0);
	write_text("0 - Close", 120, 170, WHITE, 0);

}

void draw_horizontal_line(int row, int y1, int y2, int c){
	int i;
	for(i=y1; i<y2; i++){
		write_pixel(i,row, c);
	}
}

void draw_vertical_line(int col, int x1, int x2, int c){
	int i;
	for(i=x1; i<x2; i++){
		write_pixel(col,i, c);
	}
}

void draw_line(int x1, int y1, int x2, int y2, int c){
	//bresenham's algo for drawing a line
	int dx = x2-x1, dy = y2-y1;
	int abs_dy = dy*dy/dy;
	int m = 2*abs_dy;
	int x = x1, y = y1, e=0, t=dx, t_inc=2*dx;
	abs_dy = (abs_dy<0)?abs_dy*-1:abs_dy;
	while(x<=x2){
		write_pixel(x,y,c);
		e=e+m;
		if(e>=t){
			y++;
			t+=t_inc;
		}
		x++;
	}
}

void set_up_workarea(){
	clear_screen();
	draw_horizontal_line(2, MIN_X, MAX_X, LIGHTMAGENTA);
	draw_horizontal_line(MIN_Y-1, MIN_X, MAX_X, LIGHTMAGENTA);
	draw_vertical_line(MIN_X, 2, MIN_Y-1, LIGHTMAGENTA);
	draw_vertical_line(MAX_X, 2, MIN_Y-1, LIGHTMAGENTA);

	draw_horizontal_line(5, 1, 164, LIGHTRED);
	draw_horizontal_line(70, 1, 164, LIGHTRED);
	draw_horizontal_line(150, 1, 164, LIGHTRED);
	

	write_text("P", MIN_X+45, 15, DARKGRAY, 1);
	write_text("I", MIN_X+55, 15, BLUE, 1);
	write_text("N", MIN_X+65, 15, GREEN, 1);
	write_text("T", MIN_X+75, 15, RED, 1);
	write_text("A", MIN_X+85, 15, BROWN, 1);
	write_text("D", MIN_X+95, 15, YELLOW, 1);
	write_text("O", MIN_X+105, 15, WHITE, 1);

	write_text("Colors", 45,15, CYAN, 0);				
	write_text("1-Black",5,25,DARKGRAY,TOOL_FONT_SIZE);
	write_text("2-Blue",85,25,BLUE,TOOL_FONT_SIZE);
	write_text("3-Green",5,35,GREEN,TOOL_FONT_SIZE);
	write_text("4-Red",85,35,RED,TOOL_FONT_SIZE);
	write_text("5-Brown",5,45,BROWN,TOOL_FONT_SIZE);
	write_text("6-Yellow",85,45,YELLOW,TOOL_FONT_SIZE);
	write_text("7-White",40,55,WHITE,TOOL_FONT_SIZE);

	write_text("Movements", 37,75, CYAN, 0);				
	write_text("w-Up",5,85,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("d-Right",85,85,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("s-Down",5,95,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("a-Left",85,95,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("q-Upper Left",22,105,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("e-Upper Right",17,115,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("z-Lower Left",22,125,LIGHTGRAY,TOOL_FONT_SIZE);
	write_text("c-Lower Right",17,135,LIGHTGRAY,TOOL_FONT_SIZE); 

	write_text("Others", 45,155, CYAN, 0);	
	write_text("f<color_key>-Fill",5,165,LIGHTGRAY,TOOL_FONT_SIZE);			
	write_text("0-Clear",50,175,RED,TOOL_FONT_SIZE);
	write_text("p-EXIT",50,185,RED,TOOL_FONT_SIZE);

	clear_canvas();  
}
