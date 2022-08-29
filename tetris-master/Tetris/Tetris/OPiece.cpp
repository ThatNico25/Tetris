#include "OPiece.h"

OPiece::OPiece(const int a_x, const int a_y, const int a_IDColor, const int a_Size) :
	m_IDColor(a_IDColor),
	m_Size(a_Size)
{
	CreatePiece(a_x, a_y, -1, -1);
}

OPiece::OPiece(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY, const int a_IDColor, const int a_Size) :
	m_GridPosX(a_GridPosY),
	m_GridPosY(a_GridPosY),
	m_IDColor(a_IDColor),
	m_Size(a_Size)
{
	CreatePiece(a_x, a_y, a_GridPosX, a_GridPosY);
}

OPiece::~OPiece()
{
	if (m_Surface != nullptr)
	{
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
	}

	if (m_Rect != nullptr)
	{
		delete m_Rect;
		m_Rect = nullptr;
	}

	for (std::vector<Tiles*>::iterator i = m_Tiles.begin(); i != m_Tiles.end(); ++i)
	{
		delete *i;
		*i = nullptr;
	}
}

void OPiece::CreatePiece(const int a_x, const int a_y, int a_GridPosX, int a_GridPosY)
{	
	if (m_IDColor == 0)
	{
		m_Tiles.push_back(new Tiles("Ressources/YellowSquare.png", a_x , a_y, 32, 32, a_GridPosX, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/YellowSquare.png", a_x - 32, a_y, 32, 32, a_GridPosX - 1, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/YellowSquare.png", a_x, a_y - 32, 32, 32, a_GridPosX, a_GridPosY - 1));
		m_Tiles.push_back(new Tiles("Ressources/YellowSquare.png", a_x - 32, a_y - 32, 32, 32, a_GridPosX - 1, a_GridPosY - 1));
	}
	else if (m_IDColor == 1)
	{
		m_Tiles.push_back(new Tiles("Ressources/OrangeSquare.png", a_x, a_y, 32, 32, a_GridPosX, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/OrangeSquare.png", a_x - 32, a_y, 32, 32, a_GridPosX - 1, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/OrangeSquare.png", a_x, a_y - 32, 32, 32, a_GridPosX, a_GridPosY - 1));
		m_Tiles.push_back(new Tiles("Ressources/OrangeSquare.png", a_x - 32, a_y - 32, 32, 32, a_GridPosX - 1, a_GridPosY - 1));
	}
	else if (m_IDColor == 2)
	{
		m_Tiles.push_back(new Tiles("Ressources/BlackSquare.png", a_x, a_y, 32, 32, a_GridPosX, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/BlackSquare.png", a_x - 32, a_y, 32, 32, a_GridPosX - 1, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/BlackSquare.png", a_x, a_y - 32, 32, 32, a_GridPosX, a_GridPosY - 1));
		m_Tiles.push_back(new Tiles("Ressources/BlackSquare.png", a_x - 32, a_y - 32, 32, 32, a_GridPosX - 1, a_GridPosY - 1));
	}
	else if (m_IDColor == 3)
	{
		m_Tiles.push_back(new Tiles("Ressources/RedSquare.png", a_x, a_y, 32, 32, a_GridPosX, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/RedSquare.png", a_x - 32, a_y, 32, 32, a_GridPosX - 1, a_GridPosY));
		m_Tiles.push_back(new Tiles("Ressources/RedSquare.png", a_x, a_y - 32, 32, 32, a_GridPosX, a_GridPosY - 1));
		m_Tiles.push_back(new Tiles("Ressources/RedSquare.png", a_x - 32, a_y - 32, 32, 32, a_GridPosX - 1, a_GridPosY - 1));
	}	
}

void OPiece::SetPosition(const int a_x, const int a_y, int GridPosX, int GridPosY)
{
	m_Tiles[0]->SetGridPosition(GridPosX, GridPosY);
	m_Tiles[1]->SetGridPosition(GridPosX - 1, GridPosY);
	m_Tiles[2]->SetGridPosition(GridPosX, GridPosY - 1);
	m_Tiles[3]->SetGridPosition(GridPosX - 1, GridPosY - 1);
}

void OPiece::Draw(SDL_Surface* a_ScreenSurface)
{
	for (int i = 0; i < m_Tiles.size(); i++)
	{
		m_Tiles[i]->Draw(a_ScreenSurface);
	}
}

void OPiece::Rotate(int a_angle, int a_OffsetX, int a_OffsetY)
{
	m_Angle = a_angle;

	// Reset angle if it's too high
	if (a_angle == 360)
	{
		m_Angle = 0;
	}

	// OPiece doesn't need a rotation
}

int OPiece::GetAngle()
{
	return m_Angle;
}

vector<Tiles*> OPiece::GetTiles()
{
	return m_Tiles;
}

int OPiece::GetCollisionSize()
{
	return m_Size;
}
