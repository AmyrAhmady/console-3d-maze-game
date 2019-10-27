# Console 3D Maze Game

## Information
A simple console based 3D maze game written in C++, which only works on Windows and Linux at the moment until I find a way to write buffer directly to console output with colors

## Notes
If you ever see random characters on walls instead of block characters ( █, ▓, ▒, and ░ ), try to set your project `Character Set` to Unicode instead of Multi-byte or whatever it is set to.

**Linux users: it needs root permissions to read keyboard key states so don't forget to run it with "sudo"**

## Preview
(No, preview is not laggy, it's your internet trying to load this ~6mb GIF file! it will be fine when it's finally done loading all frames.)

(Click on it, github doesn't let me have such a big file as an embed for preview..)

https://cdn.discordapp.com/attachments/466249612529893386/636653512880816128/bruh_2.gif

## Download
Well, check [Releases tab](https://github.com/AmyrAhmady/console-3d-maze-game/releases) !

## Build instruction
### Windows
- Any C++ compiler that supports std C++11
- CMake
```
git clone https://github.com/AmyrAhmady/console-3d-maze-game
cd console-3d-maze-game
mkdir build
cd build
cmake ..
```
Now you can go to `build` directory and open your project (like opening solution file if you are using Visual Studio)

### Linux
- Any C++ compiler that supports std C++11
- CMake
```
git clone https://github.com/AmyrAhmady/console-3d-maze-game
cd console-3d-maze-game
mkdir build
cd build
cmake ..
make

now do this to run the output:
cd console-3d-maze-game
sudo ./console-3d-maze-game

```
You output file will be in `console-3d-maze-game/build/console-3d-maze-game` and its called `console-3d-maze-game`