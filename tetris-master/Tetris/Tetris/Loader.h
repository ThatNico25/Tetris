#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

/// <summary> This class manage to load image and create rectangles. </summary>
class Loader
{
public:
	/// <summary> This function will load a image png. </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	/// <return> SDL_Surface* : Return the image loaded. </return>
	static SDL_Surface* LoadPng(const std::string& a_Path);

	/// <summary> This function will create a rectangle. </summary>
	/// <param name="a_x"> const int : This is the position in x of the rectangle.  </param>
	/// <param name="a_y"> const int : This is the position in y of the rectangle.  </param>
	/// <param name="a_Width"> const int : This is the width of the rectangle . </param>
	/// <param name="a_Height"> const int : This is the height in y of the rectangle.  </param>
	/// <return> SDL_Rect* : Return a rectangle. </return>
	static SDL_Rect* CreateRect(const int a_X, const int a_Y, const int a_Width, const int a_Height);
};

