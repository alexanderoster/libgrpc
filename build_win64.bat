mkdir build
cd build
cmake ..
REM cmake -DCMAKE_TOOLCHAIN_FILE=c:\vcpkg\scripts\buildsystems\vcpkg.cmake --build . --config Release 
cmake --build . --config Release 

pause