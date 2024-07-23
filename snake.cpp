#include "snake.h"

int4 triTuyetDoi(int4 n) {
	if (n > 0) {
		return n;
	}
	else return -n;
}

Snake::Snake() {
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &screenInfo);

	mode = MODE_CLASSIC;

	head_direction = 'r';
	prev_head_direction = head_direction;

	setupWall();

	length = 5;
	snake.resize(length);
	for (int4 i = 0; i < length; i++) {
		snake[i] = { wall.top_left.x + i + 1, wall.top_right.y + 1 };
	}

	hard.difficulty = EASY_CHOICE;
	hard.limit_time = LIMIT_TIME_EASY;
	hard.plus_point = PLUS_POINT_EASY;
	hard.speed = SPEED_EASY;
	hard.minus_speed = MINUS_SPEED_EASY;

	time_start = time(0);
	time_left = 0;

	allowed_for_continue = false;
	exist_food = false;

	//existFood = false;
	point = 0;
}

Snake::~Snake() {
	length = 0;
	snake.resize(0);
}

int4 Snake::choice(int4 num_of_choice, COORD pos_of_first_choice, int4 distance_between_each_choice) {
	if (num_of_choice <= 0) {
		return -1;
	}
	int4* choice_y = new int4[num_of_choice];
	choice_y[0] = pos_of_first_choice.Y;
	for (int4 i = 1; i < num_of_choice; i++) {
		choice_y[i] = choice_y[i - 1] + distance_between_each_choice;
	}
	int4 code_keyboard = 0;
	int4 code = 0;

	int4 pos_of_pointer_char_left_X = pos_of_first_choice.X - 10;
	int4 pos_of_pointer_char_right_X = pos_of_first_choice.X + 10;

	GotoXY(pos_of_pointer_char_left_X, choice_y[code]);
	printf("%c", POINTER_CHAR_LEFT);
	GotoXY(pos_of_pointer_char_right_X, choice_y[code]);
	printf("%c", POINTER_CHAR_RIGHT);

	while (true) {
		if (_kbhit()) {
			code_keyboard = _getch();
			int4 old_code = code;
			if (code_keyboard == CODE_UP_ARROW || code_keyboard == 'w' || code_keyboard == 'W') {
				code--;
			}
			else if (code_keyboard == CODE_DOWN_ARROW || code_keyboard == 's' || code_keyboard == 'S') {
				code++;
			}
			else if (code_keyboard == CODE_ENTER) {
				break;
			}

			if (code < 0) {
				code = num_of_choice - 1;
			}
			else if (code >= num_of_choice) {
				code = 0;
			}
			GotoXY(pos_of_pointer_char_left_X, choice_y[old_code]);
			printf(" ");
			GotoXY(pos_of_pointer_char_right_X, choice_y[old_code]);
			printf(" ");

			GotoXY(pos_of_pointer_char_left_X, choice_y[code]);
			printf("%c", POINTER_CHAR_LEFT);
			GotoXY(pos_of_pointer_char_right_X, choice_y[code]);
			printf("%c", POINTER_CHAR_RIGHT);
		}
	}
	delete[] choice_y;

	return code + 1; // trả về thứ tự của lựa chọn đã chọn
}

void Snake::setupWall() {
	wall.top_left.x = screenInfo.dwSize.X / TI_LE_TUONG_CHIEU_DAI;
	wall.top_left.y = screenInfo.dwSize.Y / TI_LE_TUONG_CHIEU_CAO + 2;

	wall.top_right.x = screenInfo.dwSize.X * (TI_LE_TUONG_CHIEU_DAI - 1) / TI_LE_TUONG_CHIEU_DAI;
	wall.top_right.y = screenInfo.dwSize.Y / TI_LE_TUONG_CHIEU_CAO + 2;

	wall.bottom_left.x = screenInfo.dwSize.X / TI_LE_TUONG_CHIEU_DAI;
	wall.bottom_left.y = screenInfo.dwSize.Y * (TI_LE_TUONG_CHIEU_CAO - 1) / TI_LE_TUONG_CHIEU_CAO + 2;

	wall.bottom_right.x = screenInfo.dwSize.X * (TI_LE_TUONG_CHIEU_DAI - 1) / TI_LE_TUONG_CHIEU_DAI;
	wall.bottom_right.y = screenInfo.dwSize.Y * (TI_LE_TUONG_CHIEU_CAO - 1) / TI_LE_TUONG_CHIEU_CAO + 2;

}

void Snake::printSnake() {
	for (int4 i = length - 1; i >= 0; i--) {
		GotoXY(snake[i].x, snake[i].y);
		printf("%c", HINH_DOT_RAN);
	}
}

void Snake::inDauRan() {
	GotoXY(snake[length - 1].x, snake[length - 1].y);
	if (head_direction == 'd') {
		printf("%c", HINH_DAU_RAN_XUONG);
	}
	else if (head_direction == 'u') {
		printf("%c", HINH_DAU_RAN_LEN);
	}
	else {
		printf("%c", HINH_DAU_RAN);
	}
}

void Snake::inDuoiRan() {
	GotoXY(snake[0].x, snake[0].y);
	printf("%c", HINH_DUOI_RAN);
}

