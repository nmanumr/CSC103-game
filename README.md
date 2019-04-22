# Tic Tac Toe

Tic Tac Toe game written in pure C with computer autoplayer support. Tested with `gcc 8.3.0` on `Ubuntu 18.10`. This should work on all bash terminals, but only tested on `xtermjs`, `konsole`, `gnome-terminal`.

## Compiling & Running 

```
# Compiling & running game
make run

# Compile
make compile
```

## Autoplay Algorithm

Currently this only works for 3x3 boards but little optimization can make it work for nxn boards also. There are two techinques we use depending on the situation.

1. Corner First (when center is occupied by oponent)
2. Side First (when center is occupied by computer)

### Corner First

This techinques goes something like following:

1. If player has only one missing in row, col or diagonal mark the missing one.
2. Take center if possible
3. Take opposite empty corner of your oppoennt if any
4. Take any of the empty corner if any
5. Take empty side if any

### Side First

This techinques is also very similar to Corner First but with a little order shift.

1. If player has only one missing in row, col or diagonal mark the missing one.
2. Take center if possible
3. Take empty side if any
4. Take opposite empty corner of your oppoennt if any
5. Take any of the empty corner if any

## TODO

* [ ] Refector code to seperate rendering, game and autoplyaer logic from `include/Game.h`
* [ ] Autoplayer support for `nxn` boards
* [ ] (TBD) move to `ncurses` lib

## ScreenShots

![Board Size 5](/ScreenShots/1.png?raw=true)
![Won](/ScreenShots/2.png?raw=true)
![Draw](/ScreenShots/3.png?raw=true)
