#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include <stack>
#include <stdint.h>
#include <vector>
#include <windows.h>

using int2 = int16_t;
using int4 = int32_t;

#define FILE_NAME_DATA_FOR_HISTORY_FILE L"data_for_history_file.bin"
#define FILE_NAME_DATA_FOR_CONTINUE_GAME L"data_for_continue_game.bin"

struct Data_of_each_game {
	char difficulty;
	char mode; // 'c' == classic, 'f' == freedom;
	int2 point;
	int2 speed;
	int2 length;
	int2 time_finish;
	time_t time_start;

};

class File {
private:
	HANDLE hfile_history_file;
	HANDLE hfile_continue_file;
public:
	File();
	~File();
	int4 num_of_data;
	Data_of_each_game best_game;
	std::vector<Data_of_each_game> data;
	void getDataFromFile_history();
	void writeDataToFile_history();
	void updateToDataFor_history(char difficulty, char mode, int2 point, int2 speed, int2 length,
		int2 time_finish, time_t time_start);
};

/*
Quy định về cấu trúc file :

- 4 byte đầu tiên là lưu số lượng dữ liệu có trong file, kiểu như là số n lần chơi á

- 18 byte đầu tiên là lần chơi có số điểm cao nhất mà gần đây nhất. 18 byte này không tính vào n lần chơi ở trên

- 18 * n byte tiếp theo là dữ liệu của các lần chơi

- Mỗi lần chơi là gồm các thông tin sau đây: 15 byte;
	+ Độ khó : 1 byte
	+ Mode : 1 byte
	+ Số điểm: 2 byte
	+ Tốc độ thấp nhất: 2 byte
	+ Chiều dài rắn : 2 byte
	+ Thời gian hoàn thành : 2 byte;
	+ Ngày giờ, tháng, năm bắt đầu chơi : 8 byte; (là time_t á);
*/

#endif // !_FILE_H_