#include "Tiles.h"
#include "Loader.h"

Tiles::Tiles(const std::string& a_Path, const int a_x, const int a_y, const int a_sizeX, const int a_sizeY)
{
	m_Surface = Loader::LoadPng(a_Path);
	m_Rect = Loader::CreateRect(a_x, a_y, a_sizeX, a_sizeY);
}

Tiles::Tiles(const std::string& a_Path, const int a_x, const int a_y, const int a_sizeX, const int a_sizeY, int GridPosX, int GridPosY) :
	m_GridPosX(GridPosX),
	m_GridPosY(GridPosY)
{
	m_Surface = Loader::LoadPng(a_Path);
	m_Rect = Loader::CreateRect(a_x, a_y, a_sizeX, a_sizeY);
}

Tiles::~Tiles()
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
}

void Tiles::Draw(SDL_Surface* a_ScreenSurface)
{
	SDL_BlitSurface(m_Surface, nullptr, a_ScreenSurface, m_Rect);
}


void Tiles::SetGridPosition(const int a_x, const int a_y)
{
	m_GridPosX = a_x;
	m_GridPosY = a_y;
	m_Rect->x = (a_x * 32) + 28;
	m_Rect->y = (a_y * 32) + 28;
}

int Tiles::GetGridPosX()
{
	return m_GridPosX;
}

int Tiles::GetGridPosY()
{
	return m_GridPosY;
}