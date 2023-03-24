#include "ScriptManager.h"

using namespace LocoMotor;

ScriptManager::ScriptManager() {
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
}

LocoMotor::ScriptManager::~ScriptManager()
{
	delete luaState;
}
