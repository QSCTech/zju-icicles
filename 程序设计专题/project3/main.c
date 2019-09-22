#include "include/graphics.h"
#include "include/extgraph.h"
#include "include/genlib.h"
#include "include/simpio.h"
#include "include/random.h"
#include "include/strlib.h"
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>//include
//stuct area
struct Positon
{
	double x1,y1;
	double x2,y2;
};
//define area
static char Text[100];
static int textlen = 0;
static int location = -1;
static bool isBlink = FALSE;
static bool isDisplay = FALSE;
#define TIMER_BLINK 1
#define mseconds 500
//dim area
double width,length;//to record the map
bool Eraser_Button = 0;//react to the eraser
bool Pencil_Button = 0;//react to the pencil
bool Text_Button = 0;//react to Text
bool LEFT_Switch = 0;//react to the LEFt_BUTTON
bool Square_Button = 0;//react to the square button
bool Circle_Button = 0;//react to the circle button 
struct Positon sQuare;
struct Positon cIrcle;
struct Positon sTring;
double ri;
bool Square_Number = 0;
bool Circle_Number = 0;
bool String_Button = 0;
bool String_Number = 0;
bool Move_Button = 0;
bool Move_Square = 0;
bool Move_Circle = 0;
bool Move_String = 0;
double function = 0.1; 
//function area 
void CreateCAD(void);
void INITCAD(void);
void MouseEventProcess(int x,int y,int button,int event);
void KeyboardEventProcess(int key,int event);
void TimerEventProcess(int timerID);  
void CharEventProcess(char c);
int JudgeSquare(double mx,double my)
{
	double x;
	double y;
	x = (mx - sQuare.x1)*(mx - sQuare.x2);
	y = (my - sQuare.y1)*(my - sQuare.y2);
	if(x<0 && y<=0)
	return 1;
	else
	return 0;
}
int JudgeCircle(double mx,double my)
{
	double distance;
	distance = sqrt((mx - cIrcle.x1)*(mx - cIrcle.x1)+(my - cIrcle.y1)*(my - cIrcle.y1));
	if(distance <= ri)
	return 1;
	else
	return 0;
}
int JudgeString(double mx,double my)
{
	struct Positon line;
	line.x1 = mx - sTring.x1;
	line.y1 = my - sTring.y1;
	line.x2 = mx - sTring.x2;
	line.y2 = my - sTring.y2;
	double x;
	double y;
	x = (mx - sTring.x1)*(mx - sTring.x2);
	y = (my - sTring.y1)*(my - sTring.y2);
	double f1,f2,f3,f;
	f1 =  line.x1 * line.x2 + line.y1 * line.y2;
	f2 = sqrt(line.x1*line.x1+line.y1*line.y1);
	f3 = sqrt(line.x1*line.x1+line.y2*line.y2);
	f = acos(f1/f2/f3);
	if(x < 0 && y < 0 && fabs(f-3.1415)<1 || fabs(f-3.1415)>4.5)
	return 1;
	else 
	return 0;
}
//end of function area
void Main()   
{  
	// funciton
    InitConsole();  
    InitGraphics();          
	CreateCAD(); 
	INITCAD();
	// register
	registerMouseEvent(MouseEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
	registerCharEvent(CharEventProcess);  
    registerTimerEvent(TimerEventProcess); 
    //Text Blink
    
    if(isBlink) startTimer(TIMER_BLINK,mseconds);
	isBlink = ! isBlink;
    if(isBlink) 
	startTimer(TIMER_BLINK,mseconds);
    else
    cancelTimer(TIMER_BLINK);
	
}  
void CreateCAD(void)//Initilize the map
{
	width = GetWindowWidth();
	length = GetWindowHeight();
	SetPenColor("black");
	SetPenSize(2); 
	MovePen(width-3,length-0.15);
	DrawTextString("To Get Help In Command Line");
	//margin
	MovePen(0.15,0.15);
	DrawLine(0,length-0.15);
	DrawLine(width-0.3,0);
	DrawLine(0,-length+0.15);
	DrawLine(-width+0.15,0);
	//
	MovePen(1.15,length-0.2);
	DrawLine(width-1.3,0);
	//option 
	MovePen(0.15,0.15);
	DrawLine(0,length-0.15);
	DrawLine(1,0);
	DrawLine(0,-length+0.15);
	DrawLine(-1,0);//INITIALIZE the left square
	SetPenSize(1);
	MovePen(0.3,0.3);//The last Square x(0.3-1.05) y (0.3-1.05)
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,0.35);//change
	DrawTextString("   Eraser");//change
	MovePen(0.45,0.48);
	DrawLine(0,0.5);
	DrawLine(0.5,0);
	DrawLine(0,-0.5);
	DrawLine(-0.5,0);
	SetPenColor("red");
	MovePen(0.45,0.48+0.35);
	DrawLine(0.5,0);
	//Initialize Drawline
	SetPenColor("black");//range from(0.3-1.05)(1.5-2.25)
	MovePen(0.3,1.5);
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,1.55);
	DrawTextString("   Pencil");//finish the pencil structure
	MovePen(0.5,1.75);
	DrawLine(0.3,0.4);
	DrawLine(0.15,0.075);
	DrawLine(0,-0.15);
	DrawLine(-0.3,-0.4);
	DrawLine(-0.15,0.1);
	MovePen(0.8,2.15);
	DrawLine(0.15,-0.1);//finish the logo of pencil
	MovePen(0.3,2.75);//range from(0.3-1.05)(2.75-3.5)
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,2.8);
	DrawTextString("    Text");//finish the Text Structure;
	MovePen(0.6,3);
	DrawLine(0,0.3);
	DrawLine(-0.1,0);
	DrawLine(0,0.1);
	DrawLine(0.3,0);
	DrawLine(0,-0.1);
	DrawLine(-0.1,0);
	DrawLine(0,-0.3);
	DrawLine(-0.1,0);//finish the logo of text;
	// 
	MovePen(0.3,4);//(0.3-1.05) (4-4.75)
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,4.05);
	DrawTextString("  Square");
	MovePen(0.5,4.25);
	SetPenColor("Green");
	DrawLine(0,0.4);
	DrawLine(0.4,0);
	DrawLine(0,-0.4);
	DrawLine(-0.4,0);
	SetPenColor("black");
	//finish the structure the square	
	MovePen(0.3,5);//(0.3-1.05) (5-5.75)
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,5.05);
	DrawTextString("  Circle");
	MovePen(0.85,5.45);
	SetPenColor("Green");
	DrawArc(0.2,0,360);
	SetPenColor("black");
	//finish the structure of circle
	MovePen(0.3,6);//(0.3-1.05) (6-6.75)
	DrawLine(0,0.75);
	DrawLine(0.75,0);
	DrawLine(0,-0.75);
	DrawLine(-0.75,0);
	MovePen(0.35,6.05);
	DrawTextString("  String");
	MovePen(0.6,6.25);
	SetPenColor("Green");
	DrawLine(0.3,0.4);
	SetPenColor("black");
	//finish the structure of string
	//finish the structure
	//start the movement
	MovePen(1.5,length-0.15);
	DrawTextString(" Move");
	MovePen(2.5,length-0.15);
	SetPenSize(2);
	DrawLine(0,3);
	DrawLine(0,-3.05);
	SetPenSize(1);
	//finish the Move area
	//set mouse position
	MovePen(width/2,length/2);	
}
void INITCAD(void)//information function
{
	printf("Welcome to USE The CAD Software\n");
	printf("**||When you press a button,you will know its option\n");
	printf("After you finish a step,system will give you the feedback\n");
	printf("Function HELP\n");
	printf("press the area of move to load in MOVE function\n");
	printf("**You can press F8 to increase Pensize AND press F9 to decrease Pensize\n");
	printf("||Function Move");
	printf("**You can press F1 to increase Size AND press F2 to decrease Pensize\n");
	printf("***You can ↑↓←→to move the image\n");
	printf("****You can press F4 and F5 to control the size\n");
	printf("*****Press F11 to delete the image\n"); 
	printf("****Press ESC when finishing\n");
	printf("NOW ENTER THE SYSTEM\n");
	printf("\n");
}
void MouseEventProcess(int x,int y,int button,int event)
{
	double mx,my;
	static double lx = 0.0,ly = 0.0;
	mx = ScaleXInches(x);
	my = length - ScaleXInches(y);
	switch(event)
	{
		case BUTTON_DOWN:
			if(button == LEFT_BUTTON)
			{
				LEFT_Switch = 1;
				if(mx>=0.3 && mx <= 1.05 && my >= 0.3 && my <= 1.05)//control the eraser button
				{
					Eraser_Button = !Eraser_Button;
					if(Eraser_Button)
					{ 
					printf("|| Click Again to close the Raser \n");
					printf("** You can use the Raser to clean\n");
					Pencil_Button = 0;//add elments when using
					Text_Button = 0;
					Square_Button = 0;
					Circle_Button = 0;
					Move_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					String_Button = 0;
					} 
				}
				if(mx>=0.3 && mx <= 1.05 && my >= 1.5 && my <= 2.25)//control the pencil button
				{
					Pencil_Button = !Pencil_Button;
					if(Pencil_Button)
					{ 
					printf("|| Click Again to close the Pencil \n");
					printf("** You can use the Pencil to draw\n");
					Eraser_Button = 0;//add elments when using
					Text_Button = 0;
					Square_Button = 0;
					Move_Button = 0;
					Circle_Button = 0;
					String_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					} 
				}
				if(mx>=0.3 && mx <= 1.05 && my >= 2.75 && my <= 3.5)//control the text button
				{
					Text_Button = !Text_Button;
					if(Text_Button)
					{ 
					printf("|| Click Again to close the Text \n");
					printf("** You can use the Text to input word\n");
					printf("*** Choose a location to input the word\n");
					Eraser_Button = 0;//add elments when using
					Pencil_Button = 0;
					Square_Button = 0;
					Circle_Button = 0;
					Move_Button = 0;
					String_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					MovePen(width/2,length/2);//intialize the pen location
					} 
				}
				if(mx>=0.3 && mx <= 1.05 && my >= 4 && my <= 4.75)//control the square button
				{
					Square_Button = !Square_Button;
					if(Square_Button)
					{ 
					printf("|| Click Again to close the Square \n");
					printf("** You can use this to draw a Square\n");
					printf("*** locate two points to create a Square\n");
					Eraser_Button = 0;//add elments when using
					Text_Button = 0;
					Pencil_Button = 0;
					Square_Number = 1;
					Circle_Button = 0;
					String_Button = 0;
					Move_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					} 
				}
				if(mx>=0.3 && mx <= 1.05 && my >= 5 && my <= 5.75)//control the circle button
				{
					Circle_Button = !Circle_Button;
					if(Circle_Button)
					{ 
					printf("|| Click Again to close the circle and click once for one circle\n");
					printf("** You can use this to draw a circle\n");
					printf("*** locate two points to create a circle.One is the point and the other is the R\n");
					Eraser_Button = 0;//add elments when using
					Text_Button = 0;
					Pencil_Button = 0;
					Square_Button =0;
					Circle_Number = 1;
					Move_Button = 0;
					String_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					} 
				}
					if(mx>=0.3 && mx <= 1.05 && my >= 6 && my <= 6.75)//control the string button
				{
					String_Button = !String_Button;
					if(String_Button)
					{ 
					printf("|| Click Again to close the String \n");
					printf("** You can use this to draw a String\n");
					printf("*** locate two points to create a String\n");
					Eraser_Button = 0;//add elments when using
					Text_Button = 0;
					Pencil_Button = 0;
					Square_Button =0;
					Circle_Button = 0;
					Move_Button = 0;
					String_Number = 1;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					} 
				}
				//end of the button 
				//define the movement
				if(mx>1.5 && mx <= 2.5 && my >= length-0.15 && my <= length)//control the string button
				{
					Move_Button = !Move_Button;
					if(Move_Button)
					{ 
					printf("|| Click Again to close the Movement \n");
					printf("** You can use this to Move and aggregrate the graphics\n");
					printf("After choosing a image successfully,it will turn into green\n");
					printf("Press F1 and F2 to largen and smallen \n");
					printf("After finishing, Press ESC \n");
					printf("Press ↑↓←→to move \n");
					printf("Press F4 and F5 to increase and decrease the size\n");
					Eraser_Button = 0;//add elments when using
					Text_Button = 0;
					Pencil_Button = 0;
					Square_Button = 0;
					Circle_Button = 0;
					String_Button = 0;
					Move_Square = 0;
					Move_Circle = 0;
					Move_String = 0;
					} 
				}
				//define the text location
				if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 && Text_Button)
				{
					MovePen(mx,my);
				}
				//define the square function
				if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 && Square_Button)
				{
					if(Square_Number)
					{
						sQuare.x1 = mx;
						sQuare.y1 = my;
						Square_Number = 0;
					}
					else
					{
						sQuare.x2 = mx;
						sQuare.y2 = my;
						MovePen(sQuare.x1,sQuare.y1);
						DrawLine(sQuare.x2-sQuare.x1,0);
						DrawLine(0,sQuare.y2-sQuare.y1);
						DrawLine(sQuare.x1-sQuare.x2,0);
						DrawLine(0,sQuare.y1-sQuare.y2);
						Square_Button = 0;
					}
				}
				//define the circle function
				if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 && Circle_Button)
				{
					if(Circle_Number)
					{
						cIrcle.x1 = mx;
						cIrcle.y1 = my;
						Circle_Number = 0;
					}
					else
					{
						cIrcle.x2 = mx;
						cIrcle.y2 = my;
						ri = sqrt((cIrcle.x2 - cIrcle.x1)*(cIrcle.x2 - cIrcle.x1)+(cIrcle.y2 - cIrcle.y1)*(cIrcle.y2 - cIrcle.y1));
						MovePen(cIrcle.x1+ri,cIrcle.y1);
						DrawArc(ri,0,360);
						Circle_Button = 0;
					}
				}
				//define the string function
				if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 && String_Button)
				{
					if(String_Number)
					{
						sTring.x1 = mx;
						sTring.y1 = my;
						String_Number = 0;
					}
					else
					{
						sTring.x2 = mx;
						sTring.y2 = my;
						MovePen(sTring.x1,sTring.y1);
						DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
						String_Button = 0;
					}
				}
				//define the function end
		
				if(Move_Button)
				{
					if(JudgeSquare(mx,my))
						{
							Move_Square = 1;
							Move_Circle = 0;
							Move_String = 0;
							printf("Have choosen the square\n");
							SetPenColor("green");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("black");
						}
					if(JudgeCircle(mx,my))
					{
						Move_Square = 0;
						Move_Circle = 1;
						Move_String = 0;
						printf("Have choosen the circle\n");
						SetPenColor("green");
						MovePen(cIrcle.x1+ri,cIrcle.y1);
						DrawArc(ri,0,360);
						SetPenColor("black");
					}
					if(JudgeString(mx,my))
					{
						Move_Square = 0;
						Move_Circle = 0;
						Move_String = 1;
						printf("Have choosen the string\n");
						SetPenColor("green");
						MovePen(sTring.x1,sTring.y1);
						DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
						SetPenColor("black");
					}
				}
			}
			break;
		case BUTTON_UP:
			{
				if(button == LEFT_BUTTON)
					LEFT_Switch = 0;
				break;
			}
		case MOUSEMOVE:
			{
				if(LEFT_Switch)
				{
					if(Eraser_Button)//Erase_button xiaoguo
					{
						if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 )
						{
							SetPenColor("white");
							SetPenSize(2);
							DrawLine(mx-lx,my-ly);
							MovePen(mx,my);
						}
					}
					if(Pencil_Button)//Erase_button xiaoguo
					{
						if(mx >= 1.5 && mx <= width-0.35 && my >= 0.35 && my <= length-0.35 )
						{
							SetPenColor("black");
							SetPenSize(2);
							DrawLine(mx-lx,my-ly);
							MovePen(mx,my);
						}
					}
				}
				break;
			}
	}
	lx=mx;
	ly=my;
}
void KeyboardEventProcess(int key,int event)//react to keyboard
{
	int Pensize;
	Pensize = GetPenSize();
	static char str[2] = {0,0};
	switch(event)
	{
		case KEY_DOWN:
			//blink function start
				switch (key){
				case VK_F8:
					SetPenSize(Pensize + 1);
					printf("Increase Pensize Success\n");
					break;
				case VK_F9:
						SetPenSize(Pensize - 1);
						printf("Decrease Pensize Success\n");			
					break;
				case VK_UP:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.y1 = sQuare.y1 + function;
							sQuare.y2 = sQuare.y2 + function;//平移参数设置 
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.y1 = sTring.y1 + function;
							sTring.y2 = sTring.y2 + function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							cIrcle.y1 = cIrcle.y1 + function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_DOWN:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.y1 = sQuare.y1 - function;
							sQuare.y2 = sQuare.y2 - function;//平移参数设置 
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.y1 = sTring.y1 - function;
							sTring.y2 = sTring.y2 - function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							cIrcle.y1 = cIrcle.y1 - function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_LEFT:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.x1 = sQuare.x1 - function;
							sQuare.x2 = sQuare.x2 - function;//平移参数设置 
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.x1 = sTring.x1 - function;
							sTring.x2 = sTring.x2 - function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							cIrcle.x1 = cIrcle.x1 - function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_RIGHT:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.x1 = sQuare.x1 + function;
							sQuare.x2 = sQuare.x2 + function;//平移参数设置 
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.x1 = sTring.x1 + function;
							sTring.x2 = sTring.x2 + function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							cIrcle.x1 = cIrcle.x1 + function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_F1:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.x1 = sQuare.x1 + function;
							sQuare.x2 = sQuare.x2 - function;//平移参数设置 
							sQuare.y1 = sQuare.y1 - function;
							sQuare.y2 = sQuare.y2 + function;
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.x1 = sTring.x1 + function;
							sTring.y1 = sTring.y1 - function;
							sTring.x2 = sTring.x2 - function;
							sTring.y2 = sTring.x1 + function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							ri = ri + function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_F2:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("green");
							sQuare.x1 = sQuare.x1 - function;
							sQuare.x2 = sQuare.x2 + function;//平移参数设置 
							sQuare.y1 = sQuare.y1 + function;
							sQuare.y2 = sQuare.y2 - function;
							//
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.x1 = sTring.x1 - function;
							sTring.y1 = sTring.y1 + function;
							sTring.x2 = sTring.x2 + function;
							sTring.y2 = sTring.x1 - function;
							SetPenColor("green");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							SetPenColor("black");
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							ri = ri - function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							cIrcle.x1 = cIrcle.x1 + function;
							SetPenColor("green");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							SetPenColor("black");
						}
						break;
				case VK_ESCAPE:
						if(Move_Square)
						{
							SetPenColor("black");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							Move_Square = 0; 
						}
						if(Move_String)
						{
							SetPenColor("black");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							Move_String = 0;
						}
						if(Move_Circle)
						{
							SetPenColor("black");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							Move_Circle = 0;
						}
						break;
				case VK_F4:
						function = function + 0.1;
						printf("Size Up\n");
						break;
				case VK_F5:
						function = function - 0.1;
						printf("Size Down\n");
						break;
				case VK_F11:
						if(Move_Square)
						{
							SetPenColor("white");
							MovePen(sQuare.x1,sQuare.y1);
							DrawLine(sQuare.x2-sQuare.x1,0);
							DrawLine(0,sQuare.y2-sQuare.y1);
							DrawLine(sQuare.x1-sQuare.x2,0);
							DrawLine(0,sQuare.y1-sQuare.y2);
							SetPenColor("black");
							Move_Square = 0;
						}
						if(Move_String)
						{
							SetPenColor("white");
							MovePen(sTring.x1,sTring.y1);
							DrawLine(sTring.x2-sTring.x1,sTring.y2-sTring.y1);
							sTring.x1 = sTring.x1 + function;
							sTring.y1 = sTring.y1 - function;
							sTring.x2 = sTring.x2 - function;
							sTring.y2 = sTring.x1 + function;
							SetPenColor("black");
							Move_String = 0;
						}
						if(Move_Circle)
						{
							SetPenColor("white");
							MovePen(cIrcle.x1+ri,cIrcle.y1);
							DrawArc(ri,0,360);
							ri = ri + function;
							SetPenColor("black");
							Move_String = 0;
						}
						break;
				default:
					break;
			}
				if(Text_Button)//Text input function
			{
				
				if(key==VK_DELETE||key==VK_BACK){  
                if(location<0)return;  
                int i;  
                SetEraseMode(TRUE);  
                if (isBlink && isDisplay) {  
                   MovePen(GetCurrentX(), GetCurrentY());  
                   DrawTextString("|");  
                   MovePen(GetCurrentX()-TextStringWidth("|"), GetCurrentY());  
                }  
                str[0]=Text[location];  
                MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());  
                DrawTextString(str);  
                if(location==textlen)MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());  
                else{  
                    string s1,s2;  
                    s1=SubString(Text,location+1,textlen);  
                    s2=SubString(Text,location,textlen);   
                    SetEraseMode(TRUE);  
                    DrawTextString(s1);  
                    SetEraseMode(FALSE);  
                    MovePen(GetCurrentX()-TextStringWidth(s2),GetCurrentY());  
                    DrawTextString(s1);  
                    MovePen(GetCurrentX()-TextStringWidth(s1),GetCurrentY());  
                }  
                for(i=location;i<textlen;i++){  
                    Text[i]=Text[i+1];  
                }  
                Text[--textlen]='\0';  
                location--;  
                SetEraseMode(FALSE);                      
            }  
            else if(key==VK_LEFT){  
                if(location<0)return;  
                if (isBlink && isDisplay) {  
                    SetEraseMode(TRUE);  
                    MovePen(GetCurrentX(), GetCurrentY());  
                    DrawTextString("|");  
                    SetEraseMode(FALSE);  
                    MovePen(GetCurrentX()-TextStringWidth("|"), GetCurrentY());  
                }  
                str[0]=Text[location];  
                MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());  
                location--;  
            }  
            else if(key==VK_RIGHT){  
                if(location>=textlen)return;   
                if (isBlink && isDisplay) {  
                    SetEraseMode(TRUE);  
                    MovePen(GetCurrentX(), GetCurrentY());  
                    DrawTextString("|");  
                    SetEraseMode(FALSE);  
                    MovePen(GetCurrentX()-TextStringWidth("|"), GetCurrentY());  
                }  
                str[0]=Text[location+1];  
                MovePen(GetCurrentX()+TextStringWidth(str),GetCurrentY());  
                location++;  
            } 
			//text blink function end 
			}
			break;
	}
} 
void CharEventProcess(char key)  
{  
	if(Text_Button){	//char input area
    if(textlen>=99||GetCurrentX()>=GetWindowWidth()-0.2)return;  
    if(key==VK_BACK||key==VK_DELETE)return;  
    if(key=='\r'){  
        SetEraseMode(TRUE);  
        if(isBlink && isDisplay){  
            DrawTextString("|");  
            MovePen(GetCurrentX()-TextStringWidth("|"),GetCurrentY());  
        }  
        InitConsole();  
        printf("%s\n", Text);  
        system("pause");  
        FreeConsole();  
        MovePen(GetCurrentX()-TextStringWidth(Text), GetCurrentY());  
        DrawTextString(Text);  
        SetEraseMode(FALSE);  
        MovePen(GetCurrentX()-TextStringWidth(Text), GetCurrentY());  
        textlen=0;  
        location=-1;  
        Text[0]='\0';  
    }  
    else{  
        char str[2]={0,0};  
        str[0]=key;  
        if(location==textlen-1){  
            Text[textlen++]=key;  
            Text[textlen]='\0';  
            DrawTextString(str);  
            location++;  
        }  
        else{  
            int i;  
            string s1;  
            s1=SubString(Text,location+1,textlen);   
            SetEraseMode(TRUE);  
            DrawTextString(s1);  
            SetEraseMode(FALSE);  
            MovePen(GetCurrentX()-TextStringWidth(s1),GetCurrentY());  
            DrawTextString(str);  
            DrawTextString(s1);  
            MovePen(GetCurrentX()-TextStringWidth(s1),GetCurrentY());  
            textlen++;  
            location++;  
            for(i=textlen;i>=location+1;i--){  
                Text[i]=Text[i-1];  
            }  
            Text[location]=key;  
        }  
        if (isBlink && isDisplay) {  
            SetEraseMode(TRUE);  
            MovePen(GetCurrentX()-TextStringWidth(str), GetCurrentY());  
            DrawTextString("|");  
            MovePen(GetCurrentX()-TextStringWidth("|"),GetCurrentY());  
            SetEraseMode(FALSE);  
            DrawTextString(str);  
        }  
        else{  
            MovePen(GetCurrentX()-TextStringWidth(str),GetCurrentY());  
            DrawTextString(str);  
        }  
    } 
		}
}  
void TimerEventProcess(int timerID) 
{
	double x, y;  
    bool erasemode;
	if(Text_Button)  
    switch (timerID) {  
        case TIMER_BLINK:  
        if (!isBlink) return;  
        erasemode = GetEraseMode();  
        x = GetCurrentX();  
        y = GetCurrentY();  
        SetEraseMode(isDisplay);  
        DrawTextString("|");  
        MovePen(x, y);  
        if(textlen-1!=location){  
            char str[2]={0,0};  
            str[0]=Text[location+1];  
            SetEraseMode(FALSE);  
            DrawTextString(str);  
            MovePen(x,y);  
        }  
        SetEraseMode(erasemode);  
    	isDisplay = !isDisplay;  
        break;  
        default:  
        	break;  
    }  		
	
}
