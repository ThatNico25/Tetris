#include "Grid.h"
#include "Loader.h"

#include <iostream>  
#include <stdlib.h>
#include <Windows.h>
#include <cstdlib>
#include <time.h>  

Grid::Grid(const std::string& a_Path) :
	m_Index(-1),
	m_IdColor(0),
	m_NbFallingPiece(0)
{
	m_Surface = Loader::LoadPng(a_Path);
	SpawnPiece();
}

Grid::~Grid()
{
	if (m_Surface != nullptr)
	{
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
	}

	if (m_GameOverText != nullptr)
	{
		SDL_FreeSurface(m_GameOverText);
		m_GameOverText = nullptr;
	}

	if (m_NextPieces != nullptr)
	{
		delete m_NextPieces;
		m_NextPieces = nullptr;
	}

	for (std::vector<Piece*>::iterator i = m_Pieces.begin(); i != m_Pieces.end(); ++i) 
	{
		delete *i;
		*i = nullptr;
	}

	for (std::vector<Tiles*>::iterator i = m_Tiles.begin(); i != m_Tiles.end(); ++i)
	{
		delete *i;
		*i = nullptr;
	}
}

void Grid::Update()
{
	if (!m_IsGameOver)
	{
		MoveVertical();
	}
}

void Grid::CheckRow()
{
	if (!m_IsGameOver)
	{
		int count = 0;

		for (int y = 0; y <= 17; y++)
		{
			for (int x = 0; x <= 10; x++)
			{
				if (m_Grid[x][y] == 1)
				{
					count++;
				}
			}

			if (count % 10 != 0)
			{
				count = 0;
			}
			else if (count == 10)
			{
				m_Lines++;
				RemoveFullLines(y);
				count = 0;
				break;
			}
		}
	}
}

void Grid::MoveVertical()
{
	// Check if there is something under the piece
	bool isBlock = false;

	for (int i = 0; !isBlock && i < m_Pieces[m_Index]->GetTiles().size(); i++)
	{
		if (m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY() + 1] == 1
			|| 16 <= m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY())
		{
			isBlock = true;
			break;
		}
	}

	// If yes, create the piece
	if (isBlock)
	{
		for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
		{
			m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 1;
		}
		
		SpawnPiece();
		isBlock = false;
		m_NbFallingPiece++;
	}
	else // if not, move down
	{
		for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size() && !isBlock; i++)
		{
			m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 0;
			m_Pieces[m_Index]->GetTiles()[i]->SetGridPosition(m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX(), m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY() + 1);
			m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 2;
		}
	}
}

void Grid::SetColorIDFromLine(int a_IdLevel)
{
	m_IdColor = a_IdLevel % 4;
}

void Grid::MoveHorizontal(int a_MoveDir)
{
	bool isBlock = false;

	for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
	{
		// Check if not out of the grid
		if (a_MoveDir == 1 && m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() >= 9)
		{
			isBlock = true;
		}
		else if (a_MoveDir == -1 && m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() <= 0)
		{
			isBlock = true;
		}

		// Check If Blocks
		if (a_MoveDir == 1 && m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() + 1][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] == 1)
		{
			isBlock = true;
		}
		else if (a_MoveDir == -1 && m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() - 1][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] == 1)
		{
			isBlock = true;
		}
	}

	// Action
	if(!isBlock)
	{
		for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
		{
			if (a_MoveDir == -1)
			{
				m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 0;
				m_Pieces[m_Index]->GetTiles()[i]->SetGridPosition(m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() - 1, m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY());
				m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 2;
			}
			else
			{
				m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 0;
				m_Pieces[m_Index]->GetTiles()[i]->SetGridPosition(m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX() + 1, m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY());
				m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 2;
			}
		}
	}
}

