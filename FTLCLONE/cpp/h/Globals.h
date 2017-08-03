#pragma once
#ifndef _GLOBALS_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>


//Screen dimension constants
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;

extern SDL_Renderer* gRenderer;

extern bool quit;
#endif