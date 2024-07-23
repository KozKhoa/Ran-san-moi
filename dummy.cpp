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


//GotoXY(0, screenInfo.dwSize.Y - 1);
//printf(STRING_VERSION);
//Notifi notifi;
//notifi.readyClock();
//cls();
//GotoXY(0, screenInfo.dwSize.Y - 1);
//printf(STRING_VERSION);
//createWall();
//createStatus();
//printSnake();
//bool restart_game = true;
//int4 action = -1;
//int4 event = -1;

//updateTime(9999);
//time_start = time(0);
//while (!checkGameOver()) {
//	if ((mode == MODE_CLASSIC) && (!updateTime(notifi.countDownClock(hard.limit_time, restart_game)))) {
//		action = endGame(TIME_UP);
//		allowed_for_continue = false;
//		break;
//	}
//	else if (mode == MODE_FREEDOM) {
//		updateTime(notifi.countClock(restart_game));
//	}
//	if (_kbhit() && (event = _getch()));
//	if (event == CODE_BACKSPACE) {
//		if (pauseTable() == GOTO_HOME_PAGE) {
//			action = GOTO_HOME_PAGE;
//			break;
//		}
//		printSnake();
//		GotoXY(food.x, food.y);
//		printf("%c", CHAR_FOOD);
//	}
//	changeDirection(event);
//	moveSnack();
//	checkEatFood();
//	speedGame();
//}

//if (action == -1) { // tức là thoát vì game over chứ không phải hết giờ
//	action = endGame(STRING_GAME_OVER);
//	allowed_for_continue = false;
//}
//deleteWall();
//return action;


/*cls();
		int move = action.top();
		if (move == GOTO_HOME_PAGE) {
			cls();
			action.push(snake.homePage());
			continue;
		}
		if (move == GOTO_DIFFICULTY_PAGE) {
			cls();
			action.push(snake.difficultyPage());
			continue;
		}
		if (move == GOTO_GAMEPLAY_PAGE) {
			cls();
			action.push(snake.gamePlayPage());
			if (action.top() != GOTO_CONTINUE_GAME) {
				snake.resetSnakeData();
				data_file.updateToData(snake.hard.difficulty, snake.mode, snake.point, snake.hard.speed, snake.length, snake.time_use, snake.time_start);
				data_file.writeDataToFile();
			}
			continue;
		}
		if (move == GOTO_CONTINUE_GAME) {
			cls();
			if (snake.checkGameOver()) {
				notifi.printNoDataFound();
				contine;
			}
			action.push(snake.gamePlayPage());
			continue;
		}
		if (move == GOTO_HISTORY_PAGE) {
			cls();
			action.push(snake.historyPage(data_file));
			continue;
		}
		if (move == GOTO_EXIT) {
			cls();
			break;
		}*/