void Grid::Rotate()
{
	// Check if can rotate without offset
	int offsetX = 0;
	int offsetY = 0;
	bool canRotate = true;

	// Update the grid to remove the emplacement of each tiles of the falling piece because they will be updated
	for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
	{
		m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 0;
	}

	// Create offset for the pos x with the falling piece 
	if (m_Pieces[m_Index]->GetAngle() == 90 || m_Pieces[m_Index]->GetAngle() == 270)
	{
		for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
		{
			// Check the left
			if (m_Pieces[m_Index]->GetTiles()[0]->GetGridPosX() - m_Pieces[m_Index]->GetCollisionSize() <= 0 && m_PieceChoosen != 1)
			{
				offsetX = (int)m_Pieces[m_Index]->GetCollisionSize() / 2;
			}

			// Check the right
			if (m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX() + 2 >= 9)
			{
				offsetX = 10 - (m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX() + m_Pieces[m_Index]->GetCollisionSize());

			} 
		}
	}

	// Create offset for the pos y with the falling piece 
	if (m_Pieces[m_Index]->GetAngle() == 0 || m_Pieces[m_Index]->GetAngle() == 180)
	{
		for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
		{
			if (m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() + m_Pieces[m_Index]->GetCollisionSize() >= 16)
			{
				offsetY = 17 - (m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() + m_Pieces[m_Index]->GetCollisionSize());
			}	
		}
	}

	// Check if there is piece around the falling piece
	if (m_Pieces[m_Index]->GetAngle() == 90 || m_Pieces[m_Index]->GetAngle() == 270)
	{
		if (m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY()] == 1 ||
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX() + 3][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY()] == 1 ||
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX() + 1][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY()] == 1 ||
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX() + 2][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY()] == 1)
		{
			canRotate = false;
		}
	}

	// Check collision with other block
	if (m_Pieces[m_Index]->GetAngle() == 0 || m_Pieces[m_Index]->GetAngle() == 180)
	{
		if (m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY()] == 1 || 
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() + 3] == 1 ||
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() + 1] == 1 ||
			m_Grid[m_Pieces[m_Index]->GetTiles()[1]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() + 2] == 1)
		{
			canRotate = false;
		}
	}

	// If the piece just spawn, we can't directly rotate it
	if (m_Pieces[m_Index]->GetTiles()[1]->GetGridPosY() == 0)
	{
		canRotate = false;
	}

	// If it's still possible to rotate, then rotate the falling piece
	if (canRotate)
	{
		m_Pieces[m_Index]->Rotate(m_Pieces[m_Index]->GetAngle() + 90, offsetX, offsetY); 
	}

	// Update the grid with the actual new position of each tiles from the falling piece.
	for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
	{
		m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 2;
	}
}

void Grid::RemoveFullLines(int aPosY)
{
	// Remove the line
	for (int i = 0; i < m_Pieces.size(); i++)
	{
		for (int j = 0; j < m_Pieces[i]->GetTiles().size(); j++)
		{
			if (m_Pieces[i]->GetTiles()[j]->GetGridPosY() == aPosY)
			{
				// Put them out of bound
				m_Grid[m_Pieces[i]->GetTiles()[j]->GetGridPosX()][m_Pieces[i]->GetTiles()[j]->GetGridPosY()] = 0;
				m_Pieces[i]->GetTiles()[j]->SetGridPosition(99, 99);
			}
		}
	}

	// Move down tiles
	for (int i = 0; i < m_Pieces.size(); i++)
	{
		for (int j = 0; j < m_Pieces[i]->GetTiles().size(); j++)
		{
			if (m_Pieces[i]->GetTiles()[j]->GetGridPosY() < aPosY)
			{
				m_Grid[m_Pieces[i]->GetTiles()[j]->GetGridPosX()][m_Pieces[i]->GetTiles()[j]->GetGridPosY()] = 0;
				m_Pieces[i]->GetTiles()[j]->SetGridPosition(m_Pieces[i]->GetTiles()[j]->GetGridPosX(), m_Pieces[i]->GetTiles()[j]->GetGridPosY() + 1);
			}
		}	
	}

	// Reloads grid
	for (int i = 0; i < m_Pieces.size(); i++)
	{
		for (int j = 0; j < m_Pieces[i]->GetTiles().size(); j++)
		{
			if (m_Pieces[i]->GetTiles()[j]->GetGridPosX() != 99)
			{
				m_Grid[m_Pieces[i]->GetTiles()[j]->GetGridPosX()][m_Pieces[i]->GetTiles()[j]->GetGridPosY()] = 1;
			}
		}
	}
}

void Grid::Draw(SDL_Surface* a_ScreenSurface)
{
	SDL_BlitSurface(m_Surface, nullptr, a_ScreenSurface, nullptr);

	// Draw all pieces in grid
	for (int i = 0; i < m_Pieces.size(); i++)
	{
		m_Pieces[i]->Draw(a_ScreenSurface);
	}

	// Draw next piece in the ui section
	m_NextPieces->Draw(a_ScreenSurface);

	if (m_IsGameOver)
	{
		// Draw all tiles for the game over screen
		for (int x = 0; x < m_Tiles.size(); x++)
		{
			m_Tiles[x]->Draw(a_ScreenSurface);
		}

		// Draw game over text
		SDL_Rect offset;
		offset.x = 60;
		offset.y = 200;
		SDL_BlitSurface(m_GameOverText, NULL, a_ScreenSurface, &offset);
	}
}

