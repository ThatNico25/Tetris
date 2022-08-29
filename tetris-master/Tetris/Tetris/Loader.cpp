
#include "Loader.h"

SDL_Surface* Loader::LoadPng(const std::string& a_Path)
{
	SDL_Surface* optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(a_Path.c_str());

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", a_Path.c_str(), IMG_GetError());
	}
	else
	{
		return loadedSurface;
	}

	return nullptr;
}

SDL_Rect* Loader::CreateRect(const int a_X, const int a_Y, const int a_W, const int a_H)
{
	SDL_Rect* rect = new SDL_Rect();

	rect->x = a_X;
	rect->y = a_Y;
	rect->w = a_W;
	rect->h = a_H;

	return rect;
}