void Snake::inCoRan() {
	GotoXY(snake[length - 2].x, snake[length - 2].y);
	if (prev_head_direction == head_direction) {
		if (head_direction == 'u' || head_direction == 'd') {
			printf("%c", HINH_DOT_RAN_DOC);
		}
		else {
			printf("%c", HINH_DOT_RAN);;
		}
	}
	else {
		if ((prev_head_direction == 'r' && head_direction == 'd') || (prev_head_direction == 'u' && head_direction == 'l')) {
			printf("%c", TURN_LEFT_DOWN);
		}
		else if ((prev_head_direction == 'r' && head_direction == 'u') || (prev_head_direction == 'd' && head_direction == 'l')) {
			printf("%c", TURN_LEFT_UP);
		}
		else if ((prev_head_direction == 'l' && head_direction == 'd') || (prev_head_direction == 'u' && head_direction == 'r')) {
			printf("%c", TURN_RIGHT_DOWN);
		}
		else if ((prev_head_direction == 'l' && head_direction == 'u') || (prev_head_direction == 'd' && head_direction == 'r')) {
			printf("%c", TURN_RIGHT_UP);
		}
		prev_head_direction = head_direction;
	}
}

void Snake::speedGame() {
	if (head_direction == 'u' || head_direction == 'd') {
		Sleep(hard.speed * 3 / 2 - bonus_speed);
	}
	else {
		Sleep(hard.speed - bonus_speed);
	}
}

void Snake::moveSnack() {
	// Xóa đuôi rắn cũ và cập nhật rắn
	GotoXY(snake[0].x, snake[0].y);
	printf(" ");
	for (int4 i = 0; i < length - 1; i++) {
		snake[i] = snake[i + 1];
	}
	//
	inDuoiRan();
	inCoRan();
	if (head_direction == 'u') {
		snake[length - 1].y = snake[length - 1].y - 1;
	}
	else if (head_direction == 'd') {
		snake[length - 1].y = snake[length - 1].y + 1;
	}
	else if (head_direction == 'r') {
		snake[length - 1].x = snake[length - 1].x + 1;
	}
	else if (head_direction == 'l') {
		snake[length - 1].x = snake[length - 1].x - 1;
	}
	inDauRan();
}

void Snake::changeDirection(int4 event) {
	if (head_direction != 'd' && (event == CODE_UP_ARROW || event == 'w' || event == 'W')) {
		head_direction = 'u';
		bonus_speed = 0;
	}
	else if (head_direction != 'u' && (event == CODE_DOWN_ARROW || event == 's' || event == 'S')) {
		head_direction = 'd';
		bonus_speed = 0;
	}
	else if (head_direction != 'l' && (event == CODE_RIGHT_ARROW || event == 'd' || event == 'D')) {
		head_direction = 'r';
		bonus_speed = 0;
	}
	else if (head_direction != 'r' && (event == CODE_LEFT_ARROW || event == 'a' || event == 'A')) {
		head_direction = 'l';
		bonus_speed = 0;
	}
}

void Snake::createWall() {
	setColor(GRAY, WHITE);
	GotoXY(wall.top_left.x, wall.top_left.y);
	std::cout << WALL_TOP_LEFT;
	std::cout << std::setfill(WALL_TOP) << std::setw(wall.top_right.x - wall.top_left.x);
	std::cout << WALL_TOP_RIGHT;

	GotoXY(wall.bottom_left.x, wall.bottom_left.y);
	std::cout << WALL_BOTTOM_LEFT;
	std::cout << std::setw(wall.top_right.x - wall.top_left.x);
	std::cout << WALL_BOTTOM_RIGHT;

	GotoXY(wall.top_left.x, wall.top_left.y + 1);
	for (int4 i = 0; i < wall.bottom_left.y - wall.top_left.y; i++) {
		std::cout << WALL_LEFT;
		GotoXY(wall.top_left.x, wall.top_left.y + i + 1);
	}

	GotoXY(wall.top_right.x, wall.top_right.y + 1);
	for (int4 i = 0; i < wall.bottom_left.y - wall.top_left.y; i++) {
		std::cout << WALL_LEFT;
		GotoXY(wall.top_right.x, wall.top_right.y + i + 1);
	}

	setColor(BLACK, WHITE);
}

void Snake::deleteWall() {
	setColor(BLACK, BLACK);
	GotoXY(wall.top_left.x, wall.top_left.y);
	std::cout << WALL_TOP_LEFT;
	std::cout << std::setfill(WALL_TOP) << std::setw(wall.top_right.x - wall.top_left.x);
	std::cout << WALL_TOP_RIGHT;

	GotoXY(wall.bottom_left.x, wall.bottom_left.y);
	std::cout << WALL_BOTTOM_LEFT;
	std::cout << std::setw(wall.top_right.x - wall.top_left.x);
	std::cout << WALL_BOTTOM_RIGHT;

	GotoXY(wall.top_left.x, wall.top_left.y + 1);
	for (int4 i = 0; i < wall.bottom_left.y - wall.top_left.y; i++) {
		std::cout << WALL_LEFT;
		GotoXY(wall.top_left.x, wall.top_left.y + i + 1);
	}

	GotoXY(wall.top_right.x, wall.top_right.y + 1);
	for (int4 i = 0; i < wall.bottom_left.y - wall.top_left.y; i++) {
		std::cout << WALL_LEFT;
		GotoXY(wall.top_right.x, wall.top_right.y + i + 1);
	}
	setColor(BLACK, WHITE);
}

