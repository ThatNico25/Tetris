#pragma once
#include <SDL.h>
#include <string>

/// <summary> This class manage the background  </summary>
class Background
{
public:
	/// <summary> Constructor of IPiece </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	Background(const std::string& a_Path);

	/// <summary> Destructor of Background </summary>
	~Background();

	/// <summary> This function draw all tiles that belong to the piece. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the background.  </param>
	void Draw(SDL_Surface* a_ScreenSurface);

private:
	SDL_Surface* m_Surface = nullptr; // Pointer of SDL_Surface that the background will be draw.
};

