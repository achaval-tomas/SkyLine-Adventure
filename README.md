# SkyLine-Adventure
My first 2D platformer game in C++ using SDL and related libraries.

Code might not be the best, this was my first ever project in C++. Feel free to contribute improvements via Pull Requests.

The game is Speedrun oriented. The goal is to Collect all coins and get to the finish platform alive as fast as possible. There are 3 levels of difficulty and 2 cities to be played in.

Play with (Windows)
````
start bin/release/main
````
Compile with
````
g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I /bin/release && g++ *.o -o bin/release/main -s -L /bin/release -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
````

Some gameplay:

https://github.com/achaval-tomas/SkyLine-Adventure/assets/134091945/63c47894-4c3a-4080-850d-d363b1b2f02a

**Necessary Libraries are included in bin/release. If this doesn't work for you, you may need to [Download and install SDL](https://www.libsdl.org/) and/or [mingw](https://www.mingw-w64.org/)**
