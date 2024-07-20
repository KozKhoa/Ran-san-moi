#include "file.h"

File::File() {
	hfile_history_file = CreateFileW(FILE_NAME_DATA_FOR_HISTORY_FILE, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	num_of_data = 0;
	data.resize(num_of_data);
	getDataFromFile_history();
}

File::~File() {
	CloseHandle(hfile_history_file);
	hfile_history_file = NULL;
	num_of_data = 0;
	data.resize(num_of_data);
}

void File::getDataFromFile_history() {
	DWORD num_of_bytes_read_success;
	bool open_file_success = ReadFile(hfile_history_file, &num_of_data, sizeof(int4), &num_of_bytes_read_success, NULL);
	data.resize(num_of_data);
	if (num_of_data == 0) {
		return;
	}
	open_file_success = ReadFile(hfile_history_file, &best_game, sizeof(Data_of_each_game), &num_of_bytes_read_success, NULL);
	open_file_success = ReadFile(hfile_history_file, &(data[0]), sizeof(Data_of_each_game) * num_of_data, &num_of_bytes_read_success, NULL);

}

void  File::writeDataToFile_history() {
	SetFilePointer(hfile_history_file, 0, NULL, FILE_BEGIN);
	DWORD num_of_bytes_read_success;
	bool open_file_success = WriteFile(hfile_history_file, &num_of_data, sizeof(int4), &num_of_bytes_read_success, NULL);
	open_file_success = WriteFile(hfile_history_file, &best_game, sizeof(Data_of_each_game), &num_of_bytes_read_success, NULL);
	open_file_success = WriteFile(hfile_history_file, &(data[0]), sizeof(Data_of_each_game) * num_of_data, &num_of_bytes_read_success, NULL);
}

void  File::updateToDataFor_history(char difficulty, char mode, int2 point, int2 speed, int2 length,
	int2 time_finish, time_t time_start) {
	Data_of_each_game game_data;
	game_data.length = length;
	game_data.difficulty = difficulty;
	game_data.point = point;
	game_data.speed = speed;
	game_data.time_finish = time_finish;
	game_data.mode = mode;

	game_data.time_start = time_start;

	if (game_data.point >= best_game.point) {
		best_game = game_data;
	}

	data.push_back(game_data);
	num_of_data++;
}



