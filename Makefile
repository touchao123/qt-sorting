


all:
	gcc window.c `sdl2-config --libs --cflags`
