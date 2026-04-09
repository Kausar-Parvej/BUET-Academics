g++ my_b1.cpp -o my_b1.exe -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ my_a1.cpp -o my_a1.exe -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ my_a2.cpp -o my_a2.exe -lfreeglut -lglew32 -lopengl32 -lglu32 

start my_b1.exe
start my_a1.exe
start my_a2.exe



start "A1\wave_gen.exe"
start "A2+B2\july2023-A2-B2.exe"
start "B1\rotating_circles.exe"


start "tias\circles.exe"
start "tias\nagordola.exe"
start "tias\wave.exe"

start "sadi\a1.exe"
start "sadi\b1.exe"

start riha_a2.exe


g++ "tias\circles.cpp" -o "tias\circles.exe" -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ "tias\nagordola.cpp" -o "tias\nagordola.exe" -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ "tias\wave.cpp" -o "tias\wave.exe" -lfreeglut -lglew32 -lopengl32 -lglu32 

g++ "sadi\a1_19_online.cpp" -o "sadi\a1.exe" -lfreeglut -lglew32 -lopengl32 -lglu32 
g++ "sadi\b1_19_online.cpp" -o "tias\b1.exe" -lfreeglut -lglew32 -lopengl32 -lglu32 

g++ 19_A2_B2_fariha.cpp -o riha_a2.exe -lfreeglut -lglew32 -lopengl32 -lglu32 






