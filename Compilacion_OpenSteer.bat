::CMAKE OpenSteer
set cmake=.\Dependecies\CMake\bin\cmake.exe
set OpenSteerBuild=.\Dependecies\OpenSteer\Build
set OpenSteerSrc=.\Dependecies\OpenSteer\src
mkdir %OpenSteerBuild%
%cmake% -DBUILD_HACD_EXTRA:BOOL="0" -DBUILD_CLSOCKET:BOOL="0" -DBUILD_UNIT_TESTS:BOOL="0" -DINSTALL_CMAKE_FILES:BOOL="0" -DBUILD_BULLET_ROBOTICS_GUI_EXTRA:BOOL="0" -DBUILD_ENET:BOOL="0" -DENABLE_VHACD:BOOL="0" -DUSE_GLUT:BOOL="0" -DUSE_MSVC_DISABLE_RTTI:BOOL="0" -DUSE_MSVC_FAST_FLOATINGPOINT:BOOL="0" -DBUILD_OBJ2SDF_EXTRA:BOOL="0" -DBUILD_EXTRAS:BOOL="0" -DUSE_GRAPHICAL_BENCHMARK:BOOL="0" -DUSE_MSVC_STRING_POOLING:BOOL="0" -DBUILD_GIMPACTUTILS_EXTRA:BOOL="0" -DUSE_SOFT_BODY_MULTI_BODY_DYNAMICS_WORLD:BOOL="0" -DBUILD_OPENGL3_DEMOS:BOOL="0" -DBUILD_SERIALIZE_EXTRA:BOOL="0" -DBUILD_INVERSE_DYNAMIC_EXTRA:BOOL="0" -DBUILD_CPU_DEMOS:BOOL="0" -DBUILD_BULLET2_DEMOS:BOOL="0" -DBUILD_BULLET3:BOOL="0" -DBUILD_BULLET_ROBOTICS_EXTRA:BOOL="0" -DUSE_MSVC_FUNCTION_LEVEL_LINKING:BOOL="0" -DBUILD_CONVEX_DECOMPOSITION_EXTRA:BOOL="0" -DUSE_MSVC_COMDAT_FOLDING:BOOL="0" -DUSE_MSVC_RUNTIME_LIBRARY_DLL:BOOL="1" -S %OpenSteerSrc% -B %OpenSteerBuild% 

msbuild %OpenSteerBuild%\ALL_BUILD.vcxproj /p:configuration=Debug   
msbuild %OpenSteerBuild%\ALL_BUILD.vcxproj /p:configuration=Release 
