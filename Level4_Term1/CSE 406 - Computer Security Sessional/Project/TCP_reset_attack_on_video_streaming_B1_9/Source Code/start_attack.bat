@echo off
REM TCP Reset Attack - Quick Start Script
REM BUET CSE406 Computer Security Sessional
REM Educational Purpose Only

echo ===================================================================
echo                    TCP Reset Attack Tool
echo                 BUET CSE406 Security Project
echo ===================================================================
echo.
echo WARNING: Educational and Authorized Testing ONLY
echo Unauthorized use is ILLEGAL and may violate security laws
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorLevel% neq 0 (
    echo ERROR: This tool requires administrator privileges
    echo Please right-click and "Run as Administrator"
    pause
    exit /b 1
)

echo ✓ Running with administrator privileges
echo.

REM Check if Python is installed
python --version >nul 2>&1
if %errorLevel% neq 0 (
    echo ERROR: Python is not installed or not in PATH
    echo Please install Python 3.7+ from https://python.org
    pause
    exit /b 1
)

echo ✓ Python is available
echo.

REM Run setup if needed
if not exist "logs" (
    echo Running initial setup...
    python setup.py
    if %errorLevel% neq 0 (
        echo Setup failed!
        pause
        exit /b 1
    )
    echo.
)

REM Menu system
:menu
echo ===================================================================
echo                        Main Menu
echo ===================================================================
echo.
echo 1. Run Network Discovery
echo 2. Start TCP Reset Attack (Interactive)
echo 3. Start Attack with Custom Config
echo 4. View Configuration
echo 5. Exit
echo.
set /p choice="Select option (1-5): "

if "%choice%"=="1" goto discovery
if "%choice%"=="2" goto attack
if "%choice%"=="3" goto custom_attack
if "%choice%"=="4" goto view_config
if "%choice%"=="5" goto exit

echo Invalid option. Please try again.
echo.
goto menu

:discovery
echo.
echo Starting Network Discovery...
python scripts\network_discovery.py
echo.
pause
goto menu

:attack
echo.
echo Starting TCP Reset Attack...
echo Press Ctrl+C to stop the attack gracefully
echo.
python src\tcp_reset_attack.py
echo.
pause
goto menu

:custom_attack
echo.
set /p config_file="Enter configuration file path: "
if not exist "%config_file%" (
    echo Configuration file not found!
    pause
    goto menu
)
echo.
echo Starting TCP Reset Attack with custom configuration...
python src\tcp_reset_attack.py --config "%config_file%"
echo.
pause
goto menu

:view_config
echo.
echo Current Configuration:
echo ===================================================================
type config\attack_config.ini
echo ===================================================================
echo.
pause
goto menu

:exit
echo.
echo Exiting TCP Reset Attack Tool
echo Remember to use responsibly and only on authorized networks!
echo.
pause
exit /b 0
