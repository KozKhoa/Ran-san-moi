#include "notification.h"

Notifi::Notifi() {
	number = new char* [8];
	for (int i = 0; i < 8; i++) {
		number[i] = new char[4];
	}

	c = new char* [5];
	for (int i = 0; i < 5; i++) {
		c[i] = new char[5];
	}
}

Notifi::~Notifi() {
	for (int i = 0; i < 8; i++) {
		delete[] number[i];
	}
	delete[] number;

	for (int i = 0; i < 5; i++) {
		delete[] c[i];
	}
	delete[] c;
}

void Notifi::print_number() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 8; i++) {
			GotoXY(j + screenInfo.dwCursorPosition.X, i + screenInfo.dwCursorPosition.Y);
			printf("%c", number[i][j]);
		}
	}
}

void Notifi::print_character() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			GotoXY(j + screenInfo.dwCursorPosition.X, i + screenInfo.dwCursorPosition.Y);
			printf("%c", c[i][j]);
		}
	}
}

void Notifi::reset_number() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 4; j++) {
			number[i][j] = ' ';
		}
	}
}

void Notifi::numberOne() {
	reset_number();
	number[3][0] = number[2][1] = number[1][2] = number[0][3] = POINT_NUMBER;
	for (int i = 0; i < 8; i++) {
		number[i][3] = POINT_NUMBER;
	}
}

void Notifi::numberTwo() {
	reset_number();
	number[2][0] = number[1][0] = number[0][1] = number[0][2] = number[1][3] = number[2][3]
		= number[3][3] = number[4][2] = number[5][1] = number[6][0] = POINT_NUMBER;
	for (int i = 0; i < 4; i++) {
		number[7][i] = POINT_NUMBER;
	}
}

void Notifi::numberThree() {
	reset_number();
	for (int i = 0; i < 4; i++) {
		number[0][i] = POINT_NUMBER;
	}
	number[1][3] = number[2][2] = number[3][1] = number[4][1] = number[4][2] = number[5][3]
		= number[6][3] = number[7][1] = number[7][2] = number[6][0] = POINT_NUMBER;
}

void Notifi::readyClock() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	setColor(BLACK, LIGTH_AQUA);

	GotoXY(screenInfo.dwSize.X / 2 - 2, screenInfo.dwSize.Y / 2 - 4);
	numberThree();
	print_number();
	Sleep(WAIT_COUNT_DOWN);

	GotoXY(screenInfo.dwSize.X / 2 - 2, screenInfo.dwSize.Y / 2 - 4);
	numberTwo();
	print_number();
	Sleep(WAIT_COUNT_DOWN);

	GotoXY(screenInfo.dwSize.X / 2 - 2, screenInfo.dwSize.Y / 2 - 4);
	numberOne();
	print_number();
	Sleep(WAIT_COUNT_DOWN);

	setColor(BLACK, WHITE);
}

int4 Notifi::countClock(bool& reset) {
	static time_t tgian_goc = time(0);
	static int4 current_sec = 0;

	if (reset == true) {
		tgian_goc = time(0);
		current_sec = 0;
		reset = false;
	}
	time_t tgian = time(0);
	if (tgian - tgian_goc > 0) {
		tgian_goc = tgian;
		current_sec = current_sec + 1;
	}
	return current_sec;

	//if (sec == -1) {
	//	return 999999999;
	//}
	//static time_t tgian_goc = time(0);
	//if (reset == true) {
	//	tgian_goc = time(0);
	//	reset = false;
	//}
	//time_t tgian = time(0);
	//return (sec - (tgian - tgian_goc) % (sec + 1));
}
//
//int Notifi::countClock(bool& reset_time) {
//	static time_t t = time(0);
//	if (reset_time == true) {
//		reset_time = false;
//		t = time(0);
//	}
//	return time(0) - t;
//
//}

void Notifi::reset_character() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			c[i][j] = ' ';
		}
	}
}