int4 Snake::checkGameOver() {
	if (snake[length - 1].x == wall.top_left.x || snake[length - 1].x == wall.bottom_right.x
		|| snake[length - 1].y == wall.top_left.y || snake[length - 1].y == wall.bottom_right.y) {
		return LOSE_BY_WALL;
	}
	for (int4 i = 0; i < length - 4; i++) {
		// do đầu rắn ko thể ăn tới đốt thứ hai, tức là cổ, tương tự đối với đốt thứ 3 và thứ 4 nên chỉ cần xét tới đốt thứ 5 là đc
		if (snake[length - 1].x == snake[i].x && snake[length - 1].y == snake[i].y) {
			return LOSE_BY_EAT_ITSELF;
		}
	}
	return NOT_LOSE;
}

void Snake::createTableFor_endGame(COORD pos_top_left, COORD pos_bottom_right) {
	for (int4 x = pos_top_left.X + 1; x < pos_bottom_right.X; x++) {
		for (int4 y = pos_top_left.Y + 1; y < pos_bottom_right.Y; y++) {
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

	for (int4 i = pos_top_left.Y + 1; i < pos_bottom_right.Y; i++) {
		GotoXY(pos_top_left.X, i);
		printf("%c", KHUNG_LEFT);

		GotoXY(pos_bottom_right.X, i);
		printf("%c", KHUNG_LEFT);
	}
}

int4 Snake::endGame(const wchar_t* content) {
	COORD pos_top_left = { wall.top_left.x + 20, wall.top_left.y + 3 };
	COORD pos_bottom_right = { wall.bottom_right.x - 20, wall.bottom_right.y - 3 };

	createTableFor_endGame(pos_top_left, pos_bottom_right);

#define DISTANCE_FROM_TOP_OF_TABLE pos_top_left.Y + 3
#define DISTANCE_FROM_TIME_UP_NOTIFY 3
	_setmode(_fileno(stdout), _O_U16TEXT);
	setColor(BLACK, WHITE);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - wcslen(content) / 2, DISTANCE_FROM_TOP_OF_TABLE);
	wprintf(content);
	_setmode(_fileno(stdout), _O_TEXT);

	setColor(BLACK, GREEN);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(PLAY_AGAIN) / 2, DISTANCE_FROM_TOP_OF_TABLE + 3);
	printf(PLAY_AGAIN);

	setColor(BLACK, YELLOW);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(HOME) / 2, DISTANCE_FROM_TOP_OF_TABLE + 6);
	printf(HOME);

	setColor(BLACK, RED);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(EXIT) / 2, DISTANCE_FROM_TOP_OF_TABLE + 9);
	printf(EXIT);

	setColor(BLACK, WHITE);
	COORD pos_of_first_choice = { screenInfo.dwSize.X / 2, DISTANCE_FROM_TOP_OF_TABLE + 3 };
	int4 code = choice(3, pos_of_first_choice, 3);

	if (code == 1) { // Play again
		return GOTO_GAMEPLAY_PAGE;
	}
	if (code == 2) {
		return GOTO_HOME_PAGE;
	}
	if (code == 3) {
		return GOTO_EXIT;
	}
	return -1;
}

void Snake::resetSnakeData() {
	head_direction = 'r';
	prev_head_direction = head_direction;

	if (hard.difficulty == EASY_CHOICE) {
		hard.speed = SPEED_EASY;
	}
	else if (hard.difficulty == MEDIUM_CHOICE) {
		hard.speed = SPEED_MEDIUM;
	}
	else if (hard.difficulty == HARD_CHOICE) {
		hard.speed = SPEED_HARD;
	}

	allowed_for_continue = false;

	time_start = time(0);
	time_left = 0;

	length = 5;
	snake.resize(length);
	for (int4 i = 0; i < length; i++) {
		snake[i] = { wall.top_left.x + i + 1, wall.top_right.y + 1 };
	}
	//existFood = false;
	point = 0;
}

bool Snake::checkEatFood() {
	if ((snake[length - 1].x == food.x && snake[length - 1].y == food.y) || (exist_food == false)) {
		return true;
	}
	return false;
}

void Snake::randomFood() {
	srand(time(0));
	int4 randomNum = rand();
	randomNum = triTuyetDoi((randomNum * randomNum * 100 / 9 * snake[1].x) / head_direction);

	food.x = wall.top_left.x + 1 + rand() % (wall.top_right.x - wall.top_left.x - 1);
	food.y = wall.top_left.y + 1 + rand() % (wall.bottom_left.y - wall.top_left.y - 1);
	for (int4 i = length - 1; i >= 0; i--) {
		if (food.x == snake[i].x && food.y == snake[i].y) {
			/*food.x = snake[0].x;
			food.y = snake[0].y;*/
			return;
		}
	}
	GotoXY(food.x, food.y);
	std::cout << '*';
	GotoXY(wall.top_left.x + (wall.top_right.x - wall.top_left.x) / 2 + strlen(FOOD_POS) / 2 - 1,
		wall.top_left.y - DISTANCE_FROM_TOP_WALL);
	printf("%d - %d      ", food.x, food.y);
}

