[![Build Status](https://travis-ci.org/bsamseth/ricefish.svg?branch=master)](https://travis-ci.org/bsamseth/ricefish)
[![Coverage Status](https://coveralls.io/repos/github/bsamseth/ricefish/badge.svg?branch=master)](https://coveralls.io/github/bsamseth/ricefish?branch=master)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/bsamseth/ricefish/blob/master/LICENCE)
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](http://www.repostatus.org/badges/latest/active.svg)](http://www.repostatus.org/#active)

# Ricefish
###### Stockfish's distant Chinese cousin


This is a "UCI" Chinese checkers engine. UCI is normally the _Universal Chess Interface_. This interface is implemented 
exactly the same as for regular chess, with some notable exception:

- Moves are encoded as `(from.row,from.col),(to.row,to.col)`, with no spaces. In chess you would say e.g. `e2e4`, but here you say e.g. `(13,5),(5,13)`.
- There is currently no support for specifying a position directly (like with FEN notation in chess). You specify a position by the starting position and the subsequent moves. This will likely be implemented sometime soon(ish).


The current version is based heavily on
[bsamseth/goldfish](https://github.com/bsamseth/goldfish).   

This is meant as a project to work on just for the fun of it.
Contributions are welcome if you feel like it.

## Build

The project is built using CMake, which hopefully makes this as portable as
possible. Recommend building in a separate directory:

``` bash
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make
```

After the compiling is done you should have two executables in the build
directory: `ricefish` and `unit_tests.x`. The former is the interface to the
engine it self.

## Run

You can play using the UCI interface directly, although this is a bit tedious. A playing script is in the works.
For now, here's a short example of how to play with the engine (lines starting with `>` are the commands entered):

``` text
terminal $ build/ricefish.x
> uci
id name Ricefish v0.1
id author Bendik Samseth
uciok
> isready
readyok
> position startpos
> print
 0|
 1|                          x
 2|                        x x
 3|                      x x x
 4|                    x x x x
 5|          . . . . . . . . . . . . .
 6|          . . . . . . . . . . . .
 7|          . . . . . . . . . . .
 8|          . . . . . . . . . .
 9|          . . . . . . . . .
 :|        . . . . . . . . . .
 ;|      . . . . . . . . . . .
 <|    . . . . . . . . . . . .
 =|  . . . . . . . . . . . . .
 >|          + + + +
 ?|          + + +
 @|          + +
 A|          +
 B|
   --------------------------------------
   0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B
> go movetime 3000
info depth 1 seldepth 0 nodes 0 time 1538727497146 nps 0
info depth 1 seldepth 1 nodes 2 time 0 nps 0 score cp 2 pv (3,11),(5,11)
info depth 2 seldepth 2 nodes 31 time 0 nps 0 score cp 0 pv (3,11),(5,11) (15,5),(13,5)
info depth 3 seldepth 3 nodes 113 time 0 nps 0 score cp 4 pv (3,11),(5,11) (15,5),(13,5) (1,13),(5,9)
info depth 4 seldepth 4 nodes 898 time 1 nps 0 score cp 0 pv (3,11),(5,11) (15,5),(13,5) (1,13),(5,9) (17,5),(13,7)
info depth 5 seldepth 5 nodes 6305 time 8 nps 0 score cp 3 pv (3,11),(5,11) (15,5),(13,5) (5,11),(6,11) (17,5),(13,7) (1,13),(7,11)
info depth 6 seldepth 6 nodes 86471 time 82 nps 0 score cp 0 pv (3,11),(5,11) (15,5),(13,5) (5,11),(6,11) (13,5),(12,5) (1,13),(7,11) (17,5),(11,5)
info depth 7 seldepth 7 nodes 650297 time 526 nps 0 score cp 4 pv (3,11),(5,11) (15,5),(13,5) (4,11),(5,10) (13,5),(12,5) (2,13),(6,9) (17,5),(11,5) (1,13),(7,9)
info depth 8 seldepth 8 nodes 1990626 time 1526 nps 1304473 currmove (3,11),(5,11) currmovenumber 1
info depth 8 seldepth 8 nodes 2972413 time 2526 nps 1176727 currmove (3,11),(5,11) currmovenumber 1
info depth 8 seldepth 8 nodes 3479826 time 3005 nps 1158011 currmove (3,11),(5,11) currmovenumber 1
bestmove (3,11),(5,11) ponder (15,5),(13,5)
> position startpos moves (3,11),(5,11)
> print
 0|
 1|                          x
 2|                        x x
 3|                      . x x
 4|                    x x x x
 5|          . . . . . . x . . . . . .
 6|          . . . . . . . . . . . .
 7|          . . . . . . . . . . .
 8|          . . . . . . . . . .
 9|          . . . . . . . . .
 :|        . . . . . . . . . .
 ;|      . . . . . . . . . . .
 <|    . . . . . . . . . . . .
 =|  . . . . . . . . . . . . .
 >|          + + + +
 ?|          + + +
 @|          + +
 A|          +
 B|
   --------------------------------------
   0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B
> go movetime 1000
info depth 1 seldepth 0 nodes 0 time 32077 nps 0
info depth 1 seldepth 1 nodes 2 time 0 nps 0 score cp 0 pv (15,5),(13,5)
info depth 2 seldepth 2 nodes 44 time 0 nps 0 score cp -4 pv (15,5),(13,5) (1,13),(5,9)
info depth 3 seldepth 3 nodes 153 time 0 nps 0 score cp 0 pv (15,5),(13,5) (1,13),(5,9) (17,5),(13,7)
info depth 4 seldepth 4 nodes 2059 time 2 nps 0 score cp -3 pv (15,5),(13,5) (5,11),(6,11) (17,5),(13,7) (1,13),(7,11)
info depth 5 seldepth 5 nodes 14948 time 15 nps 0 score cp 0 pv (15,5),(13,5) (5,11),(6,11) (13,5),(12,5) (1,13),(7,11) (17,5),(11,5)
info depth 6 seldepth 6 nodes 179022 time 140 nps 0 score cp -4 pv (15,5),(13,5) (4,11),(5,10) (13,5),(12,5) (2,13),(6,9) (17,5),(11,5) (1,13),(7,9)
info depth 7 seldepth 7 nodes 1103351 time 1003 nps 1100050 currmove (15,5),(13,5) currmovenumber 1
bestmove (15,5),(13,5) ponder (4,11),(5,10)
> position startpos moves (3,11),(5,11) (15,5),(13,5)
> print
 0|
 1|                          x
 2|                        x x
 3|                      . x x
 4|                    x x x x
 5|          . . . . . . x . . . . . .
 6|          . . . . . . . . . . . .
 7|          . . . . . . . . . . .
 8|          . . . . . . . . . .
 9|          . . . . . . . . .
 :|        . . . . . . . . . .
 ;|      . . . . . . . . . . .
 <|    . . . . . . . . . . . .
 =|  . . . . + . . . . . . . .
 >|          + + + +
 ?|          . + +
 @|          + +
 A|          +
 B|
   --------------------------------------
   0 1 2 3 4 5 6 7 8 9 : ; < = > ? @ A B
```
