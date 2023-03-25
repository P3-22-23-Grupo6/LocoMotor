#ifndef _SCRIPT_MANAGER_H
#define _SCRIPT_MANAGER_H
#pragma once
#include "Singleton.h"
#include <string>

namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	class SceneManager;

	class ScriptManager : public Singleton<ScriptManager> {
	public:
		bool Init();
		void LoadSceneFromFile(std::string path);
		
	private:
		void readLuaScript(const std::string path);
		void report_errors(int status);
		luabridge::LuaRef getFromLua(std::string name);
		void setParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer);
		ScriptManager();
		~ScriptManager();

		lua_State* luaState;
		SceneManager* scMan;

	};
}

#endif // !_SCRIPT_MANAGER_H
