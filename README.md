# Master Mind
A C++20 implementation of the classic 1970s game of [Master Mind](https://en.wikipedia.org/wiki/Mastermind_(board_game)).

## Description
I wacked up this game on [Godbolt](https://godbolt.org), and will be extending it gradually to learn about C++20.
The codemaker-side of the game is done, and I will probably get into writing a (semi-intelligent/non-stupud) solver as well.

Live initial example here: https://www.godbolt.org/z/x1KvoY

## Requirements

* Conan
* GCC v10 or higher
* Clang-format v10 or higher

## Building instructions

```sh
mkdir build
ccmake -S . -B ./build/
cd build
make
```

## `master-mind-cli`

This is a command-line tool to play around with the codemake-side:
```
Usage: master-mind-cli [-h|--help] [--secret=SECRET] [-v|--verbose] GUESS

-h --help       Show this help info
--secret=SECRET Provide a custom secret instead of generating a random one
-v --verbose    Show guess/secret/outcome
```
E.g.:
```
$ master-mind-cli --secret=9001285452600931 2348761560631927                                                                                                                                  │
Secret: [9001285452600931]
Secret: [2348761560631927]
Score : [2211111111100000]
```
