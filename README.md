# mapless-practice
`mapless-practice` is a small utility to generate seeds for practicing
mapless Buried Treasure, which is a strategy for Minecraft speedruns.
It makes use of the wonderful [cubiomes](http://github.com/cubitect/cubiomes)
library to do so.

This only checks for a buried treasure within a few chunks of the world
spawn. It does no filtering to ensure that there are no other nearby
structures which may show up as false positives on the pie chart.

If you need a lot of mapless practice seeds, this is far faster than
running the JustLearnTreasure filter on repl.it. Here's a demo,
running on a single core on a Ryzen 3600:

<video src="https://raw.githubusercontent.com/woofdoggo/mapless-practice/main/assets/output.mp4" width="100%">
</video>

# Building
Ensure that you have GNU make and a C compiler toolchain installed.

```
git clone https://github.com/woofdoggo/mapless-practice.git
cd mapless-practice
git submodule update --init --recursive

make CC=gcc
./out/finder
```
