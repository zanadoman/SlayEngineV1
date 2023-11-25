#include <stdio.h>
#include "inc/SDL.h"

#undef main

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	printf("Hello World!\n");

	return 0;
}