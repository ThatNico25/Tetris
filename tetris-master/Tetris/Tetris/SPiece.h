#pragma once
#include "Piece.h"

using namespace std;

/// <summary> This class manage the behavior of S piece. </summary>
class SPiece : public Piece
{
public:
	/// <summary> Constructor of SPiece </summary>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_IDColor"> const int : This is the id that will tell what color to put on the piece. </param>
	/// <param name="a_Size"> const int : This is the size of the piece.  </param>
	SPiece(const int a_x, const int a_y, const int a_IDColor, const int a_Size);

	/// <summary> Constructor of SPiece </summary>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_GridPosX"> int : This is the position in x of the piece in the grid.  </param>
	/// <param name="a_GridPosY"> int : This is the position in y of the piece in the grid.  </param>
	/// <param name="a_IDColor"> const int : This is the id that will tell what color to put on the piece. </param>
	/// <param name="a_Size"> const int : This is the size of the piece.  </param>
	SPiece(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY, const int a_IDColor, const int a_Size);

	/// <summary> Destructor of SPiece </summary>
	~SPiece();

	/// <summary> This function draw all tiles that belong to the piece. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the piece  </param>
	void Draw(SDL_Surface* a_ScreenSurface) override;

	/// <summary> This function will rotate the piece. </summary>
	/// <param name="a_angle"> int : It's in what angle the piece will be rotated.  </param>
	/// <param name="a_OffsetX"> const int : This is the offset in x of the rotation.  </param>
	/// <param name="a_OffsetY"> const int : This is the offset in y of the rotation.  </param>
	void Rotate(int a_angle, int a_OffsetX, int a_OffsetY) override;

	/// <summary> This function will move all tiles to a position given by the params. </summary>
	/// <param name="a_x"> const int : This is the position in x of the piece.  </param>
	/// <param name="a_y"> const int : This is the position in y of the piece.  </param>
	/// <param name="a_GridPosX">  const int : This is the position in x of the piece. </param>
	/// <param name="a_GridPosY"> const int : This is the position in y of the piece. </param>
	void SetPosition(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY) override;

	/// <summary> This function only return the angle of the piece </summary>
	/// <return> int : m_Angle </return>
	int GetAngle() override;

	/// <summary> This function only return the size of the offset of the piece </summary>
	/// <return> int : m_Size </return>
	int virtual GetCollisionSize();

	/// <summary> This function only return a vector of tiles of the piece </summary>
	/// <return> vector<Tiles*> : m_Tiles </return>
	vector<Tiles*> GetTiles() override;

private:
	SDL_Surface* m_Surface = nullptr; // Pointer of SDL_Surface that the piece will be draw.
	SDL_Rect* m_Rect = nullptr; // Pointer of SDL_Rect that will tell where the piece will be draw.

	vector<Tiles*> m_Tiles; // Vector of pointers of tiles that the piece contains.

	int m_IDColor; // ID that will tell which color the piece will be

	int m_Angle; // Angle of the current rotationof the peiece

	int m_Size; // Size of the offset of the piece that will check if the piece can move to its target

	int m_GridPosX; // Pos in x in the grid of the game
	int m_GridPosY; // Pos in y in the grid of the game

	/// <summary> This function will create the tile of the piece. </summary>
	/// <param name="a_x"> const int : This is the position in x of the visual of the piece. </param>
	/// <param name="a_y"> const int : This is the position in y of the visual of the piece.  </param>
	/// <param name="a_GridPosX"> int : This is the position in x of the piece in the grid.  </param>
	/// <param name="a_GridPosY"> int : This is the position in y of the piece in the grid.  </param>
	void CreatePiece(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY) override;
};