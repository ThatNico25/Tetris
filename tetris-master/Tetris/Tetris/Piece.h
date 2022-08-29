#pragma once
#include <SDL.h>
#include <string>
#include <vector>

#include "Tiles.h"

using namespace std;

/// <summary> This class manage the behavior of each piece. The class Piece is an abstract class that will be used by the childrens of Piece. </summary>
class Piece
{
public:
	/// <summary> This function draw all tiles that belong to the piece. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the piece  </param>
	void virtual Draw(SDL_Surface* a_ScreenSurface) = 0;

	/// <summary> This function will rotate the piece. </summary>
	/// <param name="a_angle"> int : It's in what angle the piece will be rotated.  </param>
	/// <param name="a_OffsetX"> const int : This is the offset in x of the rotation.  </param>
	/// <param name="a_OffsetY"> const int : This is the offset in y of the rotation.  </param>
	void virtual Rotate(int a_angle, int a_OffsetX, int a_OffsetY) = 0;

	/// <summary> This function will move all tiles to a position given by the params. </summary>
	/// <param name="a_x"> const int : This is the position in x of the piece.  </param>
	/// <param name="a_y"> const int : This is the position in y of the piece.  </param>
	/// <param name="a_GridPosX">  const int : This is the position in x of the piece. </param>
	/// <param name="a_GridPosY"> const int : This is the position in y of the piece. </param>
	void virtual SetPosition(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY) = 0;

	/// <summary> This function only return the angle of the piece </summary>
	/// <return> int : m_Angle </return>
	int virtual GetAngle() = 0;

	/// <summary> This function only return the size of the offset of the piece </summary>
	/// <return> int : m_Size </return>
	int virtual GetCollisionSize() = 0;

	/// <summary> This function only return a vector of tiles of the piece </summary>
	/// <return> vector<Tiles*> : m_Tiles </return>
	vector<Tiles*> virtual GetTiles() = 0;

protected:
	/// <summary> This function will create the tile of the piece. </summary>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_GridPosX"> int : This is the position in x of the piece in the grid.  </param>
	/// <param name="a_GridPosY"> int : This is the position in y of the piece in the grid.  </param>
	void virtual CreatePiece(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY) = 0;
};