void Notifi::character_A() {
	reset_character();
	c[0][2] = c[1][1] = c[1][3] = c[2][1] = c[2][3] = c[3][0] = c[3][4] = c[4][0] = c[4][4] = POINT_CHARACTER;
	c[2][2] = char(254);
}

void Notifi::character_C() {
	reset_character();
	for (int i = 1; i < CHAR_WIDTH - 1; i++) {
		c[i][4] = c[4][i] = c[0][i] = c[i][0] = POINT_CHARACTER;
	}
	c[2][4] = ' ';
}

void Notifi::character_D() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		c[i][4] = c[4][i] = c[0][i] = c[i][0] = POINT_CHARACTER;
	}
	c[0][4] = c[4][4] = ' ';
}

void Notifi::character_E() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][0] = c[0][i] = c[4][i] = c[2][i] = POINT_CHARACTER;
	}
}

void Notifi::character_F() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][0] = c[0][i] = c[2][i] = POINT_CHARACTER;
	}
}

void Notifi::character_I() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][2] = POINT_CHARACTER;
	}
	c[0][1] = c[0][3] = char(223);
	c[4][1] = c[4][3] = char(220);
}

void Notifi::character_K() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		c[i][0] = POINT_CHARACTER;
	}
	for (int i = 0; i < CHAR_HEIGHT - 2; i++) {
		c[2 - i][i + 1] = c[i + 2][i + 1] = POINT_CHARACTER;
	}
}

void Notifi::character_L() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][0] = POINT_CHARACTER;
		c[4][i] = char(220);
	}
}

void Notifi::character_N() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		c[i][0] = c[i][4] = POINT_CHARACTER;
	}
	for (int i = 1; i < CHAR_HEIGHT - 1; i++) {
		c[i][i] = POINT_CHARACTER;
	}
}

void Notifi::character_S() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH - 1; i++) {
		c[0][i + 1] = c[4][i] = POINT_CHARACTER;
	}
	c[1][0] = c[2][1] = c[2][2] = c[2][3] = c[3][4] = POINT_CHARACTER;
}

void Notifi::character_T() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][2] = POINT_CHARACTER;
	}
	c[0][1] = c[0][3] = c[0][0] = c[0][4] = char(223);
}

void Notifi::character_U() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH; i++) {
		c[i][4] = c[4][i] = c[i][0] = POINT_CHARACTER;
	}
	c[4][0] = c[4][4] = ' ';
}

void Notifi::character_Y() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH - 2; i++) {
		c[i][i] = c[i][4 - i] = c[i + 2][2] = POINT_CHARACTER;
	}
}


void Notifi::character_a() {
	reset_character();
	for (int i = 1; i < CHAR_HEIGHT - 1; i++) {
		c[i][0] = c[0][i] = POINT_CHARACTER;
	}
	for (int i = 0; i < CHAR_HEIGHT - 1; i++) {
		c[i][4] = c[4][i + 1] = POINT_CHARACTER;
	}
	c[0][3] = ' ';
	c[1][3] = POINT_CHARACTER;
}

void Notifi::character_e() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i += 2) {
		c[i][1] = c[i][2] = c[i][3] = POINT_CHARACTER;
	}
	c[0][4] = ' ';
	c[1][0] = c[3][0] = c[1][4] = c[2][0] = POINT_CHARACTER;
}

void Notifi::character_k() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		c[i][0] = POINT_CHARACTER;
	}
	for (int i = 0; i < CHAR_HEIGHT - 2; i++) {
		c[2 - i][i + 1] = c[i + 2][i + 1] = POINT_CHARACTER;
	}
}

void Notifi::character_n() {
	reset_character();
	for (int i = 0; i < CHAR_HEIGHT; i++) {
		c[i][0] = c[i][4] = POINT_CHARACTER;
	}
	c[0][4] = ' ';
	c[0][1] = c[0][2] = c[0][3] = POINT_CHARACTER;
}

