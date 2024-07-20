#pragma once
#include <vector>
#include <stdint.h> 
#include <conio.h> // khai báo để dùng hàm _getch và _khbit
#include "console.h"
#include <iomanip> // khai báo để xài hàm std::setfill và std::setw
#include "notification.h"
#include <fcntl.h> // khai báo để dùng _O_U16TEXT, xuất tiếng việt
#include <io.h>    // khai báo để dùng _setmode, xuất tiếng việt
#include <time.h>
#include "file.h"

#ifndef _DEFINE_CAC_THU_

#ifndef _SET_UP_WALL_
	#define TI_LE_TUONG_CHIEU_DAI 10
	#define TI_LE_TUONG_CHIEU_CAO 7
#endif // !_SET_UP_WALL_

#ifndef _CREATE_WALL_
	#define WALL_TOP_LEFT char(201)
	#define WALL_TOP_RIGHT char(187)
	#define WALL_BOTTOM_LEFT char(200)
	#define WALL_BOTTOM_RIGHT char(188)
	#define WALL_TOP char(205)
	#define WALL_BOTTOM char(205)
	#define WALL_LEFT char(186)
	#define WALL_RIGHT char(186)
#endif // _CREATE_WALL_

#ifndef _DIFFICULT_PAGE_
	#define DISTANCE_FROM_TOP_DIFFICULT_PAGE 3
	#define DISTANCE_FROM_LEFT screenInfo.dwSize.X / 2 - DIFFICULTY_LENGTH / 2
	#define DISTANCE_FROM_DIFFICULTY 5
	#define CHOOSE_DIFFICULTY "HÃY CHỌN ĐỘ KHÓ"
	
	#define POS_OF_EASY_X screenInfo.dwSize.X / 2 - strlen(EASY) / 2
	#define POS_OF_EASY_Y  DISTANCE_FROM_TOP_DIFFICULT_PAGE + 5 + DISTANCE_FROM_DIFFICULTY + 4
	#define POS_OF_MEDIUM_X screenInfo.dwSize.X / 2 - strlen(MEDIUM) / 2
	#define POS_OF_MEDIUM_Y POS_OF_EASY_Y + 3
	#define POS_OF_HARD_X screenInfo.dwSize.X / 2 - strlen(HARD) / 2
	#define POS_OF_HARD_Y POS_OF_MEDIUM_Y + 3
	
	#define POS_POINTER_CHOICE_LEFT_X screenInfo.dwSize.X / 2 - 10
	#define POS_POINTER_CHOICE_RIGHT_X screenInfo.dwSize.X / 2 + 9
	#define POINTER_CHAR_LEFT char(175)
	#define POINTER_CHAR_RIGHT char(174)
	#define DIFFICULTY_LENGTH 59 // 10 * 5 + 9

#endif // !_DIFFICULT_PAGE_

#ifndef _HOME_PAGE_
	#define DISTANCE_FROM_TOP_SNAKE_PAGE 2
	#define SNAKES_LENGTH 30 // 5 * 6
	#define DISTANCE_FROM_SNAKE_CHARATER DISTANCE_FROM_TOP_SNAKE_PAGE + 5 + 4
	#define DISTANCE_FROM_MODE_GAME_CHAR DISTANCE_FROM_SNAKE_CHARATER + 3
	#define STRING_NEW_GAME "NEW GAME"
	#define STRING_CONTINUE "CONTINUE"
	#define STRING_HISTORY "HISTORY"
	#define STRING_OPTIONS "OPTIONS"
	#define STRING_MODE_GAME "MODE : "

	#define DISTANCE_FROM_NEW_GAME DISTANCE_FROM_MODE_GAME_CHAR + 3
	#define DISTACNE_FROM_CONTINUE DISTANCE_FROM_NEW_GAME + 3
	#define DISTANCE_FROM_HISTORY DISTACNE_FROM_CONTINUE + 3
	#define DISTANCE_FROM_OPTION DISTANCE_FROM_HISTORY + 3

//#define POS_POINTER_CHOICE_STATER_PAGE_LEFT_X screenInfo.dwSize.X / 2 - 10
//#define POS_POINTER_CHOICE_STATER_PAGE_RIGHT_X screenInfo.dwSize.X / 2 + 10
#endif // !_HOME_PAGE_

#ifndef _TIME_UP_
#define KHUNG_TOP_LEFT char(201)
#define KHUNG_TOP_RIGHT char(187)
#define KHUNG_BOTTOM_LEFT char(200)
#define KHUNG_BOTTOM_RIGHT char(188)
#define KHUNG_TOP char(205)
#define KHUNG_LEFT char(186)

#define PLAY_AGAIN "PLAY AGAIN"
#define HOME "HOME"
#define EXIT "EXIT"
#define STRING_TIME_UP L"-->  HẾT THỜI GIAN  <--"

#endif // !_TIME_UP_

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPULE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_AQUA 11
#define LIGHT_RED 12
#define LIGHT_PURPLE 13
#define LIGHT_YELLOW 14
#define BRIGHT_WHITE 15

#define HINH_DAU_RAN char(254)
#define HINH_DAU_RAN_LEN char(220)
#define HINH_DAU_RAN_XUONG char(223)
#define HINH_DUOI_RAN char(250)

