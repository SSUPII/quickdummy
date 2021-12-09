# quickdummy
A command line tool to create dummy dinary files.
Can be used if other software needs a raw, empty file to begin working like emulated memory cards or images, or any case where a file of specific size is needed.

## Compiling
### Linux
Make sure your C++ compiler is installed.
To be sure (on **Debian**):
```
sudo apt-get install build-essentials
```
Compile using
```
g++ -Wall ./src/*.cpp -o quickdummy
```
### Windows
MSYS2:
```
g++ -Wall ./src/*.cpp -o quickdummy.exe -static -static-libgcc -static-libstdc++ -m32
```
Or invocating base MinGW instead. This program only needs standard libraries.
Omit ```-m32``` to compile 64-bit instead.
