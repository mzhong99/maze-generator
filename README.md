# Maze Generator
Maze generator which uses graph theory algorithms to produce simple mazes in PNGs

## Overview

This maze generator can be used to generate arbitrary-size square mazes using a variety of different algorithms. These algorithms include:

- Backtracking (Simple Depth-First Search)
- Kruskal's Algorithm
- Prim's Algorithm
- Binary Trees
- Eller's Algorithm

The end result is similar, regardless of the choice of algorithm. It's a `png` of a maze which you can use for whatever you see fit. Here's some examples of how these mazes look:

| Algorithm          | Sample Result                                        | Result With Solution                                          |
| ------------------ | ---------------------------------------------------- | ------------------------------------------------------------- |
| Backtracking / DFS | <img src=image-samples/backtracking.png width=202 /> | <img src=image-samples/backtracking_solution.png width=202 /> |
| Kruskal's          | <img src=image-samples/kruskals.png     width=202 /> | <img src=image-samples/kruskals_solution.png     width=202 /> |
| Prim's             | <img src=image-samples/prims.png        width=202 /> | <img src=image-samples/prims_solution.png        width=202 /> |
| Binary Trees       | <img src=image-samples/binarytree.png   width=202 /> | <img src=image-samples/binarytree_solution.png   width=202 /> |
| Eller's            | <img src=image-samples/ellers.png       width=202 /> | <img src=image-samples/ellers_solution.png       width=202 /> |

## Installation

After downloading all of the files (you can either do this manually or through a `git pull`), you can build this program by executing the following commands in your command line:

#### Windows

If you're a Windows user, I will assume you have a command-line based `CMake` and a Microsoft Visual Studio C++ Compiler. Once you have those installed, you can run the following commands to build this project:

```
cd C:\path\to\dir
mkdir build
cd build
cmake ../
cmake --build .
```

The runnable executables are located at `build\debug\maze-generator.exe` and `build\debug\unit-tests.exe`. The latter executable is useful if you would like to verify the unit tests yourself.

#### Ubuntu

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

## Usage

When running this application without any arguments, you'll see the following:

Windows: `maze-generator.exe`

Ubuntu: `./maze-generator`

Output:

```
Usage: ./maze-generator <algorithm> <output_name>
Usage: ./maze-generator <width> <height> <algorithm> <output_name>
```

There are several important command line arguments this program needs to accept to generate a maze. Here are the arguments:

- **(Required)**`<algorithm>` determines which algorithm will be used to generate the maze. A list of algorithms this generator supports includes:
    - `eller`
    - `ellers`
    - `tree`
    - `binary_tree`
    - `prim`
    - `prims`
    - `dfs`
    - `DFS`
    - `backtracker`
    - `kruskal`
    - `kruskals`
- **(Required)**`<output_name>` determines the base filename into which this program will output the maze.
- **(Optional)**`<width>` and `<height>` respectively will set the width and height of the maze. Note that the resolution of the image generated has the dimensions of `2w + 1` by `2h + 1` where `w` and `h` are width and height, respectively. Should you choose not to enter a custom width and height, the default values will make a `w=10` and `h=10` grid (resolution of `21x21`).

Here's an example of how I ran this program to generate a maze using the `Binary Tree` algorithm of size `50x50` and save the **unsolved** maze to `binarymaze.png` and the **solved** maze to `binarymaze_solution.png`:

Windows: `maze-generator.exe 50 50 tree binarymaze`

Ubuntu: `./maze-generator 50 50 tree binarymaze`

Output:

```
Maze Generator with attributes:
    Width:  101
    Height: 101
Printing completed!
Problem Image: binarymaze.png
Solution Image: binarymaze_solution.png
```

## Properties of Mazes

Depending on the algorithm you choose to use, your maze will have certain biases which make them either easier or harder to solve. In particular, the biases include:

- Backtracking: Long, winding passages. Fewer dead ends.
- Prim's, Kruskal's, and Eller's: A decent balance of dead ends and actual paths. The mazes may feel more erratic in terms of which paths actually feel like dead ends.
- Binary Tree: Heavy diagonal bias. It's possible to solve a binary tree by only moving right and down. If you imagine the root of this tree as planted on the top-left corner of the map, moving right and down corresponds to traversing a branch of the binary tree.

## For more information...

I made this generator from the algorithms discussed in http://weblog.jamisbuck.org and http://www.jamisbuck.org/presentations/rubyconf2011/index.html. A special thank you to Jamis Buck for a great discussion of these algorithms.
