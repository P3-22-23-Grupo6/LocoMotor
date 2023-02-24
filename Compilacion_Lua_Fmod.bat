set BIN=.\Bin
::BUILD LUA

set LuaSln=.\Dependecies\Lua
msbuild %LuaSln%\Lua.sln /p:configuration=Debug
msbuild %LuaSln%\Lua.sln /p:configuration=Release
COPY /y %LuaSln%\build\Lua_d.dll %BIN%
COPY /y %LuaSln%\build\Lua.dll %BIN%

::COPY FMOD

COPY /y .\Dependecies\FMod\core\lib\x64\fmod.dll %BIN%
COPY /y .\Dependecies\FMod\core\lib\x64\fmodL.dll %BIN%