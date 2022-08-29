#include "UI.h"
#include "Loader.h"
#include "LoadSaveJson.h"
#include <iostream>
#include <sstream> 

UI::UI(const std::string& a_Path)
{
	m_Surface = Loader::LoadPng(a_Path);
	m_Rect = Loader::CreateRect(375, 0, 175, 640);
	
	font = TTF_OpenFont("Ressources/font.ttf", 12);

	m_HighestScore = TTF_RenderText_Solid(font, ("Highest score: "), { 255, 255, 255 });
	m_HighestScoreNb = TTF_RenderText_Solid(font, (std::to_string(LoadSaveJson::Load())).c_str(), { 255, 255, 255 });

	m_Score = TTF_RenderText_Solid(font, "Score: 000000", { 255, 255, 255 });
	m_Level = TTF_RenderText_Solid(font, "Level: 01 ", { 255, 255, 255 });
	m_Time = TTF_RenderText_Solid(font, "Time: ", { 255, 255, 255 });
	m_Line = TTF_RenderText_Solid(font, "Line: 0 ", { 255, 255, 255 });

	m_Timer = 0;
	m_StartTimer = SDL_GetTicks();
	m_Lines = 0;
	m_ScoreNb = 0;
}

UI::~UI()
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

	if (m_Score != nullptr)
	{
		SDL_FreeSurface(m_Score);
		m_Score = nullptr;
	}

	if (m_Time != nullptr)
	{
		SDL_FreeSurface(m_Time);
		m_Time = nullptr;
	}

	if (m_Line != nullptr)
	{
		SDL_FreeSurface(m_Line);
		m_Line = nullptr;
	}

	if (m_HighestScore != nullptr)
	{
		SDL_FreeSurface(m_HighestScore);
		m_HighestScore = nullptr;
	}

	if (m_HighestScoreNb != nullptr)
	{
		SDL_FreeSurface(m_HighestScoreNb);
		m_HighestScoreNb = nullptr;
	}

	if (font != nullptr)
	{
		TTF_CloseFont(font);
		font = nullptr;
	}
}

void UI::UpdateUI()
{
	// Timer
	m_Timer += (SDL_GetTicks() - m_StartTimer) / 1000;
	m_StartTimer = SDL_GetTicks();

	m_Time = TTF_RenderText_Solid(font, ("Time: " + std::to_string((int)m_Timer) + " secs").c_str(), { 255, 255, 255 });
	
	// Lines
	m_Line = TTF_RenderText_Solid(font, ("Lines: " + std::to_string((int)m_Lines)).c_str(), { 255, 255, 255 });

	// Score
	m_Score = TTF_RenderText_Solid(font, ("Score: " + std::to_string(m_ScoreNb)).c_str(), { 255, 255, 255 });

	// Highest Score
	int highScore = LoadSaveJson::Load();

	if (highScore < m_ScoreNb)
	{
		m_HighestScoreNb = TTF_RenderText_Solid(font, (std::to_string(m_ScoreNb)).c_str(), { 255, 255, 255 });
		LoadSaveJson::Save(m_ScoreNb);
	}

	// Level
	if (m_LevelNb != 10)
	{
		m_Level = TTF_RenderText_Solid(font, ("Level: " + std::to_string(m_LevelNb)).c_str(), { 255, 255, 255 });
	}
	else
	{
		m_Level = TTF_RenderText_Solid(font, ("Level: " + std::to_string(m_LevelNb) + " Max").c_str(), { 255, 255, 255 });
	}
}

int UI::GetLines()
{
	return m_Lines;
}

void UI::SetLine(int aLine)
{
	m_Lines = aLine;
}

int UI::GetScore()
{
	return m_ScoreNb;
}

void UI::SetScore(int aScore)
{
	m_ScoreNb = aScore;
}

int UI::GetLevelNb()
{
	return m_LevelNb;
}

void UI::SetLevelNb(int aLevel)
{
	m_LevelNb = aLevel;
}

void UI::Draw(SDL_Surface* a_ScreenSurface)
{
	SDL_BlitSurface(m_Surface, nullptr, a_ScreenSurface, m_Rect);

	SDL_Rect offset;
	offset.x = 408;
	offset.y = 175;
	SDL_BlitSurface(m_Score, NULL, a_ScreenSurface, &offset);

	offset.y = 250;
	SDL_BlitSurface(m_Level, NULL, a_ScreenSurface, &offset);

	offset.y = 325;
	SDL_BlitSurface(m_Time, NULL, a_ScreenSurface, &offset);

	offset.y = 400;
	SDL_BlitSurface(m_Line, NULL, a_ScreenSurface, &offset);

	offset.y = 460;
	SDL_BlitSurface(m_HighestScore, NULL, a_ScreenSurface, &offset);

	offset.y = 485;
	SDL_BlitSurface(m_HighestScoreNb, NULL, a_ScreenSurface, &offset);
}