#define HINH_DOT_RAN char(205)
#define HINH_DOT_RAN_DOC char(186)

#define TURN_RIGHT_DOWN char(201)
#define TURN_LEFT_DOWN char(187)
#define TURN_RIGHT_UP char(200)
#define TURN_LEFT_UP char(188)

#define SNAKE_COLOR 7 //white
#define BACKGROUND_COLOR 0 // black 

#define EASY "EASY"
#define MEDIUM "MEDIUM"
#define HARD "HARD"
#define TEN_GAME "GAME RAN SAN MOI"
#define POINT "POINT : "
#define LENGTH "CHIEU DAI RAN : "
#define COUNT_DOWN "THOI GIAN CON LAI : "
#define SPEED "SPEED : "
#define FOOD_POS "VI TRI THUC AN : "
#define STRING_SAVE_AND_EXIT "SAVE AND EXIT"

#define LIMIT_TIME_EASY 120
#define LIMIT_TIME_MEDIUM 90
#define LIMIT_TIME_HARD 60;
#define EASY_CHOICE 'e'
#define MEDIUM_CHOICE 'm'
#define HARD_CHOICE 'h'
#define PLUS_POINT_EASY 10
#define PLUS_POINT_MEDIUM 12
#define PLUS_POINT_HARD 15
#define SPEED_EASY 150
#define SPEED_MEDIUM 120
#define SPEED_HARD 100
#define MINUS_SPEED_EASY 1
#define MINUS_SPEED_MEDIUM 2
#define MINUS_SPEED_HARD 3

#define MINIMUM_SPEED 10

#define DISTANCE_FROM_TOP_WALL 2
#define POS_STATUC_RIGHT 18

#define CODE_UP_ARROW 72
#define CODE_DOWN_ARROW 80
#define CODE_LEFT_ARROW 75
#define CODE_RIGHT_ARROW 77
#define CODE_ENTER 13
#define CODE_BACKSPACE 8

#define STRING_VERSION "ver 1.0.0"

#define GOTO_HOME_PAGE 0
#define GOTO_DIFFICULTY_PAGE 1
#define GOTO_GAMEPLAY_PAGE 2
#define GOTO_CONTINUE_GAME 3
#define GOTO_HISTORY_PAGE 4
#define GOTO_OPTIONS_PAGE 5
#define GOTO_EXIT 6
#define GOTO_CHANGE_MODE_PAGE 1965
#define GOTO_DO_NOT_THING 3647

#define STRING_GAME_OVER L"-->  GAME OVER  <--"
#define STRING_PAUSE_GAME "-->  PAUSE GAME  <--"

#define CHAR_FOOD char(42)

#define MODE_CLASSIC 'c'
#define MODE_FREEDOM 'f'

#define CHAR_BACK char(174)

#define LOSE_BY_EAT_ITSELF 2345
#define LOSE_BY_WALL 2346
#define LOSE_BY_TIME_UP 2247
#define NOT_LOSE 2348

#endif // !_DEFINE_CAC_THU_

using int4 = int32_t;

class Snake {
private:
	CONSOLE_SCREEN_BUFFER_INFO screenInfo;
	struct Point {
		int4 x;
		int4 y;
	};
	struct Wall {
		Point top_left;
		Point top_right;
		Point bottom_left;
		Point bottom_right;
	};
	struct Difficulty {
		char difficulty; // 'e' = easy, 'm' = medium, 'h' = hard;
		time_t limit_time;
		int4 plus_point;
		int4 speed;
		int4 minus_speed;
	};
	std::vector<Point> snake;
	Point head;
	Point tail;
	Point food;
	
	bool exist_food;
	char head_direction;
	char prev_head_direction;

	int choice(int num_of_choice, COORD pos_of_first_choice, int distance_between_each_choice);
	void inDauRan();
	void themDotRan();
	void inDuoiRan();
	void inCoRan();
	void setupWall();
	int chooseDifficulty();
	void printDIFFICULTY_character(int distance_from_top, int distance_from_left);
	void printSNAKES_character(int distance_from_top, int distance_from_left);
	int chooseHome();
	void createTableFor_endGame(COORD pos_top_left, COORD pos_bottom_right);
	void createTableOfInfomationFor_historyPage(Data_of_each_game &data, int distance_from_the_previous);
	void changeMode();
public:
	Snake();
	~Snake();
	int pauseGame();
	Wall wall; 
	int4 point;
	Difficulty hard;
	int4 length;
	char mode;
	int4 time_use;
	time_t time_start;
	bool allowed_for_continue;
	void printSnake();
	void moveSnack();
	void changeDirection(int event);
	void createWall();
	void deleteWall();
	int checkGameOver();
	int endGame(const wchar_t* content);
	void randomFood();
	bool checkEatFood();
	void speedGame();
	void resetSnakeData(); // không reset difficulty;
	void createStatus();
	void updateStatus();
	bool updateTime(int4 sec); // trả về true nếu còn thời gian, trả về false nếu hết thời gian
	int difficultyPage();
	int homePage();
	int gamePlayPage();
	int historyPage(File &file);
};