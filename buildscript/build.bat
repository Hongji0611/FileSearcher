DEL /F/Q/S build
cmake -B ./build -S ./
mingw32-make -C build
MOVE build\*.exe .