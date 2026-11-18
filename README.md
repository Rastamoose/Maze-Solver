# Robot Maze

This program generates a random 19 × 19 maze using a recursive backtracking
algorithm implemented with an explicit stack. It draws the maze on the background
layer and animates a magenta triangular robot on the foreground layer. The robot
starts at the entrance at (0, 1), facing east, and follows the right-hand wall
until it reaches the green exit marker. A 100 ms delay between moves makes the
animation visible. Run the program again to generate another maze.

## Compile and run

Requirements: GCC (or Clang), Java, and the drawing app files supplied on Moodle.
Keep the submitted `src/` and `include/` directories together. Create a `drawapp/`
directory alongside them and place the supplied `graphics.c` and `graphics.h`
inside it. Place `drawapp-5.0.jar` alongside `src/`, `include/`, and `drawapp/`.
These drawing app files are required locally but are not included in the submission.

From that directory, compile using the Makefile (requires Make):

```sh
make
```

Or compile directly with:

```sh
gcc -Wall -Wextra -Iinclude -Idrawapp src/main.c src/maze.c src/maze_gen.c src/robot.c drawapp/graphics.c -o maze
```

Both methods create `maze` in the current directory. Run with:

```sh
./maze | java -jar drawapp-5.0.jar
```

If the JAR is named `drawapp.jar`, use that filename instead. The program runs
automatically without keyboard input or command-line arguments. No data or image
files are needed.
