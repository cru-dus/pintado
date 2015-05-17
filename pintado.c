#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"
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
#define MAX_X MIN_X+150
#define MAX_Y MIN_Y+150
/*----SIZE-----*/
#define TOOL_FONT_SIZE 50



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
void draw_rectangle(int, int, int, int, int);
void reset_points();
void display_readme();

POINT start, end;

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
			case '2':
				clear_screen();
				set_graphics(VGA_TEXT80X25X16);
				display_readme();
				break;
		}
	}
	set_up_workarea();
	while(1){
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
			case _BLACK:
				color = BLACK;
				break;
			case _BLUE:
				color = BLUE;
				break;
			case _GREEN:
				color = GREEN;
				break;
			case _RED:
				color = RED;
				break;
			case _BROWN:
				color = BROWN;
				break;
			case _YELLOW:
				color = YELLOW;
				break;
			case _ERASE:
				color = WHITE;
				break;
			case _CLEAR:
				clear_canvas();
				reset_points();
				color = BLACK;
				break;
			case EXIT:
				exit_pintado();
				return;
		}
		write_pixel(end.x, end.y, color);
	}
}

void reset_points(){
	start.x = (MAX_X+MIN_X)/2, start.y = (MAX_Y+MIN_Y)/2, end.x = (MAX_X+MIN_X)/2, end.y = (MAX_Y+MIN_Y)/2;
}

void exit_pintado(){
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
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
	int x=165,y=45,w=150,h=150;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,WHITE);
}

void display_readme(){
	FILE *fp = fopen("./README.txt", "r");
	char *line;
	if(fp == NULL){
		printf("ERROR in opening the file README\n");
		return;
	}
	
	while(1){
		if(fgets(line, 250, fp) == NULL)break;
		printf("%s",line);
	}
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
	write_text("2 - Read Me", 115, 160, WHITE, 0);
	write_text("0 - Close", 120, 170, WHITE, 0);

}

void draw_line(int x1, int y1, int x2, int y2, int c){
	//bresenham's algo for drawing a line
	int dx = x2-x1, dy = y2-y1;
	int abs_dy = dy*dy/dy;
	int m = 2*abs_dy;
	int x = x1, y = y1, e=0, t=dx, t_inc=2*dx;
	
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

void draw_rectangle(int x1, int y1, int x2, int y2, int c){

}

void set_up_workarea(){
	clear_screen();
  write_text("1-Black",5,5,DARKGRAY,TOOL_FONT_SIZE);
  write_text("2-Blue",5,15,BLUE,TOOL_FONT_SIZE);
  write_text("3-Green",5,25,GREEN,TOOL_FONT_SIZE);
  write_text("4-Red",5,35,RED,TOOL_FONT_SIZE);
  write_text("5-Brown",5,45,BROWN,TOOL_FONT_SIZE);
  write_text("6-Yellow",5,55,YELLOW,TOOL_FONT_SIZE);
  write_text("7-White",5,65,WHITE,TOOL_FONT_SIZE);
  write_text("w-Up",5,85,WHITE,TOOL_FONT_SIZE);
  write_text("s-Down",5,95,WHITE,TOOL_FONT_SIZE);
  write_text("a-Left",5,105,WHITE,TOOL_FONT_SIZE);
  write_text("d-Right",5,115,WHITE,TOOL_FONT_SIZE);
  write_text("q-Upper Left",5,125,WHITE,TOOL_FONT_SIZE);
  write_text("e-Upper Right",5,135,WHITE,TOOL_FONT_SIZE);
  write_text("z-Lower Left",5,145,WHITE,TOOL_FONT_SIZE);
  write_text("c-Lower Right",5,155,WHITE,TOOL_FONT_SIZE); 
  write_text("0-Clear",5,175,WHITE,TOOL_FONT_SIZE);
  write_text("f-Open File",5,185,WHITE,TOOL_FONT_SIZE);  
  write_text("p-EXIT",5,195,RED,TOOL_FONT_SIZE);

	clear_canvas();  
}