void Notifi::character_s() {
	reset_character();
	for (int i = 0; i < CHAR_WIDTH - 1; i++) {
		c[0][i + 1] = c[4][i] = POINT_CHARACTER;
	}
	c[1][0] = c[2][1] = c[2][2] = c[2][3] = c[3][4] = POINT_CHARACTER;
}

void Notifi::notificationTable(COORD pos_top_left, COORD pos_bottom_right) {
	for (int x = pos_top_left.X + 1; x < pos_bottom_right.X; x++) {
		for (int y = pos_top_left.Y + 1; y < pos_bottom_right.Y; y++) {
			GotoXY(x, y);
			printf(" ");
		}
	}

	GotoXY(pos_top_left.X, pos_top_left.Y);
	printf("%c", KHUNG_TOP_LEFT);
	std::cout << std::setfill(KHUNG_TOP) << std::setw(pos_bottom_right.X - pos_top_left.X) << KHUNG_TOP_RIGHT;

	GotoXY(pos_top_left.X, pos_bottom_right.Y);
	printf("%c", KHUNG_BOTTOM_LEFT);
	std::cout << std::setw(pos_bottom_right.X - pos_top_left.X) << KHUNG_BOTTOM_RIGHT;

	for (int i = pos_top_left.Y + 1; i < pos_bottom_right.Y; i++) {
		GotoXY(pos_top_left.X, i);
		printf("%c", KHUNG_LEFT);

		GotoXY(pos_bottom_right.X, i);
		printf("%c", KHUNG_LEFT);
	}
}

void Notifi::deleteNotificatinoTable(COORD pos_top_left, COORD pos_bottom_right) {
	for (int x = pos_top_left.X; x <= pos_bottom_right.X; x++) {
		for (int y = pos_top_left.Y; y <= pos_bottom_right.Y; y++) {
			GotoXY(x, y);
			printf(" ");
		}
	}
}

void Notifi::printNoDataFound() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	COORD pos_top_left = { screenInfo.dwSize.X / 2 - 10, screenInfo.dwSize.Y / 2 - 2 };
	COORD pos_bottom_right = { screenInfo.dwSize.X / 2 + 10, screenInfo.dwSize.Y / 2 + 2 };
	notificationTable(pos_top_left, pos_bottom_right);
	GotoXY(screenInfo.dwSize.X / 2 - strlen("NO DATA FOUND") / 2, screenInfo.dwSize.Y / 2);
	printf("NO DATA FOUND");
	Sleep(500);
	deleteNotificatinoTable(pos_top_left, pos_bottom_right);
}

//void Notifi::notificationTable(const wchar_t* content, COORD pos_top_left, COORD pos_bottom_right) {
//	if (pos_top_left.X == -1) {
//		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
//		CONSOLE_SCREEN_BUFFER_INFO screenInfo;
//		GetConsoleScreenBufferInfo(hstdout, &screenInfo);
//		pos_top_left.X = screenInfo.dwSize.X / 2 - wcslen(content) / 2 - 5;
//		pos_top_left.Y = screenInfo.dwSize.Y / 2 - 2;
//		pos_bottom_right.X = screenInfo.dwSize.X / 2 + +wcslen(content) / 2 + 5;
//		pos_bottom_right.Y = screenInfo.dwSize.Y / 2 + 2;
//	}
//
//	createTableFor_notificationTable(pos_top_left, pos_bottom_right);
//
//	_setmode(_fileno(stdout), _O_U16TEXT);
//	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - wcslen(content) / 2,
//		pos_top_left.Y + (pos_bottom_right.Y - pos_top_left.Y) / 2);
//	wprintf(content);
//	_setmode(_fileno(stdout), _O_TEXT);
//	/*setColor(BLACK, BLACK);
//	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - wcslen(content) / 2,
//		pos_top_left.Y + (pos_bottom_right.Y - pos_top_left.Y) / 2);
//	wprintf(content);
//	setColor(BLACK, WHITE);
//	deleteTableFor_notificationTable(pos_top_left, pos_bottom_right);*/
//}



