@echo off
REM ─────────────────────────────────────────────────────────────────────────────
REM  run.bat  —  Build and run the multi-teller bank simulation
REM
REM  Requirements: g++ (MinGW or similar) must be on PATH
REM ─────────────────────────────────────────────────────────────────────────────

echo.
echo [1/2] Compiling...
g++ -std=c++17 -O2 -Wall -o mtbank.exe simlib.cpp mtbank.cpp

IF %ERRORLEVEL% NEQ 0 (
    echo.
    echo Compilation FAILED. Check the errors above.
    pause
    exit /b 1
)

echo Compilation successful.
echo.
echo [2/2] Running simulation...
mtbank.exe
echo Output file: mtbank.out
echo.
pause
