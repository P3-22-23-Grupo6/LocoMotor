#include "LogSystem.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
using namespace LocoMotor;
LogSystem* Singleton<LogSystem>::_instance = nullptr;

LogSystem::LogSystem() {
	_file = nullptr;
}

LogSystem::~LogSystem() {
	FileClose();
}

void LogSystem::Initialize() {

	if (_file == nullptr)
		fopen_s(&_file, "log.txt", "w+");
}


void LogSystem::FileClose() {
	if (_file != nullptr)
		fclose(_file);
}



void LogSystem::Save(int type, std::string message) {

	if (_file == nullptr)
		fopen_s(&_file, "log.txt", "w+");

	std::string strToLog = "";
	if (type == 0) {
		strToLog = "Error: " + message + "\n";
		fprintf(_file, strToLog.c_str());
	}
	else if (type == 1) {
		strToLog = "Warning: " + message + "\n";
		fprintf(_file, strToLog.c_str());
	}

	else if (type > 1) {
		strToLog = message + "\n";
		fprintf(_file, strToLog.c_str());
	}

#ifdef _DEBUG
	std::cout << strToLog << "\n";
#endif // _DEBUG

}


