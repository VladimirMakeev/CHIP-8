# CHIP-8 [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
A [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) emulator written in C++11 using the [SDL2 library](https://www.libsdl.org).

## Building from sources
You will need to have SDL2 headers and libraries installed as well as make utility. Run make to build:
```Shell
$ make
```

## Usage
To emulate chip-8 rom file just pass it as an argument:
```Shell
$ chip8emu /path/to/rom/file/PONG
```

## Screenshots
Pong:

![Pong](screenshots/pong.png)

Brix:

![Brix](screenshots/brix.png)

Space Invaders:

![Space Invaders](screenshots/invaders.png)
