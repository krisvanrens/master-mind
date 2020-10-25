# Master Mind
A C++20 implementation of the classic 1970s game of [Master Mind](https://en.wikipedia.org/wiki/Mastermind_(board_game)).

## Description
I wacked up this game on [Godbolt](https://godbolt.org), and will be extending it gradually to learn about C++20.
The codemaker-side of the game is done, and I will probably get into writing a (semi-intelligent/non-stupud) solver as well.

Live initial example here: https://www.godbolt.org/z/x1KvoY

## Requirements

* Conan
* GCC-10 or higher

## Building instructions

```sh
mkdir build
ccmake -S . -B ./build/
cd build
make
```
