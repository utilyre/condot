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

## Build

### Linux x86_64

To build condot on Linux, you will need to install
[Raylib's dependencies](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux#dependencies)
for your specific distribution.

Then simply run `make` while you are at the root of this project and run the game like so:

```bash
./build/condot
```

### WASM (Experimental)

## How to Play

See [docs/rules.pdf](./docs/rules.pdf).

## License

This project is licensed under the [MIT license](./LICENSE), except for
[docs/rules.pdf](./docs/rules.pdf) which has its own licensing.
