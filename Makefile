FILES = finder.c \
		cubiomes/biome_tree.c \
		cubiomes/finders.c \
		cubiomes/generator.c \
		cubiomes/layers.c \
		cubiomes/noise.c \
		cubiomes/util.c

finder:
	mkdir -p out
	$(CC) -lm -O3 -o out/finder -I cubiomes $(FILES) $(CFLAGS)
