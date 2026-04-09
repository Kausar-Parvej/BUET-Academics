@echo off
REM Script to compile and run 2005076.cpp on Windows

echo Compiling 2005076.cpp...
g++ -o 2005076.exe 2005076.cpp -lm

if %errorlevel% neq 0 (
    echo.
    echo Compilation failed! Please check the error messages above.
    pause
    exit /b 1
)

echo Compilation successful!
echo.
echo Running the program...
echo.
2005076.exe

echo.
echo Program finished. Check out.txt for results.
pause
