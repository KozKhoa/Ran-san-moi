#include <iostream>
#include "console.h"
#include "snake.h"
#include "notification.h"
#include <corecrt_wstring.h> // Khai báo để dùng wcslen();
#include <stack>
#include "file.h"


int ai() {
	showPointer(turnOffPointer);
	Snake snake;
	Notifi notifi;
	
	snake.gamePlayPage();
	_getch();
	GotoXY(0, 20);

	return 0;
}

int4 mai() {
	SetConsoleTitle(L"GAME RẮN SĂN MỒI");
	showPointer(turnOffPointer);
	Snake snake;
	File data_file;
	Notifi notifi;
	std::stack<int> action;
	action.push(GOTO_HOME_PAGE);
	std::stack<Snake> contine; // dùng cho mục continue
	readDataFrom_settingsFile(snake);
	while (!action.empty()) {
		int event = action.top();
		action.pop();
		if (event == GOTO_HOME_PAGE) {
			action.push(snake.homePage());
		}
		else if (event == GOTO_DIFFICULTY_PAGE) {
			action.push(snake.difficultyPage());
		}
		else if (event == GOTO_GAMEPLAY_PAGE) {
			action.push(snake.gamePlayPage());
			if (snake.allowed_for_continue == false) {
				data_file.updateToDataFor_history(snake.hard.difficulty, snake.mode, snake.point, snake.hard.speed, snake.length, snake.time_use, snake.time_start);
				data_file.writeDataToFile_history();
			}
			updateDataTo_continueFile(snake);
			snake.resetSnakeData();
		}
		else if (event == GOTO_CONTINUE_GAME) {
			readDataFrom_continueFile(snake);
			if (snake.allowed_for_continue == false) {
				action.push(GOTO_HOME_PAGE);
				snake.resetSnakeData();
				notifi.printNoDataFound();
			}
			else {
				action.push(GOTO_GAMEPLAY_PAGE);
			}
		} 
		else if (event == GOTO_HISTORY_PAGE) {
			action.push(snake.historyPage(data_file));
		}
		cls();
		
	}

	// TỐI 13/07/2024 BUG CŨ XUẤT HIỆN LẠI, LỖI MẤT HIỆN THỊ MỒI
	// CẦN FIX LỖI KHI VÀO CHƠI CONTINUE THÌ LẠI BỊ RESET TIME LẠI BAN ĐẦU
	// CẦN PHẢI XỬ LÍ CÁI TIME - THỜI GIAN CÒN LẠI KHI CHƠI CONTINUE NẾU KHÔNG THÌ THỜI GIAN SẼ BỊ ĐẶT SAI
	// XỬ LÍ LÔI KO HIỂN THỊ VÍ TRÍ CỦA THỨC ĂN NGAY KHI VỪA MỚI VÀO 
	// BUG XẢY RA KHI TA CHƠI GAME MỚI A VÀ PAUSE GIỮA CHỪNG, SAU ĐÓ LẠI CHƠI GAME MỚI B VÀ THUA, KẾ TIẾP LÀ THÓAT CHƯƠNG TRÌNH, RỒI VÀO LẠI 
	//		CHƯƠNG TRÌNH, KHI NÀY THÌ ẤN CONTINUE THÌ GAME LẠI TIẾP TỤC MÀN CHƠI A BAN ĐẦU MÀ THAY VÌ ĐÁNG LẼ NÊN THÔNG BÁO LÀ KO CÓ DỮ LIỆU

	return 0;
}