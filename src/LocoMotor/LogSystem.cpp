#include "LogSystem.h"


LogSystem::LogSystem () {
	Init ();
	//Create ();
}

LogSystem::~LogSystem () {}

void LogSystem::Init () {

	fopen_s (&_file, "log.txt", "w+");
}

void LogSystem::FileClose () {
	fclose (_file);
}



//void guarda(int type, std::string message) {
//void guarda(int type, std::string message,FILE* file) {
void LogSystem::Save (int type, std::string message) {
	/*if (type == 0)
		messages.error.push_back ("Error: " + message);
	else if (type == 1) {
		messages.others.push_back ("Other: " + message);
	}*/


	if (type == 0) {
		std::string errorStr = "Error: " + message + "\n";
		fprintf (_file, errorStr.c_str ());
	}
	else if (type > 1) {
		std::string warnStr = "Warning: " + message + "\n";
		fprintf (_file, warnStr.c_str ());
	}

}


//primera ver
//void LogSystem::Create (std::ofstream& file) {
//	for (int i = 0; i < messages.error.size (); i++) {
//		file << messages.error[i] << "\n";
//	}
//
//	for (int i = 0; i < messages.others.size(); i++) {
//		file << messages.others[i] << "\n";
//	}
//
//}
