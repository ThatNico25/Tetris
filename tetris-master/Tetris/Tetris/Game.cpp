#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "Game.h"
#include "Loader.h"

SDL_Window* Game::m_Window = nullptr;
SDL_Surface* Game::m_ScreenSurface = nullptr;
SDL_Renderer* Game::m_Renderer = nullptr;
Background* Game::m_Background = nullptr;
Grid* Game::m_Grid = nullptr;
UI* Game::m_UI = nullptr;

float Game::m_CurrentTime = 0;
float Game::m_StartTime = SDL_GetTicks();
float Game::m_Timer = 0;
float Game::m_Limit = 400;
int Game::m_Acceleration = 0;
bool Game::m_IsRunning = true;
int Game::m_NbNessaryLines = 5;
int Game::m_NumberFallingPiece = 0;

void Game::Destroy()
{
	if (m_Background != nullptr)
	{
		delete m_Background;
		m_Background = nullptr;
	}

	if (m_Grid != nullptr)
	{
		delete m_Grid;
		m_Grid = nullptr;
	}

	if (m_UI != nullptr)
	{
		delete m_UI;
		m_UI = nullptr;
	}

	if (m_ScreenSurface != nullptr)
	{
		SDL_FreeSurface(m_ScreenSurface);
		m_ScreenSurface = nullptr;
	}

	if (m_Window != nullptr)
	{
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
	}

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		}

		// Create the window
		CreateWindow();
		
		// Set up all elements of tetris
		m_Background = new Background("Ressources/Background.jpg");
		m_Grid = new Grid("Ressources/Grid.png");
		m_UI = new UI("Ressources/UI.png");
	}
}

void Game::CreateWindow()
{
	m_Window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_SetWindowIcon(m_Window, Loader::LoadPng("Ressources/Icon.png"));

	if (m_Window == NULL)
	{
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
	}
	else
	{
		m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		int imgFlags = IMG_INIT_PNG;

		if (!(IMG_Init(imgFlags) & imgFlags))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		}
		else
		{
			m_ScreenSurface = SDL_GetWindowSurface(m_Window);
		}
	}
}

void Game::Update()
{
	SDL_Event e;

	m_CurrentTime = SDL_GetTicks() - m_StartTime;

	m_Grid->CheckRow();

	// Update element each time after a amount of time
	if (m_CurrentTime > m_Limit - m_Acceleration && !m_Grid->GetIsGameOver())
	{
		m_Grid->Update();
		m_StartTime = SDL_GetTicks();
		m_CurrentTime = 0;

		// Update UI
		m_UI->UpdateUI();
	}

	// Update score when a piece touch the ground
	if (m_Grid->GetNbFallingPiece() != m_NumberFallingPiece)
	{
		m_UI->SetScore(m_UI->GetScore() + 25);
		m_NumberFallingPiece = m_Grid->GetNbFallingPiece();
	}
	
	// Edit Lines & Level of the UI
	if (m_Grid->GetLines() != m_UI->GetLines())
	{
		m_UI->SetLine(m_Grid->GetLines());
		m_UI->SetScore(m_UI->GetScore() + 500);

		if (m_UI->GetLines() > m_NbNessaryLines && m_UI->GetLevelNb() != 10 )
		{
			m_NbNessaryLines += 5;
			m_UI->SetLevelNb(m_UI->GetLevelNb() + 1);
			m_Grid->SetColorIDFromLine(m_UI->GetLevelNb());
			m_Acceleration += 20;
		}
	}

	// Controls
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
				case SDLK_LEFT:
					m_Grid->MoveHorizontal(-1);
					break;

				case SDLK_RIGHT:
					m_Grid->MoveHorizontal(1);
					break;

				case SDLK_DOWN:
					if (m_Limit != 200)
					{
						m_Limit -= 200;
					}
					break;

				case SDLK_r:
					m_Grid->Rotate();
					break;
			}
		}

		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_DOWN:
				if (m_Limit != 400)
				{
					m_Limit += 200;
				}
				break;
			}
		}

		if (e.type == SDL_QUIT)
		{
			m_IsRunning = false;
			return;
		}
	}
}

void Game::Draw()
{
	m_Background->Draw(m_ScreenSurface);
	m_Grid->Draw(m_ScreenSurface);
	m_UI->Draw(m_ScreenSurface);
	SDL_UpdateWindowSurface(m_Window);
}
