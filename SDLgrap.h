#ifndef GRAP_H
#define GRAP_H

#include <stdio.h>
#include "SDL2/SDL.h"

void resetCol();
void clear();
void begin();
void end();
void gsleep(int sleep);
void textOut(int x, int y, char *text);
int MouseButt();
int MouseX();
int MouseY();
void boxColor();

void init(int x, int y)
{
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	else {
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN);
		if (window == NULL) printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		else {
			//screenSurface = SDL_GetWindowSurface(window);
			//SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
			//SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	/*txCreateWindow(x, y, true);
	txTextCursor(false);
	resetCol();
	txClear();*/
}

void resetCol()
{
	//txSetFillColour(RGB(50, 50, 50));
	//txSetColor(TX_WHITE, 1);
}

void boxColor() {
	//txSetFillColour(RGB(50, 50, 50));
	//txSetColor(TX_WHITE, 3);
}

void clear() { }//txClear(); }
void begin() { }//txBegin(); }
void end() { }//txEnd(); }
void gsleep(int sleep) { }//txSleep(sleep); }
void textOut(int x, int y, char *text) { }//txTextOut(x, y, text); }
int MouseButt() { return -1; }//txMouseButtons(); }
int MouseX() { return -1; }//txMouseX(); }
int MouseY() { return -1; }//txMouseY(); }

#endif
