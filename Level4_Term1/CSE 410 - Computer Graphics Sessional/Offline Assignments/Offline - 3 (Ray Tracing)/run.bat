@echo off
setlocal

REM Compile student source files
 g++ -std=c++14 -c 2005076_classes.cpp -o classes.o
 if ERRORLEVEL 1 (
     echo Compilation of 2005076_classes.cpp failed.
     pause
     exit /b 1
 )

 g++ -std=c++14 -c 2005076_main.cpp -o main.o
 if ERRORLEVEL 1 (
     echo Compilation of 2005076_main.cpp failed.
     pause
     exit /b 1
 )

REM Link executable without workspace references
 g++ -std=c++14 classes.o main.o -o main.exe -lfreeglut -lglew32 -lopengl32 -lglu32
 if ERRORLEVEL 1 (
     echo Linking failed.
     pause
     exit /b 1
 )

echo Running main.exe...
 main.exe
 pause