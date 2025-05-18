# condot

During the Renaissance Era, Italy was divided into numerous independent
city-states. While bursting with trade and wealth, the city-states' growing
concern over jealous neighbors invited the rise of the Condottieri, ambitious
leaders of powerful mercenary armies.

In Condottiere, 3-6 players vie to establish their influence and control over
the cities and regions of Italy. Fight with skill and daring and use every tool
at your disposal to reshape the political and military landscape of Italy for
generations to come.

condot is an implementation of
[Condottiere](https://boardgamegeek.com/boardgame/112/condottiere) written in
C++ with [Raylib](https://raylib.com) and [OOP design](./docs/v2.pdf).

![board](./gallery/board.png)
> _View the [full gallery](./gallery)_

## How to Build

### Linux x86_64

To build the project for Linux x86_64 targets, follow the steps below:

1. Install the [development dependencies required by
   raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#dependencies).

2. Run the build with:

   ```bash
   make
   ```

   Make sure all dependencies are correctly installed before running `make`. The
   build system will compile the source files and place the output binary in the
   `./build/` directory.

3. Launch the game:

   ```bash
   ./build/condot
   ```

### WASM (Experimental)

> [!CAUTION]
> Window dimensions and the **save** feature _won't_ work in the WASM build.

To build the project for WASM targets, follow the steps below:

1. Install the [development dependencies required by
   raylib](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#dependencies).

2. Modify [src/main.cpp](./src/main.cpp) and initialize the window with a fixed
   size such as 1920x1080 based on your display size and HiDPI scaling:

   ```diff
   -int m = GetCurrentMonitor();
   -InitWindow(GetMonitorWidth(m), GetMonitorHeight(m), "Condottiere");
   +InitWindow(1920, 1080, "Condottiere");
   ```

3. Run the build with:

   ```bash
   ./scripts/build-wasm.sh
   ```

   This will generate the essential files at `./build` for running the game in a browser.

4. Serve the build files using a tool like Python's http module:

   ```bash
   python3 -m http.server 8080
   ```

5. Head over to [localhost:8080/build/condot.html](http://localhost:8080/build/condot.html) and play!

## How to Play

See [docs/rules.pdf](./docs/rules.pdf).

## License

This project is licensed under the [MIT license](./LICENSE), except for
[docs/rules.pdf](./docs/rules.pdf) which has its own licensing.
