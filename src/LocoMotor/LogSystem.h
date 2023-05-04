#pragma once
#ifndef _LOGSYSTEM_
#define _LOGSYSTEM_
#include <fstream>
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

		/// @brief Opens the file
		void Initialize();
		/// @brief Closes the file
		void FileClose();
		/// @brief Saves the message information on the file
		/// @param type The type of the message 0->Error type 1->Warning type >1->Other
		/// @param message The info of the message
		void Save(int type, std::string message);



	private:

		FILE* _file;
		LogSystem();

		//ThingsToSave messages;

	};
}

#endif