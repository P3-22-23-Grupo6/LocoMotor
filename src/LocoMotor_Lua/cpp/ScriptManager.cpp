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
using namespace LocoMotor;

//bool LocoMotor::ScriptManager::Init() {
//	
//	return true;
//}
ScriptManager* Singleton<ScriptManager>::_instance = nullptr;

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
    Scene* s = SceneManager::GetInstance()->GetCurrentScene();
    readLuaScript(path);

    luabridge::LuaRef allEnts = getFromLua("entities");
    //luabridge::LuaRef layers = getFromLua("layers");
    int numEnts = allEnts.length();

    for (int i = 1; i <= numEnts; i++) {
        luabridge::LuaRef entity = getFromLua(allEnts[i]);

        //De referencia por si hacemos layers
        //std::string layer;
        /*f (!layers.isNil()) {
            luabridge::LuaRef l = getFromLua(allEnts[i]);
            layer = l.tostring();
        }
        else
            layer = "prueba";*/

        //Cargo las entidades 
        GameObject* ent = s->GetObjectByName(allEnts[i]);
        if (ent == nullptr) {
            ent = s->AddGameobject(allEnts[i]);
        }
        std::cout << "Loading entity: " << allEnts[i] << " Components: \n";
        setParams(entity, ent, nullptr, "layer");
        
        ent->StartComp();
    }

}

ScriptManager::ScriptManager() {
    luaState = luaL_newstate();
    //scMan = SceneManager::GetInstance();
    luaL_openlibs(luaState);
}

LocoMotor::ScriptManager::~ScriptManager()
{
    lua_close(luaState);
	//delete luaState;
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

        
        ent->AddComponent(compName, parameters);
        for (auto p : parameters) {
            std::cout << "\t" << p.first << ": " << p.second << "\n";
        }
        lua_pop(entity, 1);
    }

}
