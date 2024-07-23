#include "console.h"

void GotoXY(short x, short y) {
	COORD point = { x, y };
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hstdout, point);
}

void showPointer(bool action) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO mouseInfo;
	mouseInfo.dwSize = 1; // 1 này hình như là độ rộng của con trỏ
	mouseInfo.bVisible = action;

	SetConsoleCursorInfo(hstdout, &mouseInfo);
}

void cls() { // xóa màn hình mà ko thay đổi vị trí hiện tại của con trỏ buffer
	HANDLE handleSTDout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	COORD start = { 0,0 };
	GetConsoleScreenBufferInfo(handleSTDout, &consoleInfo);
	DWORD dummy;
	FillConsoleOutputCharacter(handleSTDout, ' ', consoleInfo.dwSize.X * consoleInfo.dwSize.Y, start, &dummy);	
}

void clrscr(COORD start, COORD end) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

}

void setColor(int backgroundColor, int textColor) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD attribute = backgroundColor * 16 + textColor;
	SetConsoleTextAttribute(hstdout, attribute);
}

void SetScreenBufferSize(int width, int height) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD new_console = { width, height };
	SetConsoleScreenBufferSize(hstdout, new_console);
}
 
void setConsoleSize(int width, int height) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT windowSize;
	windowSize.Top = windowSize.Left = 0;
	windowSize.Bottom = height;
	windowSize.Right = width;
	SetConsoleWindowInfo(hstdout, 1, &windowSize);
}

void setWindowBufferSize(int height, int width) {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD window_buffer_size = { width, height };
	SetConsoleScreenBufferSize(hstdout, window_buffer_size);
}