void Snake::themDotRan() {
	snake.push_back(snake[length - 1]);
	length++;
}

bool Snake::updateTime(int4 sec) {
	GotoXY(wall.top_left.x + (wall.top_right.x - wall.top_left.x) / 2 + strlen(COUNT_DOWN) / 2,
		wall.top_left.y - DISTANCE_FROM_TOP_WALL - 1);
	printf("%d    ", sec);
	time_use = sec;
	if (sec <= 0) {
		return false;
	}
	return true;
}

void Snake::createStatus() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	GotoXY(screenInfo.dwSize.X / 2 - 6, 1);
	wprintf(L"GAME RẮN SĂN MỒI");

	GotoXY(wall.top_left.x, wall.top_left.y - DISTANCE_FROM_TOP_WALL);
	wprintf(L"POINT : "); wprintf(L"%d", point);

	GotoXY(wall.top_right.x - POS_STATUC_RIGHT, wall.top_right.y - DISTANCE_FROM_TOP_WALL);
	wprintf(L"CHIỀU DÀI RẮN : "); wprintf(L"%d", length);

	GotoXY(wall.top_right.x - POS_STATUC_RIGHT, wall.top_right.y - DISTANCE_FROM_TOP_WALL - 1);
	if (mode == MODE_CLASSIC) {
		wprintf(L"CHẾ ĐỘ : CỔ ĐIỂN");
	}
	else if (mode == MODE_FREEDOM) {
		wprintf(L"CHẾ ĐỘ : TỰ DO");
	}

	GotoXY(wall.top_left.x, wall.top_left.y - DISTANCE_FROM_TOP_WALL - 1);
	wprintf(L"SPEED : "); wprintf(L"%d", hard.speed);

	GotoXY(wall.top_left.x + (wall.top_right.x - wall.top_left.x) / 2 - strlen(COUNT_DOWN) / 2,
		wall.top_left.y - DISTANCE_FROM_TOP_WALL - 1);
	wprintf(L"THỜI GIAN CÒN LẠI : ");

	GotoXY(wall.top_left.x + (wall.top_right.x - wall.top_left.x) / 2 - strlen(COUNT_DOWN) / 2,
		wall.top_left.y - DISTANCE_FROM_TOP_WALL);
	wprintf(L"VỊ TRÍ THỨC ĂN : ");

	_setmode(_fileno(stdout), _O_TEXT);

	GotoXY(wall.top_left.x + (wall.top_right.x - wall.top_left.x) / 2 + strlen(FOOD_POS) / 2 - 1,
		wall.top_left.y - DISTANCE_FROM_TOP_WALL);
	printf("%d - %d      ", food.x, food.y);
}

void Snake::updateStatus() {
	point += hard.plus_point;
	if (hard.speed > MINIMUM_SPEED) {
		hard.speed = hard.speed - hard.minus_speed;
	}

	std::cout << std::setfill(' ');
	GotoXY(wall.top_left.x + strlen(STRING_POINT), wall.top_left.y - DISTANCE_FROM_TOP_WALL);
	printf("%d    ", point);

	GotoXY(wall.top_right.x - POS_STATUC_RIGHT + strlen(LENGTH), wall.top_right.y - DISTANCE_FROM_TOP_WALL);
	printf("%d    ", length);

	GotoXY(wall.top_left.x + strlen(SPEED), wall.top_left.y - DISTANCE_FROM_TOP_WALL - 1);
	printf("%d    ", hard.speed);
}

