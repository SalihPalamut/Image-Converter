rm -rf Build
mkdir Build
gcc -c -finput-charset=windows-1254 Src/main.c -o main.o
gcc -c -finput-charset=windows-1254 Src/Sources/bitmap.c -o bitmap.o
g++ -o Build/image_converter main.o bitmap.o
rm main.o
rm bitmap.o   
