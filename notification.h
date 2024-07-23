#pragma once
#include "console.h"
#include <fcntl.h> // khai báo để dùng _O_U16TEXT
#include <io.h> // khai báo để dùng setmode
#include <time.h>
#include <iomanip> // Khai báo để dùng setfill và setw

#ifndef _DEFINE_CUA_NOTIFICATION

#define POINT_NUMBER char(178) // ▓
#define POINT_CHARACTER char(219)
#define POINT_NGANG char(254)
#define WAIT_COUNT_DOWN 1000

#define CHAR_WIDTH 5
#define CHAR_HEIGHT 5

#define BLACK 0
#define AQUA 3
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGTH_AQUA 11

#define KHUNG_TOP_LEFT char(201)
#define KHUNG_TOP_RIGHT char(187)
#define KHUNG_BOTTOM_LEFT char(200)
#define KHUNG_BOTTOM_RIGHT char(188)
#define KHUNG_TOP char(205)
#define KHUNG_LEFT char(186)

#endif // !_DEFINE_CUA_NOTIFICATION




class Notifi {
private:
	char** number;
	char** c; // kí tự

	
	//void deleteTableFor_notificationTable(COORD pos_top_left, COORD pos_bottom_right);
	//void createTableFor_notificationTable(COORD pos_top_left, COORD pos_bottom_right);
public:
	Notifi();
	~Notifi();
	void print_number();
	void print_character();
	void readyClock();
	int4 countClock(time_t sec, bool &reset);	
	// Number
	void reset_number();
	void numberOne();
	void numberTwo();
	void numberThree();
	//
	//Character
	void reset_character();
	void character_A();
	void character_C();
	void character_D();
	void character_E();
	void character_F();
	void character_I();
	void character_K();
	void character_L();
	void character_N();
	void character_S();
	void character_T();
	void character_U();

	void character_Y();


	void character_a();
	void character_e();
	void character_k();
	void character_n();
	void character_s();
	
	void notificationTable(COORD pos_top_left, COORD pos_bottom_right);
	void deleteNotificatinoTable(COORD pos_top_left, COORD pos_bottom_right);
	//int countClock(bool& reset_time);
	void printNoDataFound();
};