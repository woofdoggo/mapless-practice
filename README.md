# mapless-practice
`mapless-practice` is a small utility to generate seeds for practicing
mapless Buried Treasure, which is a strategy for Minecraft speedruns.

The initial intent was to make this available in the form of a webpage,
but WebAssembly is somewhat painful.

# Building
Ensure that you have GNU make and a C compiler toolchain installed.

```
git clone https://github.com/woofdoggo/mapless-practice.git
cd mapless-practice
git submodule update --init --recursive

make CC=gcc
./out/finder
```
