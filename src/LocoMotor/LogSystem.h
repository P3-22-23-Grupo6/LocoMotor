#pragma once
#ifndef _LOGSYSTEM_
#define _LOGSYSTEM_
#include <fstream>
#include <vector>
#include <stdio.h>
#include "Singleton.h"


//forma distinta para guardar los mensajes
//struct ThingsToSave {
//	std::vector<std::string> error;
//	std::vector<std::string> others;
//};

namespace LocoMotor {
	class LogSystem : public LocoMotor::Singleton<LogSystem> {
		friend LocoMotor::Singleton<LogSystem>;

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
}

#endif