#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <corecrt_wstring.h> // Khai báo để dùng wcslen();
#include <iomanip>
#include <conio.h>
#include <vector>
#include "console.h"
#include "snake.h"

#define FILE_NAME L"input.txt"

using int2 = int16_t;
using int4 = int32_t;



int4 maidn() {
	Snake snake;

	wchar_t file_name[] = FILE_NAME_DATA_FOR_HISTORY_FILE;
	HANDLE hfile = CreateFileW(file_name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);


	return 0;
}




