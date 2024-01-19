mkdir build
cd build
cmake ..
cmake -DCMAKE_TOOLCHAIN_FILE=w:/vcpkg/scripts/buildsystems/vcpkg.cmake --build . --config Release 

pause