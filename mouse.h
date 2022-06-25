#include <windows.h> //头文件
void gotoxy(int x,int y)
{
	COORD coord;//设置鼠标位置
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
