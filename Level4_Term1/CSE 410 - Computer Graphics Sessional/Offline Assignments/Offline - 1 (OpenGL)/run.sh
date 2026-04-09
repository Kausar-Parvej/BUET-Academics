g++ main.cpp -o demo.exe -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ "Demo Class Codes\main_3D.cpp" -o demo.exe -lfreeglut -lglew32 -lopengl32 -lglu32
g++ trial.cpp -o trial.exe -lfreeglut -lglew32 -lopengl32 -lglu32 

g++ analog_clock.cpp -o clock.exe -lfreeglut -lglew32 -lopengl32 -lglu32
g++ camera_ball.cpp -o camera_ball.exe -lfreeglut -lglew32 -lopengl32 -lglu32

start demo.exe
start "Demo Executables\clockdemo.exe"
start "Demo Executables\balldemo.exe"
start clock.exe
start camera_ball.exe
start trial.exe