void Snake::printDIFFICULTY_character(int4 distance_from_top, int4 distance_from_left) {
	setColor(BLACK, GRAY);
	Notifi notifi;
	int4 i = 0;
	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_D(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_I(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_F(); notifi.print_character();
	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_I(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_C(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_U(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6, distance_from_top);
	notifi.character_L(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6 - 1, distance_from_top);
	notifi.character_T(); notifi.print_character();

	GotoXY(distance_from_left + (i++) * 6 - 1, distance_from_top);
	notifi.character_Y(); notifi.print_character();

	setColor(BLACK, WHITE);
}

int4 Snake::difficultyPage() {
	GotoXY(0, screenInfo.dwSize.Y - 1);
	printf(STRING_VERSION);

	GotoXY(0, 0);
	printf("%c BACKSPACE", CHAR_BACK);

	printDIFFICULTY_character(DISTANCE_FROM_TOP_DIFFICULT_PAGE, DISTANCE_FROM_LEFT);

	_setmode(_fileno(stdout), _O_U16TEXT);
	GotoXY(screenInfo.dwSize.X / 2 - strlen(CHOOSE_DIFFICULTY) / 2, DISTANCE_FROM_DIFFICULTY + DISTANCE_FROM_TOP_DIFFICULT_PAGE + 5);
	std::wcout << L"HÃY CHỌN ĐỘ KHÓ";
	_setmode(_fileno(stdout), _O_TEXT);

	setColor(BLACK, GREEN);
	GotoXY(POS_OF_EASY_X, POS_OF_EASY_Y);
	printf(EASY);

	setColor(BLACK, YELLOW);
	GotoXY(POS_OF_MEDIUM_X, POS_OF_MEDIUM_Y);
	printf(MEDIUM);

	setColor(BLACK, RED);
	GotoXY(POS_OF_HARD_X, POS_OF_HARD_Y);
	printf(HARD);
	setColor(BLACK, WHITE);

	int4 code = chooseDifficulty();
	if (code == -1) {
		return GOTO_HOME_PAGE;
	}
	return GOTO_GAMEPLAY_PAGE;
}

int4 Snake::chooseDifficulty() {
	COORD pos_of_first_choice = { screenInfo.dwSize.X / 2, POS_OF_EASY_Y };
	//int4 code = choice(3, pos_of_first_choice, 3);
	int4 num_of_choice = 3;
	int4* choice_y = new int4[num_of_choice];
	choice_y[0] = pos_of_first_choice.Y;
	for (int4 i = 1; i < num_of_choice; i++) {
		choice_y[i] = choice_y[i - 1] + 3;
	}
	int4 code_keyboard = 0;
	int4 code = 0;

	int4 pos_of_pointer_char_left_X = pos_of_first_choice.X - 10;
	int4 pos_of_pointer_char_right_X = pos_of_first_choice.X + 10;

	GotoXY(pos_of_pointer_char_left_X, choice_y[code]);
	printf("%c", POINTER_CHAR_LEFT);
	GotoXY(pos_of_pointer_char_right_X, choice_y[code]);
	printf("%c", POINTER_CHAR_RIGHT);

	while (true) {
		if (_kbhit()) {
			code_keyboard = _getch();
			int4 old_code = code;
			if (code_keyboard == CODE_UP_ARROW || code_keyboard == 'w' || code_keyboard == 'W') {
				code--;
			}
			else if (code_keyboard == CODE_DOWN_ARROW || code_keyboard == 's' || code_keyboard == 'S') {
				code++;
			}
			else if (code_keyboard == CODE_ENTER) {
				break;
			}
			else if (code_keyboard == CODE_BACKSPACE) {
				code = -1;
				break;
			}

			if (code < 0) {
				code = num_of_choice - 1;
			}
			else if (code >= num_of_choice) {
				code = 0;
			}
			GotoXY(pos_of_pointer_char_left_X, choice_y[old_code]);
			printf(" ");
			GotoXY(pos_of_pointer_char_right_X, choice_y[old_code]);
			printf(" ");

			GotoXY(pos_of_pointer_char_left_X, choice_y[code]);
			printf("%c", POINTER_CHAR_LEFT);
			GotoXY(pos_of_pointer_char_right_X, choice_y[code]);
			printf("%c", POINTER_CHAR_RIGHT);
		}
	}
	delete[] choice_y;

	if (code == 0) {
		hard.difficulty = 'e';
		hard.limit_time = LIMIT_TIME_EASY;
		hard.plus_point = PLUS_POINT_EASY;
		hard.speed = SPEED_EASY;
		hard.minus_speed = MINUS_SPEED_EASY;
	}
	else if (code == 1) {
		hard.difficulty = 'm';
		hard.limit_time = LIMIT_TIME_MEDIUM;
		hard.plus_point = PLUS_POINT_MEDIUM;
		hard.speed = SPEED_MEDIUM;
		hard.minus_speed = MINUS_SPEED_MEDIUM;
	}
	else if (code == 2) {
		hard.difficulty = 'h';
		hard.limit_time = LIMIT_TIME_HARD;
		hard.plus_point = PLUS_POINT_HARD;
		hard.speed = SPEED_HARD;
		hard.minus_speed = MINUS_SPEED_HARD;
	}
	return code;
}

void Snake::printSNAKES_character(int4 distance_from_top, int4 distance_from_left) {
	Notifi notifi;

	int4 distance = 0;
	setColor(BLACK, LIGHT_RED);
	GotoXY(distance_from_left + (distance++) * 6, distance_from_top);
	notifi.character_S();
	notifi.print_character();

	setColor(BLACK, LIGHT_GREEN);
	GotoXY(distance_from_left + (distance++) * 6, distance_from_top);
	notifi.character_N();
	notifi.print_character();

	setColor(BLACK, LIGHT_BLUE);
	GotoXY(distance_from_left + (distance++) * 6, distance_from_top);
	notifi.character_A();
	notifi.print_character();

	setColor(BLACK, YELLOW);
	GotoXY(distance_from_left + (distance++) * 6, distance_from_top);
	notifi.character_K();
	notifi.print_character();

	setColor(BLACK, LIGHT_RED);
	GotoXY(distance_from_left + (distance++) * 6 - 1, distance_from_top);
	notifi.character_E();
	notifi.print_character();

	setColor(BLACK, LIGHT_GREEN);
	GotoXY(distance_from_left + (distance++) * 6 - 1, distance_from_top);
	notifi.character_S();
	notifi.print_character();

	setColor(BLACK, WHITE);
}

int4 Snake::chooseHome() {
	COORD pos_of_first_choice = { screenInfo.dwSize.X / 2 , DISTANCE_FROM_SNAKE_CHARATER };
	int4 code = choice(6, pos_of_first_choice, 3);
	return code;
}

void Snake::changeMode() {
	char STRING_CHANGE_MODE[] = " CHANGE MODE";
	wchar_t STRING_CLASSIC[] = L"CỔ ĐIỂN";
	wchar_t STRING_FREEDOM[] = L"TỰ DO";

	COORD pos_of_top_left_table = { screenInfo.dwSize.X / 2 - 20, screenInfo.dwSize.Y / 2 - 5 };
	COORD pos_of_bottom_right_table = { screenInfo.dwSize.X / 2 + 20, screenInfo.dwSize.Y / 2 + 5 };

	Notifi notifi;
	notifi.notificationTable(pos_of_top_left_table, pos_of_bottom_right_table);


	COORD POS_OF_MODE_CLASSIC = { screenInfo.dwSize.X / 2 - wcslen(STRING_CLASSIC) / 2, pos_of_top_left_table.Y + 5 };
	COORD POS_OF_MODE_FREEDOM = { screenInfo.dwSize.X / 2 - wcslen(STRING_FREEDOM) / 2, POS_OF_MODE_CLASSIC.Y + 3 };

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_CHANGE_MODE) / 2, pos_of_top_left_table.Y + 2);
	std::cout << STRING_CHANGE_MODE;
	_setmode(_fileno(stdout), _O_U16TEXT);
	GotoXY(POS_OF_MODE_CLASSIC.X, POS_OF_MODE_CLASSIC.Y);
	std::wcout << STRING_CLASSIC;
	GotoXY(POS_OF_MODE_FREEDOM.X, POS_OF_MODE_FREEDOM.Y);
	std::wcout << STRING_FREEDOM;
	_setmode(_fileno(stdout), _O_TEXT);

	COORD pos_of_first_choice = { screenInfo.dwSize.X / 2, pos_of_top_left_table.Y + 5 };
	int4 code = choice(2, pos_of_first_choice, 3);
	if (code == 1) {
		mode = MODE_CLASSIC;
	}
	else if (code == 2) {
		mode = MODE_FREEDOM;
	}
	notifi.deleteNotificatinoTable(pos_of_top_left_table, pos_of_bottom_right_table);
}

int4 Snake::homePage() {
	GotoXY(0, screenInfo.dwSize.Y - 1);
	printf(STRING_VERSION);

	printSNAKES_character(DISTANCE_FROM_TOP_SNAKE_PAGE, screenInfo.dwSize.X / 2 - SNAKES_LENGTH / 2);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_MODE_GAME) / 2 - 3, DISTANCE_FROM_SNAKE_CHARATER);
	setColor(BLACK, WHITE);
	printf(STRING_MODE_GAME);
	_setmode(_fileno(stdout), _O_U16TEXT);
	if (mode == MODE_CLASSIC) {
		wprintf(L"CỔ ĐIỂN");
	}
	else if (mode == MODE_FREEDOM) {
		wprintf(L"TỰ DO");
	}
	_setmode(_fileno(stdout), _O_TEXT);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_NEW_GAME) / 2, DISTANCE_FROM_MODE_GAME_CHAR);
	setColor(BLACK, GREEN);
	printf(STRING_NEW_GAME);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_CONTINUE) / 2, DISTANCE_FROM_NEW_GAME);
	setColor(BLACK, YELLOW);
	printf(STRING_CONTINUE);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_HISTORY) / 2, DISTACNE_FROM_CONTINUE);
	setColor(BLACK, AQUA);
	printf(STRING_HISTORY);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(STRING_HISTORY) / 2, DISTANCE_FROM_HISTORY);
	setColor(BLACK, LIGHT_PURPLE);
	printf(STRING_OPTIONS);

	GotoXY(screenInfo.dwSize.X / 2 - strlen(EXIT) / 2, DISTANCE_FROM_OPTION);
	setColor(BLACK, RED);
	printf(EXIT);

	setColor(BLACK, WHITE);

	int4 action = chooseHome();
	if (action == 1) {
		changeMode();
		return homePage();
	}
	if (action == 2) {
		return GOTO_DIFFICULTY_PAGE;
	}
	if (action == 3) {
		return GOTO_CONTINUE_GAME;
	}
	if (action == 4) {
		return GOTO_HISTORY_PAGE;
	}
	if (action == 5) {
		return GOTO_OPTIONS_PAGE;
	}
	if (action == 6) {
		return GOTO_EXIT;
	}
	return -1;
}

