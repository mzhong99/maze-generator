# Maze Generator
Maze generator which uses graph theory algorithms to produce simple mazes in PNGs

## Overview

This maze generator can be used to generate arbitrary-size square mazes using a variety of different algorithms. These algorithms include:

- Backtracking (Simple Depth-First Search)
- Kruskal's Algorithm
- Prim's Algorithm
- Binary Trees
- Eller's Algorithm

The end result is similar, regarless of the choice of algorithm. It's a `png` of a maze which you can use for whatever you see fit. Here's some examples of how these mazes look:

| Algorithm          | Sample Result                                        | Result With Solution                                          |
| ------------------ | ---------------------------------------------------- | ------------------------------------------------------------- |
| Backtracking / DFS | <img src=image-samples/backtracking.png width=202 /> | <img src=image-samples/backtracking_solution.png width=202 /> |
| Kruskal's          | <img src=image-samples/kruskals.png     width=202 /> | <img src=image-samples/kruskals_solution.png     width=202 /> |
| Prim's             | <img src=image-samples/prims.png        width=202 /> | <img src=image-samples/prims_solution.png        width=202 /> |
| Binary Trees       | <img src=image-samples/binarytree.png   width=202 /> | <img src=image-samples/binarytree_solution.png   width=202 /> |
| Eller's            | <img src=image-samples/ellers.png       width=202 /> | <img src=image-samples/ellers_solution.png       width=202 /> |

## Installation

After downloading all of the files (you can either do this manually or through a `git pull`), you can build this program by executing the following commands in your command line:

### Windows

If you're a Windows user, I will assume you have a command-line based `CMake` and a Microsoft Visual Studio C++ Compiler. Once you have those installed, you can run the following commands to build this project:

```
cd C:\path\to\dir
mkdir build
cd build
cmake ../
cmake --build .
```

The runnable executables are located at `build\debug\maze-generator.exe` and `build\debug\unit-tests.exe`. The latter executable is useful if you would like to verify the unit tests yourself.

### Ubuntu

If you're an Ubuntu user, I will assume you have a command-line based `CMake` and GNU `g++` installed. In the event that these packages aren't installed, you can install them using:

```
sudo apt install cmake
sudo apt install g++
```

Once you have them installed, you can run the following commands to build this project:

```
cd /path/to/dir
mkdir build
cd build
cmake ../
make
```

The runnable executables are located at `build/maze-generator` and `build/unit-tests`. The latter executable is useful if you would like to verify the unit tests yourself.

## 