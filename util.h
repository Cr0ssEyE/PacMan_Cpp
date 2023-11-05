#pragma once

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15

#define ENTER 13
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

struct point
{
	int x;
	int y;
};

wchar_t* CharToWChar(const char* pstrSrc);
char* ConvertWCtoC(const wchar_t* str);

void gotoxy(int x, int y);

void ScreenInit();
void ScreenFlipping();
void ScreenClear(int width=120, int height=80);
void ScreenRelease();
//void ScreenPrint( int x, int y, const char* string );
void ScreenPrint(int x, int y, const wchar_t* string);
void SetColor(unsigned short color);