int4 Snake::pauseGame() {
	Notifi notifi;
	int4 Distance_from_midle_x = 15;
	int4 Distance_from_midle_y = 5;
	COORD pos_top_left = { screenInfo.dwSize.X / 2 - Distance_from_midle_x, screenInfo.dwSize.Y / 2 - Distance_from_midle_y };
	COORD pos_bottom_right = { screenInfo.dwSize.X / 2 + Distance_from_midle_x, screenInfo.dwSize.Y / 2 + Distance_from_midle_y };
	notifi.notificationTable(pos_top_left, pos_bottom_right);

	COORD pos_of_first_choice = { pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2,
		pos_top_left.Y + 5 };

	setColor(BLACK, YELLOW);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(STRING_PAUSE_GAME) / 2, pos_top_left.Y + 2);
	printf(STRING_PAUSE_GAME);

	setColor(BLACK, RED);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(STRING_SAVE_AND_EXIT) / 2, pos_top_left.Y + 5);
	printf(STRING_SAVE_AND_EXIT);

	setColor(BLACK, GREEN);
	GotoXY(pos_top_left.X + (pos_bottom_right.X - pos_top_left.X) / 2 - strlen(STRING_CONTINUE) / 2, pos_top_left.Y + 8);
	printf(STRING_CONTINUE);

	setColor(BLACK, WHITE);

	int4 code = choice(2, pos_of_first_choice, 3);
	notifi.deleteNotificatinoTable(pos_top_left, pos_bottom_right);

	if (code == 1) {
		allowed_for_continue = true;
		return GOTO_HOME_PAGE;
	}
	else if (code == 2) {
		return GOTO_DO_NOT_THING;
	}
}

