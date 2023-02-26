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

	void init();
	void fileclose();

	void guarda(int type, std::string message);

   //usar en caso de cambiar a oftream
   //void creaEscribe(std::ofstream& file);

private:


	FILE* file;
	//ThingsToSave messages;
	
};

