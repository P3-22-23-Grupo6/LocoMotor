#ifndef _SCRIPT_MANAGER_H
#define _SCRIPT_MANAGER_H
#pragma once
#include "Singleton.h"

extern "C" {
#include "lua.h";
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

namespace LocoMotor {
	class SceneManager;

	class ScriptManager : public Singleton<ScriptManager> {
	public:
		void LoadSceneFromFile(std::string& filepath);

	private:
		ScriptManager();
		~ScriptManager();

		lua_State* luaState;
		SceneManager* scMan;

	};
}

#endif // !_SCRIPT_MANAGER_H
