#pragma once
#include <SDL.h>

#include "Background.h"
#include "Grid.h"
#include "UI.h"

/// <summary> Mangage everything that happen in the game </summary>
class Game
{
public:
	/// <summary> Initialize the game </summary>
	static void Init();

	/// <summary> Update all elements in the game </summary>
	static void Update();

	/// <summary> Draw all elements in the game </summary>
	static void Draw();

	/// <summary> Destroy all elements in the game </summary>
	static void Destroy();

	/// <summary> Check if the game is still running. </summary>
	/// <return> Bool : Return a bool to tell if the game is close or not </return>
	static bool IsRunning() { return m_IsRunning; }

private:
	/// <summary> Create a window </summary>
	static void CreateWindow();

	static const int SCREEN_WIDTH = 550; // Screen width of the window
	static const int SCREEN_HEIGHT = 624; // Screen hieght of the window

	static SDL_Window* m_Window; // The main window
	static SDL_Surface* m_ScreenSurface; // The surface related to the window.
	static SDL_Renderer* m_Renderer; // Main renderer
	static Background* m_Background; // Background
	static Grid* m_Grid; // Grid of the game
	static UI* m_UI; // UI of the game

	static float m_StartTime; // Tell when the time start counting
	static float m_CurrentTime; // Tell the current
	static int m_Acceleration; // Acceleration of piece when the player press the arrow_down key
	static bool m_IsRunning; //  Return a bool to tell if the game is close or no
	static int m_NbNessaryLines; // Number of lines needed to go to the next level
	static float m_Timer; // Timer
	static float m_Limit; // Speed that the piece move
	static int m_NumberFallingPiece; // Number of piece that have fallen in the game until now
};

