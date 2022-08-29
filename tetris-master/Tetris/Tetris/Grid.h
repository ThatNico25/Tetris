#pragma once
#include <SDL.h>
#include <SDL_TTF.h>
#include <string>
#include <vector>

#include "Piece.h"
#include "IPiece.h"
#include "OPiece.h"
#include "TPiece.h"
#include "JPiece.h"
#include "LPiece.h"
#include "SPiece.h"
#include "ZPiece.h"

#include "Tiles.h"

using namespace std;

/// <summary> Mangage the grid </summary>
class Grid
{
public:
	/// <summary> Constructor of Grid </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	Grid(const std::string& a_Path);

	/// <summary> Destructor of Grid </summary>
	~Grid();

	/// <summary> Update the grid. </summary>
	void Update();

	/// <summary> This function draw the grid of tetris. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the grid </param>
	void Draw(SDL_Surface* a_ScreenSurface);

	/// <summary> Spawn a piece </summary>
	void SpawnPiece();

	/// <summary> Horizontal movevements on the falling piece </summary>
	/// <param name="a_MoveDir"> int : Direction </param>
	void MoveHorizontal(int a_MoveDir);

	/// <summary> Rotate the falling piece </summary>
	void Rotate();

	/// <summary> Set the a_IdLevel that will influance the color of piece that will spawn </summary>
	void SetColorIDFromLine(int a_IdLevel);
	
	/// <summary> Check if a row is full, if yes, RemoveFullLines will be called! </summary>
	void CheckRow();

	/// <summary> Return the number of lines destroy in the grid </summary>
	/// <return> int : m_Lines </return>
	int GetLines() { return m_Lines; }

	/// <summary> Return the number of piece that has touch the ground. </summary>
	/// <return> int : m_NbFallingPiece </return>
	int GetNbFallingPiece() { return m_NbFallingPiece; }

	/// <summary> Reture a bool to check if the game is over or not. </summary>
	/// <return> bool : m_IsGameOver </return>
	bool GetIsGameOver() { return m_IsGameOver; }

private:

	/// <summary> Make the piece fall </summary>
	void MoveVertical();

	/// <summary> Remove a line from a given Y position </summary>
	/// <param name="aPosY"> int : The line that will be deleted </param>
	void RemoveFullLines(int aPosY);

	/// <summary> Create a game over background when the game is over! </summary>
	void GameOverBackground();

	SDL_Surface* m_Surface = nullptr;  // Pointer of SDL_Surface that the grid will be draw.
	SDL_Surface* m_GameOverText = nullptr; // Game over text

	int m_Lines = 0; // Number of lines destroy
	bool m_IsGameOver = false; // Check if the game is over
	
	int m_Index; // Current index of the falling piece

	vector<Piece*> m_Pieces; // Vector containing all piece created in the game.
	Piece* m_NextPieces = nullptr; // Next piece that we see in UI section that will be in the grid

	vector<Tiles*> m_Tiles; // vector of pointers of tiles used for the game over background

	int m_Grid[10][17]; // Main grid of the game

	int m_PieceChoosen; // Keep in memory what is the next id for the next piece that will appear in the game.

	int m_IdColor; // Will tell what color the piece will be!

	int m_NbFallingPiece; // Number of piece that touch the ground
};