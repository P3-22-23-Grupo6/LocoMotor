#include "ScriptManager.h"
#include "Scene.h"
#include "SceneManager.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"
#include "Transform.h"
#include "LogSystem.h"
using namespace LocoMotor;

ScriptManager* Singleton<ScriptManager>::_instance = nullptr;

luabridge::LuaRef ScriptManager::GetFromLua(std::string name) {
	return luabridge::getGlobal(_luaState, name.c_str());
}

void ScriptManager::Report_errors(int status) {
	if (status == 0) {
		return;
	}

    LogSystem::GetInstance()->Save(0, "[LUA ERROR] " + (std::string)lua_tostring(_luaState, -1));
    //std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

	// remove error message from Lua state
	lua_pop(_luaState, 1);
}

int ScriptManager::ReadLuaScript(const std::string path) {
    
    // load some code from Lua file
    int scriptLoadStatus = luaL_dofile(_luaState, path.c_str());

    // define error reporter for any Lua error
    Report_errors(scriptLoadStatus);
    return scriptLoadStatus;
}

bool ScriptManager::LoadSceneFromFile(std::string path) {
    if (ReadLuaScript(path) != 0) {
        return false;
    }
    Scene* s = SceneManager::GetInstance()->GetSceneByName(path);
    if (s == nullptr) {
        s = _scMan->CreateScene(path);
    }

	luabridge::LuaRef allEnts = GetFromLua("entities");
	int numEnts = allEnts.length();

	for (int i = 1; i <= numEnts; i++) {
		luabridge::LuaRef entity = GetFromLua(allEnts[i]);

		//Cargo las entidades 
		GameObject* ent = s->GetObjectByName(allEnts[i]);
		if (!SetParams(entity, ent, nullptr, "layer")) {
			s->RemoveGameobject(allEnts[i]);
		}
	}

    SceneManager::GetInstance()->ChangeScene(path);
    return true;
}

ScriptManager::ScriptManager() {
	_luaState = luaL_newstate();
	_scMan = SceneManager::GetInstance();
	luaL_openlibs(_luaState);
}

LocoMotor::ScriptManager::~ScriptManager()
{
	lua_close(_luaState);
}

bool ScriptManager::SetParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer)
{

	lua_pushnil(entity);
	if (entity.isNil()) {
		LocoMotor::LogSystem::GetInstance()->Save(0, "LUA: Gameobject '" + ent->GetName() + "' has been declared but not defined");
		return false;
	}
	while (lua_next(entity, 0) != 0) {


		std::string compName = lua_tostring(entity, -2);
		std::string key;

		luabridge::LuaRef component = entity[compName];
		lua_pushnil(component);




		std::vector<std::pair<std::string, std::string>> parameters;

		while (lua_next(component, 0) != 0) {
			std::string key = lua_tostring(entity, -2);
			std::string val = lua_tostring(entity, -1);

			parameters.push_back({ key, val });
			lua_pop(component, 1);
		}


		ent->AddComponent(compName, parameters);
		lua_pop(entity, 1);
	}
	if (ent->GetComponent<Transform>() == nullptr)
		ent->AddComponent("Transform");
	return true;
}
