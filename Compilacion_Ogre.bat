set BIN=.\Bin
set cmake=.\Dependecies\CMake\bin\cmake.exe
:: CMAKE OGRE

set OgreSrc=.\Dependecies\Ogre\Src
set OgreBuild=.\Dependecies\Ogre\Build
mkdir %OgreBuild%
%cmake% -DOGRE_PROJECT_FOLDERS:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL3PLUS:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="1" -DOGRE_BUILD_COMPONENT_PAGING:BOOL="0" -DOGRE_ENABLE_PRECOMPILED_HEADERS:BOOL="0" -DOGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL="1" -DOGRE_BUILD_PLUGIN_DOT_SCENE:BOOL="0" -DOGRE_BUILD_COMPONENT_VOLUME:BOOL="0" -DOGRE_BUILD_PLUGIN_PFX:BOOL="1" -DOGRE_BUILD_SAMPLES:BOOL="0" -DOGRE_BUILD_PLUGIN_OCTREE:BOOL="0" -DOGRE_BUILD_COMPONENT_PROPERTY:BOOL="0" -DOGRE_BUILD_PLUGIN_ASSIMP:BOOL="0" -DOGRE_INSTALL_DEPENDENCIES:BOOL="0" -DOGRE_INSTALL_TOOLS:BOOL="0" -DOGRE_CONFIG_FILESYSTEM_UNICODE:BOOL="0" -DOGRE_BUILD_COMPONENT_TERRAIN:BOOL="0" -DOGRE_BUILD_COMPONENT_OVERLAY:BOOL="1" -DOGRE_BUILD_COMPONENT_OVERLAY_IMGUI:BOOL="0" -DOGRE_BUILD_COMPONENT_BITES:BOOL="0" -DOGRE_BUILD_MSVC_MP:BOOL="0" -DOGRE_BUILD_MSVC_ZM:BOOL="0" -DOGRE_BUILD_PLUGIN_PCZ:BOOL="0" -DOGRE_INSTALL_DOCS:BOOL="0" -DOGRE_BUILD_COMPONENT_RTSHADERSYSTEM:BOOL="1" -DOGRE_INSTALL_SAMPLES:BOOL="0" -DOGRE_BUILD_COMPONENT_BULLET:BOOL="0" -DOGRE_BUILD_TOOLS:BOOL="1" -DOGRE_INSTALL_PDB:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GLES2:BOOL="0" -DOGRE_BUILD_RENDERSYSTEM_GL:BOOL="1" -DOGRE_BUILD_COMPONENT_MESHLODGENERATOR:BOOL="1" -DOGRE_BUILD_PLUGIN_BSP:BOOL="0" -S %OgreSrc% -B %OgreBuild%
msbuild %OgreBuild%\OGRE.sln /p:configuration=Debug
msbuild %OgreBuild%\OGRE.sln /p:configuration=Release

COPY /y %OgreBuild%\bin\debug\Codec_STBI_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreMain_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\RenderSystem_Direct3D11_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\zlib.dll %BIN%
COPY /y %OgreBuild%\bin\debug\OgreRTShaderSystem_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\Plugin_ParticleFX_d.dll %BIN%
COPY /y %OgreBuild%\bin\debug\RenderSystem_GL_d.dll %BIN%

COPY /y %OgreBuild%\bin\release\Codec_STBI.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreMain.dll %BIN%
COPY /y %OgreBuild%\bin\release\RenderSystem_Direct3D11.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreXMLConverter.exe %BIN%
COPY /y %OgreBuild%\bin\release\OgreMeshUpgrader.exe %BIN%
COPY /y %OgreBuild%\bin\release\SDL2.dll %BIN%
COPY /y %OgreBuild%\bin\release\OgreRTShaderSystem.dll %BIN%
COPY /y %OgreBuild%\bin\release\Plugin_ParticleFX.dll %BIN%
COPY /y %OgreBuild%\bin\release\RenderSystem_GL.dll %BIN%