int4 Snake::gamePlayPage() {
	Notifi notifi;

	notifi.readyClock();
	cls();

	GotoXY(0, screenInfo.dwSize.Y - 1);
	printf(STRING_VERSION);
	GotoXY(0, 0);
	printf("%c BACKSPACE", CHAR_BACK);

	createWall();
	createStatus();

	if (exist_food == false) {
		randomFood();
		exist_food = true;
	}
	else {
		GotoXY(food.x, food.y);
		printf("%c", CHAR_FOOD);
	}

	int4 reason_for_lose = 0;
	bool reset_time = true;
	if (allowed_for_continue == false) {
		time_left = hard.limit_time;
	}
	printSnake();
	while ((reason_for_lose = checkGameOver()) && (reason_for_lose == NOT_LOSE)) {
		if (mode == MODE_CLASSIC) {
			if (updateTime(time_left - notifi.countClock(hard.limit_time, reset_time)) == 0) {
				reason_for_lose = LOSE_BY_TIME_UP;
				break;
			}
		}
		else if (mode == MODE_FREEDOM) {
			updateTime(notifi.countClock(hard.limit_time, reset_time) + time_left);
		}

		int4 event = -1;
		if (_kbhit()) {
			event = _getch();
		}
		if (event == CODE_BACKSPACE) {
			event = pauseGame();
			if (event == GOTO_HOME_PAGE) {
				break;
			}
			printSnake();
			GotoXY(food.x, food.y);
			printf("%c", CHAR_FOOD);
		}
		changeDirection(event);
		moveSnack();
		if (checkEatFood() == true) {
			themDotRan();
			updateStatus();
			randomFood();
			exist_food = true;
		}
		speedGame();
	}
	//reset_time = true;
	int4 action = 0;
	if (reason_for_lose == NOT_LOSE) {
		allowed_for_continue = true;
		action = GOTO_HOME_PAGE;
		time_left = time_use;
		// thoat ra la do update file chuan bi choi tiep
		//HANDLE hfile = CreateFileW(hfile, GENERIC_WRITE, 0, NULL, )
	}
	else if (reason_for_lose == LOSE_BY_WALL || reason_for_lose == LOSE_BY_EAT_ITSELF) {
		allowed_for_continue = false;
		action = endGame(STRING_GAME_OVER);
	}
	else if (reason_for_lose == LOSE_BY_TIME_UP) {
		allowed_for_continue = false;
		action = endGame(STRING_TIME_UP);
	}

	deleteWall();

	if (action == GOTO_GAMEPLAY_PAGE) {
		return GOTO_GAMEPLAY_PAGE;
	}
	if (action == GOTO_HOME_PAGE) {
		return GOTO_HOME_PAGE;
	}
	if (action == GOTO_EXIT) {
		return GOTO_EXIT;
	}
	return GOTO_HOME_PAGE;

	return 0;
}

