// Lua_prj.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//


extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge\LuaBridge.h>

class Vector3 {
protected:
	float x;
	float y;
	float z;
public:
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {
	}
	void SetX(float newX) {
		x = newX;
	}
	void SetY(float newY) {
		y = newY;
	}
	void SetZ(float newZ) {
		z = newZ;
	}

	float GetX() {
		return x;
	}
	float GetY() {
		return y;
	}
	float GetZ() {
		return z;
	}
};

void report_errors(lua_State* luaState, int status) {
	if (status == 0) {
		return;
	}

	std::cerr << "[LUA ERROR] " << lua_tostring(luaState, -1) << std::endl;

	// remove error message from Lua state
	lua_pop(luaState, 1);
}

int exec() {
	// create a Lua state
	lua_State* luaState = luaL_newstate();

	// load standard libs
	luaL_openlibs(luaState);

	// load some code from Lua file
	int scriptLoadStatus = luaL_dofile(luaState, "Assets/luaScript.lua");

	// define error reporter for any Lua error
	report_errors(luaState, scriptLoadStatus);

	// call function defined in Lua script
	luabridge::LuaRef add = luabridge::getGlobal(luaState, "add");

	int x = add(15, 12);

	std::cout << "[EVALUATE LUA] 15 + 12 = " << x << std::endl;

	return 0;
}
