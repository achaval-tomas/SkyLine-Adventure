# SkyLine-Adventure
My first 2D platformer game in C++ using SDL and related libraries.

Code might not be the best, this was my first ever project in C++.

The game is Speedrun oriented. The goal is to Collect all coins and get to the finish platform alive as fast as possible. There are 3 levels of difficulty and 2 cities to be played in.

Play with
````
g++ -o play -I include src/*.cpp \`sdl2-config --cflags --libs\` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
./play
````

Some gameplay:

https://github.com/achaval-tomas/SkyLine-Adventure/assets/134091945/63c47894-4c3a-4080-850d-d363b1b2f02a

Install necessary libraries:
````
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
````