void Snake::createTableOfInfomationFor_historyPage(Data_of_each_game& data, int distance_from_the_previous) {
	int4 Distance_from_top = distance_from_the_previous;
	short Distance_from_left = 5;
	short Distace_in_middle = screenInfo.dwSize.X / 2 - 10;
	short Distance_from_right = screenInfo.dwSize.X - 20;
	char* time_start = new char[30];
	ctime_s(time_start, 30, &data.time_start);

	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << std::setfill(' ');
	std::cout << std::setw(screenInfo.dwSize.X / 2 + strlen(time_start) / 2) << std::right << time_start << '\n';

	_setmode(_fileno(stdout), _O_U16TEXT);
	std::wcout << std::setw(3) << L" " << L"MODE: ";
	if (data.mode == MODE_CLASSIC) {
		std::wcout << L"CỔ ĐIỂN";
	}
	else if (data.mode == MODE_FREEDOM) {
		std::wcout << L"TỰ DO";
	}

	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	std::wcout << std::setw(screenInfo.dwSize.X / 2 - screenInfo.dwCursorPosition.X - 10) << L" " << L"DIFFICULTY: ";
	if (data.difficulty == EASY_CHOICE) {
		std::wcout << L"EASY";
	}
	else if (data.difficulty == MEDIUM_CHOICE) {
		std::wcout << L"MEDIUM";
	}
	else if (data.difficulty == HARD_CHOICE) {
		std::wcout << L"HARD";
	}

	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	std::wcout << std::setw(screenInfo.dwSize.X - screenInfo.dwCursorPosition.X - 20) << L" " << L"POINT: " << data.point;

	wprintf(L"\n\n");

	std::wcout << std::setw(3) << L" " << L"SPEED: " << data.speed;

	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	std::wcout << std::setw(screenInfo.dwSize.X / 2 - screenInfo.dwCursorPosition.X - 10) << L" " << L"LENGTH: " << data.length;

	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	std::wcout << std::setw(screenInfo.dwSize.X - screenInfo.dwCursorPosition.X - 20) << L" ";
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

	delete[] time_start;
}

int4 Snake::historyPage(File& file) {
	Notifi notifi;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	char NO_DATA_FOUND[] = "No data found";
	char Back_symbol = char(174);

	GotoXY(0, 0);
	printf("%c BACKSPACE\n", Back_symbol);

	if (file.num_of_data == 0) {
		COORD pos_top_left = { screenInfo.dwSize.X / 2 - 10, screenInfo.dwSize.Y / 2 - 2 };
		COORD pos_bottom_right = { screenInfo.dwSize.X / 2 + 10, screenInfo.dwSize.Y / 2 + 2 };
		notifi.notificationTable(pos_top_left, pos_bottom_right);
		GotoXY(screenInfo.dwSize.X / 2 - strlen(NO_DATA_FOUND) / 2, screenInfo.dwSize.Y / 2);
		printf(NO_DATA_FOUND);
	}
	else {
		GotoXY(0, 1);
		for (int i = 0; i < file.num_of_data; i++) {
			std::cout << "\n|" << i + 1 << "|" << std::setfill(' ') << std::setw(screenInfo.dwSize.X / 20) << ' ';
			std::cout << std::setfill('-') << std::setw(screenInfo.dwSize.X * 9 / 10) << '\n';
			createTableOfInfomationFor_historyPage(file.data[i], i * 7 + 3);
			printf("\n");
		}
	}
	printf("\n");

	GetConsoleScreenBufferInfo(hstdout, &screenInfo);
	GotoXY(0, screenInfo.dwSize.Y - 1);
	printf(STRING_VERSION);

	while (_getch() != CODE_BACKSPACE);
	system("cls");


	return GOTO_HOME_PAGE;
}

void updateDataTo_continueFile(Snake &snake) {
	wchar_t continue_file_name[] = L"data_for_continue_game.bin";
	HANDLE hfile = CreateFileW(continue_file_name, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE) { throw std::exception("Cannot open file to write"); };
	DWORD write_success;

	WriteFile(hfile, &snake.hard.speed, sizeof(snake.hard.speed), &write_success, NULL);
	WriteFile(hfile, &snake.time_left, sizeof(snake.time_left), &write_success, NULL);
	WriteFile(hfile, &snake.mode, sizeof(snake.mode), &write_success, NULL);
	WriteFile(hfile, &snake.point, sizeof(snake.point), &write_success, NULL);
	WriteFile(hfile, &snake.food, sizeof(snake.food), &write_success, NULL);
	WriteFile(hfile, &snake.length, sizeof(snake.length), &write_success, NULL);
	WriteFile(hfile, &snake.snake[0], sizeof(snake.snake[0]) * snake.length, &write_success, NULL);
	WriteFile(hfile, &snake.allowed_for_continue, sizeof(snake.allowed_for_continue), &write_success, NULL);
	
	CloseHandle(hfile);
	hfile = NULL;
}

void readDataFrom_continueFile(Snake& snake) {
	wchar_t continue_file_name[] = L"data_for_continue_game.bin";
	HANDLE hfile = CreateFileW(continue_file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hfile == INVALID_HANDLE_VALUE) { throw std::exception("Cannot open file to read"); };
	DWORD read_success;

	ReadFile(hfile, &snake.hard.speed, sizeof(snake.hard.speed), &read_success, NULL);
	ReadFile(hfile, &snake.time_left, sizeof(snake.time_left), &read_success, NULL);
	ReadFile(hfile, &snake.mode, sizeof(snake.mode), &read_success, NULL);
	ReadFile(hfile, &snake.point, sizeof(snake.point), &read_success, NULL);
	ReadFile(hfile, &snake.food, sizeof(snake.food), &read_success, NULL);
	ReadFile(hfile, &snake.length, sizeof(snake.length), &read_success, NULL);
	snake.snake.resize(snake.length);
	ReadFile(hfile, &snake.snake[0], sizeof(snake.snake[0]) * snake.length, &read_success, NULL);
	ReadFile(hfile, &snake.allowed_for_continue, sizeof(snake.allowed_for_continue), &read_success, NULL);


	CloseHandle(hfile);
	hfile = NULL;
}

