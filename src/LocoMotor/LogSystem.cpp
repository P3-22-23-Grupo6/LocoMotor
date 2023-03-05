#include "LogSystem.h"


LogSystem::LogSystem() {
	Init ();
	//Create ();
}

LogSystem::~LogSystem() {}

void LogSystem::Init() {

	fopen_s(&_file, "log.txt", "w+");
}

void LogSystem::FileClose () {
	fclose(_file);
}


void LogSystem::Save(int type, std::string message) {
	// Mensajes de error->0
	// Mensajes de aviso->1
	// Otros mensajes -> >1

	if (type == 0) {
		std::string errorStr = "Error: " + message + "\n";
		fprintf (_file, errorStr.c_str());
	}
	else if (type == 1 ) {
		std::string warnStr = "Warning: " + message + "\n";
		fprintf (_file, warnStr.c_str());
	}
	
	else if (type > 1 ) {
		std::string warnStr = message + "\n";
		fprintf (_file, warnStr.c_str());
	}

}