void Grid::SpawnPiece()
{
	// Number generator to generate random piece
	srand(time(nullptr));
	int randomNumber = rand() % 7 + 1;

	// Check if game over! (Check spawn point) If spawnpoint is full of tiles, then game over
	if (m_Grid[4][1] == 1 || m_Grid[5][1] == 1 || m_Grid[6][1] == 1 || m_Grid[7][1] == 1)
	{
		GameOverBackground();
		m_IsGameOver = true;
		return;
	}

	// Check if we need to delete row before spawning another piece, if yes, then the row is deleted
	for (int i = 0; i < 4; i++)
	{
		CheckRow();
	}
	
	// Create Visual Piece
	if (m_Index == -1)
	{
		int nbRand = rand() % 7 + 1;

		switch (nbRand)
		{
			case 1:
				m_Pieces.push_back(new IPiece(28 + (3 * 32), 28, 3, 0, m_IdColor, 4));
				break;
			case 2:
				m_Pieces.push_back(new OPiece(28 + (5 * 32), 28 + (1 * 32), 5, 1, m_IdColor, 1));
				break;
			case 3:
				m_Pieces.push_back(new TPiece(28 + (5 * 32), 28 + (1 * 32), 5, 1, m_IdColor, 2));
				break;
			case 4:
				m_Pieces.push_back(new JPiece(28 + (5 * 32), 28 + (1 * 32), 5, 1, m_IdColor, 2));
				break;
			case 5:
				m_Pieces.push_back(new LPiece(28 + (5 * 32), 28 + (1 * 32), 5, 1, m_IdColor, 2));
				break;
			case 6:
				m_Pieces.push_back(new SPiece(28 + (5 * 32), 28, 5, 0, m_IdColor, 2)); 
				break;
			case 7:
				m_Pieces.push_back(new ZPiece(28 + (5 * 32), 28, 5, 0, m_IdColor, 2));
				break;
		}

		m_Index++;
	}
	else
	{
		m_Pieces.push_back(m_NextPieces);
		m_Index++;
		
		switch (m_PieceChoosen)
		{
			case 1:
				m_Pieces[m_Index]->SetPosition(28 + (3 * 32), 28, 3, 0);
				break;
			case 2:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28 + (1 * 32), 5, 1);
				break;
			case 3:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28 + (1 * 32), 5, 1);
				break;
			case 4:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28 + (1 * 32), 5, 1);
				break;
			case 5:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28 + (1 * 32), 5, 1);
				break;
			case 6:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28, 5, 0);
				break;
			case 7:
				m_Pieces[m_Index]->SetPosition(28 + (5 * 32), 28, 5, 0);
				break;
		}
	}

	// Create piece in a table.
	for (int i = 0; i < m_Pieces[m_Index]->GetTiles().size(); i++)
	{
		if (m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] != 1)
		{
			m_Grid[m_Pieces[m_Index]->GetTiles()[i]->GetGridPosX()][m_Pieces[m_Index]->GetTiles()[i]->GetGridPosY()] = 2;
		}
	}

	// Check next piece
	switch (randomNumber)
	{
		case 1:
			m_NextPieces = new IPiece(400, 70, 0, 0, m_IdColor, 4);
			break;
		case 2:
			m_NextPieces = new OPiece(460, 90, 0, 0, m_IdColor, 1);
			break;
		case 3:
			m_NextPieces = new TPiece(450, 90, 0, 0, m_IdColor, 2);
			break;
		case 4:
			m_NextPieces = new JPiece(450, 90, 0, 0, m_IdColor, 2);
			break;
		case 5:
			m_NextPieces = new LPiece(450, 90, 0, 0, m_IdColor, 2);
			break;
		case 6:
			m_NextPieces = new SPiece(450, 60, 0, 0, m_IdColor, 2);
			break;
		case 7:
			m_NextPieces = new ZPiece(450, 60, 0, 0, m_IdColor, 2);
			break;
	}

	m_PieceChoosen = randomNumber;
}

void Grid::GameOverBackground()
{
	// Generate Text Game over!
	m_GameOverText= TTF_RenderText_Solid(TTF_OpenFont("Ressources/font.ttf", 36), "Game over!", {0, 0, 0});

	// Spawn tiles
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 17; y++)
		{
			int randomNumber = rand() % 8;

			switch (randomNumber)
			{
			case 0:
				m_Tiles.push_back(new Tiles("Ressources/BlackSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 1:
				m_Tiles.push_back(new Tiles("Ressources/BlueSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 2:
				m_Tiles.push_back(new Tiles("Ressources/CyanSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 3:
				m_Tiles.push_back(new Tiles("Ressources/GraySquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 4:
				m_Tiles.push_back(new Tiles("Ressources/GreenSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 5:
				m_Tiles.push_back(new Tiles("Ressources/OrangeSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 6:
				m_Tiles.push_back(new Tiles("Ressources/PurpleSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			case 7:
				m_Tiles.push_back(new Tiles("Ressources/RedSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			default:
				m_Tiles.push_back(new Tiles("Ressources/YellowSquare.png", 28 + (x * 32), 28 + (y * 32), 32, 32));
				break;
			}	
		}
	}
}