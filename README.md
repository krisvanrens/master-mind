# Master Mind
A C++20 implementation of the classic 1970s game of [Master Mind](https://en.wikipedia.org/wiki/Mastermind_(board_game)).
I will probably get to implementing this game in other languages as well.

## Description
I cooked up this game on [Godbolt](https://godbolt.org) to learn about C++20.
Alongside the codemaking-side of the game, a couple of automated solvers have been implemented.

Live initial example of the codemaker-side here: https://www.godbolt.org/z/x1KvoY

Currently the following codebreakers/solvers are available:

* Brute-force (...),
* Naive (straightforward yet pretty dumb algorithm),
* Knuth solver (see [Wikipedia](https://en.wikipedia.org/wiki/Mastermind_(board_game)) (WIP).

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

This is a command-line tool to play around with the codemaker-side, or to implement solvers in other languages than C++ that use the CLI tool for checking.

Usage information:
```
Usage: master-mind-cli [-h|--help] [--secret=SECRET] [-v|--verbose] GUESS

-h --help       Show this help info
--secret=SECRET Provide a custom secret instead of generating a random one
-v --verbose    Show guess/secret/outcome
```
E.g.:
```
$ ./master-mind-cli --secret=9001285452600931 2348761560631927                                                                                                                                  │
Secret: [9001285452600931]
Secret: [2348761560631927]
Score : [2211111111100000]
```
The return code is `0` if the score is a win, otherwise it is `1`.

## `master-mind-solver`

This is a command-line tool to test the various solvers.

Usage information
```
Usage: master-mind-solver [-h|--help] [-q|--quiet] [-v|--verbose] [--list|SOLVER]

-h --help    Show this help info
-q --quiet   Show only the number of tries needed
-v --verbose Show detailed solver output
--list       List solvers
```
E.g.:
```
$ ./master-mind-solver --list
brute-force
knuth
naive
```
or:
```
$ ./master-mind-solver brute-force
Solver 'brute-force' needed 1342 steps
```
