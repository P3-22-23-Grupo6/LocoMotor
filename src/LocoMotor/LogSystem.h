#pragma once
#include <fstream>
#include <vector>
#include <stdio.h>


//forma distinta para guardar los mensajes
//struct ThingsToSave {
//	std::vector<std::string> error;
//	std::vector<std::string> others;
//};


class LogSystem {
public:
	LogSystem();

	~LogSystem();

	void Init();
	void FileClose();

	void Save(int type, std::string message);



private:

	FILE* _file;

	//ThingsToSave messages;

};

