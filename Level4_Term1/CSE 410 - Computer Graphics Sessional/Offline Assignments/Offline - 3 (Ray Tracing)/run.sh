g++ -std=c++14 -c 2005076_classes.cpp -o classes.o
g++ -std=c++14 -c 2005076_main.cpp -o main.o
g++ -std=c++14 classes.o main.o -o main.exe -lfreeglut -lglew32 -lopengl32 -lglu32
./main.exe



# .\run.bat
