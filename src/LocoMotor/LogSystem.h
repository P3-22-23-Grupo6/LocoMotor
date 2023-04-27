#pragma once
#include <fstream>
#include <vector>
#include <stdio.h>
#include "Singleton.h"


//forma distinta para guardar los mensajes
//struct ThingsToSave {
//	std::vector<std::string> error;
//	std::vector<std::string> others;
//};


class LogSystem : public Singleton<LogSystem> {
	friend Singleton<LogSystem>;

public:

	~LogSystem();

	void Initialize();
	void FileClose();

	void Save(int type, std::string message);



private:

	FILE* _file;
	LogSystem();

	//ThingsToSave messages;

};

