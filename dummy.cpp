//SetCursorPos()

/*_setmode(_fileno(stdout), _O_U16TEXT);
GotoXY(Distance_from_left, cursor_pos.y);
std::wcout << L"MODE : ";
if (data.mode == MODE_CLASSIC) {
	std::wcout << L"CỔ ĐIỂN";
}
else if (data.mode == MODE_FREEDOM) {
	std::wcout << L"TỰ DO";
}

GotoXY(Distace_in_middle, cursor_pos.y);
std::wcout << "DIFFICULTY : ";
if (data.difficulty == EASY_CHOICE) {
	std::wcout << L"EASY";
}
else if (data.difficulty == MEDIUM_CHOICE) {
	std::wcout << L"MEDIUM";
}
else if (data.difficulty == HARD_CHOICE) {
	std::wcout << L"HARD";
}
GotoXY(Distance_from_right, cursor_pos.y);
std::wcout << L"POINT: " << data.point;
std::wcout << '\n';

GotoXY(Distance_from_left, cursor_pos.y + 1);
std::wcout << L"SPEED: " << data.speed;

GotoXY(Distace_in_middle, cursor_pos.y + 1);
std::wcout << L"LENGTH: " << data.length;

GotoXY(Distance_from_right, cursor_pos.y + 1);
if (data.mode == MODE_CLASSIC) {
	std::wcout << L"TIME LEFT: ";
	if (data.difficulty == EASY_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_EASY;
	}
	else if (data.difficulty == MEDIUM_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_MEDIUM;
	}
	else if (data.difficulty == HARD_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_HARD;
	}
}
else if (data.mode == MODE_FREEDOM) {
	std::wcout << L"TIME USE: " << data.time_finish;
}
_setmode(_fileno(stdout), _O_TEXT);


delete[] time_start;*/

/*int4 Distance_from_top = distance_from_the_previous;
int4 Distance_from_left = 5;
int4 Distance_from_right = screenInfo.dwSize.X - 20;
int4 Distace_in_middle = screenInfo.dwSize.X / 2 - 10;

char* time_start = new char[30];
ctime_s(time_start, 30, &data.time_start);
GotoXY(screenInfo.dwSize.X / 2 - strlen(time_start) / 2, Distance_from_top);
printf("%s", time_start);
delete[] time_start;

_setmode(_fileno(stdout), _O_U16TEXT);
GotoXY(Distance_from_left, Distance_from_top + 2);
std::wcout << L"MODE : ";
if (data.mode == MODE_CLASSIC) {
	std::wcout << L"CỔ ĐIỂN";
}
else if (data.mode == MODE_FREEDOM) {
	std::wcout << L"TỰ DO";
}

GotoXY(Distace_in_middle, Distance_from_top + 2);
std::wcout << "DIFFICULTY : ";
if (data.difficulty == EASY_CHOICE) {
	std::wcout << L"EASY";
}
else if (data.difficulty == MEDIUM_CHOICE) {
	std::wcout << L"MEDIUM";
}
else if (data.difficulty == HARD_CHOICE) {
	std::wcout << L"HARD";
}

GotoXY(Distance_from_right, Distance_from_top + 2);
std::wcout << L"POINT: " << data.point;

GotoXY(Distance_from_left, Distance_from_top + 4);
std::wcout << L"SPEED: " << data.speed;

GotoXY(Distace_in_middle, Distance_from_top + 4);
std::wcout << L"LENGTH: " << data.length;

GotoXY(Distance_from_right, Distance_from_top + 4);
if (data.mode == MODE_CLASSIC) {
	std::wcout << L"TIME LEFT: ";
	if (data.difficulty == EASY_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_EASY;
	}
	else if (data.difficulty == MEDIUM_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_MEDIUM;
	}
	else if (data.difficulty == HARD_CHOICE) {
		std::wcout << data.time_finish << " / " << LIMIT_TIME_HARD;
	}
}
else if (data.mode == MODE_FREEDOM) {
	std::wcout << L"TIME USE: " << data.time_finish;
}
_setmode(_fileno(stdout), _O_TEXT);*/