set BIN=.\Bin
set CMAKE=.\Dependecies\CMake\bin\cmake.exe
set CEGUIDependeciesSrc=.\Dependecies\cegui-0.8.7\cegui-dependencies
set CEGUIDependeciesBuild=.\Dependecies\cegui-0.8.7\cegui-dependencies\build
set CEGUISrcDependecies=.\Dependecies\cegui-0.8.7\src\dependencies\bin
set CEGUI_CONFIG_PATH=.\Dependecies\cegui-0.8.7\build\cegui\include\CEGUI\Config.h

set CEGUISrc=.\Dependecies\cegui-0.8.7\src
set CEGUIBuild=.\Dependecies\cegui-0.8.7\build

mkdir %CEGUIDependeciesBuild%
%CMAKE% -S%CEGUIDependeciesSrc% -B%CEGUIDependeciesBuild%
msbuild %CEGUIDependeciesBuild%\CEGUI-DEPS.sln /p:configuration=Debug
msbuild %CEGUIDependeciesBuild%\CEGUI-DEPS.sln /p:configuration=Release 

mkdir %CEGUISrc%\dependencies
xcopy /y /s %CEGUIDependeciesBuild%\dependencies %CEGUISrc%\dependencies
mkdir %CEGUIBuild%
%CMAKE% -DCEGUI_SAMPLES_ENABLE_HUD_DEMO:BOOL="0" -DCEGUI_BUILD_RENDERER_OPENGL3:BOOL="0" -DCEGUI_SAMPLES_ENABLED:BOOL="0" -DCEGUI_SAMPLES_ENABLE_HELLO_WORLD_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_COMMON_DIALOGUES_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_SCROLLABLEPANE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_GAMEMENU_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_EDITBOX_VALIDATION_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DEMO6:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TABCONTROL_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_MINESWEEPER_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_LOOKNFEELOVERVIEW_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_DRAGDROP_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_WIDGET_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_INVENTORY_DEMO:BOOL="0" -DCEGUI_BUILD_RENDERER_OGRE:BOOL="1" -DCEGUI_SAMPLES_ENABLE_TREE_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_EFFECTS_DEMO:BOOL="0" -DCEGUI_BUILD_RENDERER_OPENGL:BOOL="0" -DCEGUI_BUILD_IMAGECODEC_SDL2:BOOL="0" -DCEGUI_SAMPLES_ENABLE_FONT_DEMO:BOOL="0" -DCEGUI_SAMPLES_ENABLE_TEXT_DEMO:BOOL="0"  -S %CEGUISrc% -B %CEGUIBuild%
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MAJOR 0', 'define CEGUI_OGRE_VERSION_MAJOR 1' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_MINOR 0', 'define CEGUI_OGRE_VERSION_MINOR 13' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"
powershell -command "(gc %CEGUI_CONFIG_PATH%) -replace 'define CEGUI_OGRE_VERSION_PATCH 0', 'define CEGUI_OGRE_VERSION_PATCH 3' | Out-File -encoding ASCII %CEGUI_CONFIG_PATH%"

msbuild %CEGUIBuild%\cegui.sln /p:configuration=Release 
msbuild %CEGUIBuild%\cegui.sln /p:configuration=Debug 

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
