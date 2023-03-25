#include "ScriptManager.h"
#include "Scene.h"
#include "SceneManager.h"
extern "C" {
#include "lua.h";
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>
#include "GameObject.h"

using namespace LocoMotor;

bool LocoMotor::ScriptManager::Init() {
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
	return true;
}


luabridge::LuaRef ScriptManager::getFromLua(std::string name) {
    return luabridge::getGlobal(luaState, name.c_str());

}

void ScriptManager::report_errors(int status) {
    if (status == 0) {
        return;
    }

    std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

    // remove error message from Lua state
    lua_pop(luaState, 1);
}

void ScriptManager::readLuaScript(const std::string path) {
    
    // load some code from Lua file
    int scriptLoadStatus = luaL_dofile(luaState, path.c_str());

    // define error reporter for any Lua error
    report_errors(scriptLoadStatus);
}
void ScriptManager::LoadSceneFromFile(std::string path) {
   // Scene* s = SceneManager::GetInstance()->getCurrentScene();
    readLuaScript("Assets/Scripts/Mapa.lua");

    luabridge::LuaRef allEnts = getFromLua("entities");
    luabridge::LuaRef layers = getFromLua("layers");
    int numEnts = allEnts.length();

    for (int i = 1; i <= numEnts; i++) {
        luabridge::LuaRef entity = getFromLua(allEnts[i]);
        std::string layer;
        if (!layers.isNil()) {
            luabridge::LuaRef l = getFromLua(allEnts[i]);
            layer = l.tostring();
        }
        else
            layer = "prueba";

        GameObject* ent;
        if (ent == nullptr) {
            //ent = s->AddE;
            //std::cout << "Loading entity: " << ent->getName() << "\n";
            ent->AddComponent<Transform>("transform");
        }
       // setParams(entity, ent, s, layer);
    }

}

ScriptManager::ScriptManager() {
	
}

LocoMotor::ScriptManager::~ScriptManager()
{
	delete luaState;
}

void ScriptManager::setParams(luabridge::LuaRef entity, GameObject* ent, Scene* s, std::string layer)
{

    lua_pushnil(entity);
    while (lua_next(entity, 0) != 0) {
        std::string compName = lua_tostring(entity, -2);
        std::cout << "       Loading component: " << compName << "\n";
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

        
        ent->AddComponent<Component>(compName, parameters);
        
        lua_pop(entity, 1);
    }

}
