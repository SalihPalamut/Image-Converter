md Build
gcc.exe -c "Src\main.c" -o main.o
gcc.exe -c "Src\Sources\bitmap.c" -o bitmap.o
g++.exe  -o Build\image_converter.exe main.o bitmap.o
del main.o
del bitmap.o   
