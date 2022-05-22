# Before Building
In the file Common.h, it might be necessary to change the 2 constants `SCREEN_WIDTH` and `SCREEN_HEIGHT`.
These constant determine how big the game window is going to be and are measured in pixels.
They should be set slightly smaller than your screens resolution to account for title bars and docks.
The default resolution of 1600x900 should be sufficient for a 1080p screen.

NOTE: You must use a 16:9 aspect ration or else the scaling will be off.


# Dependencies
This build guide will use Ubuntu 22.04, but other Linux distrobutions should work as long as the needed depenedencies are met.

The dependencies are: `g++`, `cmake` and `sfml` (with development headers)

## Installation of Dependencies on Ubuntu
First update repositories
```
$ sudo apt update
```

Install dependencies
```
$ sudo apt install g++ cmake libsfml-dev
```


# Building
Navigate to the directory that the game code is in, and then go into the `build/` directory.
Then configure with cmake, and build
```
path/to/game$ cd build
path/to/game/build$ cmake ../
path/to/game/build$ cmake --build .
```


# Running
The built executable will be placed in the `bin/` directory.

IMPORTANT: for proper execution, the game must be run with the present working directory as the `bin/` directory.
Failing to do so will result in assets, such as fonts, not loading.

To run, navigate to the `bin/` directory, then run
```
path/to/game/build$ cd ../bin
path/to/game/bin$ ./breakout
```

# Playing
## The Menu
The main menu can be navigated with the arrow keys and items can be selected using the enter key.
To escape a menu item, press the escape key.
The game can be closed either with the close button, or with ctrl+q.

## The Game
The left right arrow keys are used to control the paddle.
The ball will also change direction depending where on the paddle it hits.
If it hits the right edge, it will deflect to the right, and vice versa.
The blocks on the higher levels will give a speed boost to the ball when hit.
If a block is larger than the 2 beside it, it will be colored white and will give an additional speed boost.
The score goes up each time you hit a block, with the ammount being proportional to the speed increase.
You are given a base score of 36, with 8 points being removed each time you lose a ball.
The game finishes a bit abruptly, forwarding you directly to the high scores screen.


# Notes
I tried playing this on a virtual machine, and although it was able to run, the performance of the game was exceptionally poor.
This caused some strange physics bugs, such as the ball clipping through walls or the paddle.
These bugs are not indicative of bare-metal performance.
