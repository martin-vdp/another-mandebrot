all:
	gcc main.c `sdl2-config --cflags --libs` -Wall -Werror && ./a.out
