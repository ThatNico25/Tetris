#pragma once
#include <SDL.h>
#include <string>

/// <summary> This class is manage the tiles </summary>
class Tiles
{
public:

	/// <summary> Constructor of Tiles </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_sizeX"> const int : It's the size of the visual in x  </param>
	/// <param name="a_sizeY"> const int : It's the size of the visual in y   </param>
	Tiles(const std::string& a_Path, const int a_x, const int a_y, const int a_sizeX, const int a_sizeY);

	/// <summary> Constructor of Tiles </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_sizeX"> const int : It's the size of the visual in x  </param>
	/// <param name="a_sizeY"> const int : It's the size of the visual in y   </param>
	/// <param name="a_GridPosX"> int : This is the position in x of the piece in the grid.  </param>
	/// <param name="a_GridPosY"> int : This is the position in y of the piece in the grid.  </param>
	Tiles(const std::string& a_Path, const int a_x, const int a_y, const int a_sizeX, const int a_sizeY, int a_GridPosX, int a_GridPosY);

	/// <summary> Destructor of Tiles </summary>
	~Tiles();

	/// <summary> This function draw the tile. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the tile  </param>
	void Draw(SDL_Surface* a_ScreenSurface);

	/// <summary> This function will set the postion of the tiles. (Grid position) </summary>
	/// <param name="a_x"> int : This is the position in x of the piece in the grid.  </param>
	/// <param name="a_y"> int : This is the position in y of the piece in the grid.  </param>
	void SetGridPosition(const int a_x, const int a_y);

	/// <summary> This function will return the x position in the grid. </summary>
	/// <return> int : m_GridPosX </return>
	int GetGridPosX();

	/// <summary> This function will return the y position in the grid. </summary>
	/// <return> int : m_GridPosY </return>
	int GetGridPosY();

private:
	SDL_Surface* m_Surface = nullptr; // Pointer of SDL_Surface that the tile will be draw.
	SDL_Rect* m_Rect = nullptr; // Pointer of SDL_Rect that will tell where the tile will be draw.

	int m_GridPosX; // Pos in x in the grid of the game
	int m_GridPosY; // Pos in y in the grid of the game
};

