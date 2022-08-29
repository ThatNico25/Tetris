#include "Background.h"
#include "Loader.h"

Background::Background(const std::string& a_Path)
{
	m_Surface = Loader::LoadPng(a_Path);
}

Background::~Background()
{
	if (m_Surface != nullptr)
	{
		SDL_FreeSurface(m_Surface);
		m_Surface = nullptr;
	}
}

void Background::Draw(SDL_Surface* a_ScreenSurface)
{
	SDL_BlitSurface(m_Surface, nullptr, a_ScreenSurface, nullptr);
}