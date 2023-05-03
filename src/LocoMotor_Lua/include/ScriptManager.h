#ifndef _SCRIPT_MANAGER_H
#define _SCRIPT_MANAGER_H
#pragma once
#ifdef _MOTORDLL
#define MOTOR_API __declspec(dllexport)
#else
#define MOTOR_API __declspec(dllimport)
#endif

#include "Singleton.h"
#include <string>

struct lua_State;
namespace luabridge {
	class LuaRef;
}

namespace LocoMotor {
	class SceneManager;
	class GameObject;
	class Scene;
	class MOTOR_API ScriptManager : public Singleton<ScriptManager> {
		friend Singleton<ScriptManager>;
	public:
		/// @brief Reads a lua file and builds the scene from that file
		/// @param path The path to find the lua file
		bool LoadSceneFromFile(std::string path);
	private:
		/// @brief Reads the lua script 
		/// @param path The path to find the lua script
		int ReadLuaScript(const std::string path);
		/// @brief Reports errors giving a status when reading lua
		/// @param status 
		void Report_errors(int status);
		/// @brief Get a param from lua file giving the name of the param
		luabridge::LuaRef GetFromLua(std::string name);
		/// @brief Sets the param read from lua to the gameobject and scene
		bool SetParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer);
		ScriptManager();
		~ScriptManager();
		lua_State* _luaState;
		SceneManager* _scMan;

	};
}

#endif // !_SCRIPT_MANAGER_H
