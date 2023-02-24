set BIN=.\Bin
set cmake=.\Dependecies\CMake\bin\cmake.exe
:: CMAKE OGRE

set OgreSrc=.\Dependecies\Ogre\Src
set OgreBuild=.\Dependecies\Ogre\Build
mkdir %OgreBuild%
%cmake% -DOGRE_PROJECT_FOLDERS:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="0" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="1" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="0" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_PLUGIN_ASSIMP:BOOL="0" -DOGRE_INSTALL_DEPENDENCIES:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_CONFIG_FILESYSTEM_UNICODE:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_MSVC_MP:BOOL="0" -DOGRE_BUILD_MSVC_ZM:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="0" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BULLET:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="0" -DOGRE_INSTALL_PDB:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GLES2:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="0" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="0" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0"  -S %OgreSrc% -B %OgreBuild%
msbuild %OgreBuild%\OGRE.sln /p:configuration=Debug
msbuild %OgreBuild%\OGRE.sln /p:configuration=Release

COPY /y %OgreBuild%\bin\debug\Codec_STBI_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreMain_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\RenderSystem_Direct3D11_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\zlib.dll %BIN%
COPY /y %OgreBuild%\bin\release\Codec_STBI.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreMain.dll %BIN%
COPY /y %OgreBuild%\bin\release\RenderSystem_Direct3D11.dll %BIN%


::CMAKE BULLET
set BulletBuild=.\Dependecies\Bullet\Build
set BulletSrc=.\Dependecies\Bullet\Src
mkdir %BulletBuild%
%cmake% -DBUILD_HACD_EXTRA:BOOL="0" -DBUILD_CLSOCKET:BOOL="0" -DBUILD_UNIT_TESTS:BOOL="0" -DINSTALL_CMAKE_FILES:BOOL="0" -DBUILD_BULLET_ROBOTICS_GUI_EXTRA:BOOL="0" -DBUILD_ENET:BOOL="0" -DENABLE_VHACD:BOOL="0" -DUSE_GLUT:BOOL="0" -DUSE_MSVC_DISABLE_RTTI:BOOL="0" -DUSE_MSVC_FAST_FLOATINGPOINT:BOOL="0" -DBUILD_OBJ2SDF_EXTRA:BOOL="0" -DBUILD_EXTRAS:BOOL="0" -DUSE_GRAPHICAL_BENCHMARK:BOOL="0" -DUSE_MSVC_STRING_POOLING:BOOL="0" -DBUILD_GIMPACTUTILS_EXTRA:BOOL="0" -DUSE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD:BOOL="0" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DBUILD_SERIALIZE_EXTRA:BOOL="0" -DBUILD_INVERSE_DYNAMIC_EXTRA:BOOL="0" -DBUILD_CPU_DEMOS:BOOL="0" -DBUILD_BULLET2_DEMOS:BOOL="0" -DBUILD_BULLET3:BOOL="0" -DBUILD_BULLET_ROBOTICS_EXTRA:BOOL="0" -DUSE_MSVC_FUNCTION_LEVEL_LINKING:BOOL="0" -DBUILD_CONVEX_DECOMPOSITION_EXTRA:BOOL="0" -DUSE_MSVC_COMDAT_FOLDING:BOOL="0" -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" -S %BulletSrc% -B %BulletBuild% 

msbuild %BulletBuild%\Src\BulletCollision\BulletCollision.vcxproj /p:configuration=Debug   
msbuild %BulletBuild%\Src\BulletCollision\BulletCollision.vcxproj /p:configuration=Release   
msbuild %BulletBuild%\Src\BulletDynamics\BulletDynamics.vcxproj /p:configuration=Debug   
msbuild %BulletBuild%\Src\BulletDynamics\BulletDynamics.vcxproj /p:configuration=Release   
msbuild %BulletBuild%\Src\LinearMath\LinearMath.vcxproj /p:configuration=Debug   
msbuild %BulletBuild%\Src\LinearMath\LinearMath.vcxproj /p:configuration=Release 

::BUILD LUA

set LuaSln=.\Dependecies\Lua
msbuild %LuaSln%\Lua.sln /p:configuration=Debug
msbuild %LuaSln%\Lua.sln /p:configuration=Release
COPY /y %LuaSln%\build\Lua_d.dll %BIN%
COPY /y %LuaSln%\build\Lua.dll %BIN%

::COPY FMOD

COPY /y .\Dependecies\FMod\core\lib\x64\fmod.dll %BIN%
COPY /y .\Dependecies\FMod\core\lib\x64\fmodL.dll %BIN%