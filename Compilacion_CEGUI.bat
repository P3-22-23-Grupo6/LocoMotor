set DEPENDENCIESPATH=Dependecies
set BIN=.\Bin
set CMAKE=.\Dependecies\CMake\bin\cmake.exe
set CEGUIDependeciesSrc=.\Dependecies\cegui-0.8.7\cegui-dependencies\src
set CEGUIDependeciesBuild=.\Dependecies\cegui-0.8.7\cegui-dependencies\build
set CEGUISrcDependecies=.\Dependecies\cegui-0.8.7\src\dependencies\bin
mkdir %CEGUIDependeciesBuild%

%CMAKE% -DCEGUI_BUILD_EXPAT:BOOL="1" -DCEGUI_BUILD_EFFECTS11:BOOL="0" -DCEGUI_BUILD_GLFW:BOOL="0" -DCEGUI_BUILD_SILLY:BOOL="1" -S %CEGUIDependeciesSrc% -B %CEGUIDependeciesBuild%
msbuild %CEGUIDependeciesBuild%\CEGUI-DEPS.sln" /p:configuration=Debug
msbuild %CEGUIDependeciesBuild%\CEGUI-DEPS.sln" /p:configuration=Release 

mkdir %CEGUISrc%\dependencies
xcopy /y /s %CEGUIDependeciesBuild%\dependencies %CEGUISrc%\dependencies

set CEGUISrc=.\Dependecies\cegui-0.8.7\src
set CEGUIBuild=.\Dependecies\cegui-0.8.7\build
mkdir %CEGUIBuild%
%CMAKE% -DCEGUI_SAMPLES_ENABLED:BOOL="0" -DCEGUI_BUILD_XMLPARSER_EXPAT:BOOL="1" -DCEGUI_BUILD_APPLICATION_TEMPLATES:BOOL="0" -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DCEGUI_BUILD_OPENGL:BOOL="0" -DCEGUI_BUILD_IMAGECODEC_SILLY:BOOL="1" -DOGRE_LIB_DBG:FILEPATH="Dependecies\Ogre\Build\lib\Debug\OgreMain_d.lib" -DOGRE_H_PATH:PATH="Dependecies\Ogre\Src\OgreMain\include" -DOGRE_LIB:FILEPATH="Dependecies\Ogre\Build\lib\Release\OgreMain.lib" -DOGRE_H_BUILD_SETTINGS_PATH:PATH="Dependecies\Ogre\Build\include" -S %CEGUISrc% -B %CEGUIBuild%
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MAJOR 0', 'define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MINOR 0', 'define CEGUI_OGRE_VERSION_MINOR 13' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_PATCH 0', 'define CEGUI_OGRE_VERSION_PATCH 3' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"

msbuild "cegui.sln" /p:configuration=Release 
msbuild "cegui.sln" /p:configuration=Debug 

xcopy /y /s %CEGUIBuild%\bin\CEGUIBase-0.dll %Bin%
xcopy /y /s %CEGUIBuild%\bin\CEGUIBase-0_d.dll %Bin%

xcopy /y /s %CEGUIBuild%\bin\CEGUIExpatParser.dll %Bin%
xcopy /y /s %CEGUIBuild%\bin\CEGUIExpatParser_d.dll %Bin%

xcopy /y /s %CEGUIBuild%\bin\CEGUIOgreRenderer-0.dll %Bin%
xcopy /y /s %CEGUIBuild%\bin\CEGUIOgreRenderer-0_d.dll %Bin%

xcopy /y /s %CEGUIBuild%\bin\CEGUICoreWindowRendererSet.dll %Bin%
xcopy /y /s %CEGUIBuild%\bin\CEGUICoreWindowRendererSet_d.dll %Bin%

xcopy /y /s %CEGUISrcDependecies%\freetype_d.dll %Bin%
xcopy /y /s %CEGUISrcDependecies%\freetype.dll %Bin%

xcopy /y /s %CEGUISrcDependecies%\glew.dll %Bin%
xcopy /y /s %CEGUISrcDependecies%\glew_d.dll %Bin%

xcopy /y /s %CEGUISrcDependecies%\jpeg.dll %Bin%
xcopy /y /s %CEGUISrcDependecies%\jpeg_d.dll %Bin%

xcopy /y /s %CEGUISrcDependecies%\expat.dll %Bin%
xcopy /y /s %CEGUISrcDependecies%\expat_d.dll %Bin%

xcopy /y /s %CEGUISrcDependecies%\pcre.dll %Bin%
xcopy /y /s %CEGUISrcDependecies%\pcre_d.dll %Bin%