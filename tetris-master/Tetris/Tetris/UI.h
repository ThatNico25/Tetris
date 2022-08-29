#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

/// <summary> This class manage the ui of this game. </summary>
class UI
{
public:
	/// <summary> Constructor of UI </summary>
	/// <param name="a_Path"> const std::string& : It's the path of where the image of the background is on the computer.  </param>
	UI(const std::string& a_Path);

	/// <summary> Destructor of UI </summary>
	~UI();

	/// <summary> This function draw the ui of tetris. </summary>
	/// <param name="a_ScreenSurface"> SDL_Surface* : It's the pointor of SDL_Surface that will draw the UI  </param>
	void Draw(SDL_Surface* a_ScreenSurface);

	/// <summary> This function update all elements in the UI. </summary>
	void UpdateUI();

	/// <summary> This function return the number of lines. </summary>
	/// <return> int : m_Lines </return>
	int GetLines();

	/// <summary> This function set the number of lines. </summary>
	/// <param name="a_Line"> int : number of line </param>
	void SetLine(int a_Line);

	/// <summary> This function return the score. </summary>
	/// <return> int : m_ScoreNb </return>
	int GetScore();

	/// <summary> This function set the score. </summary>
	/// <param name="a_Score"> int : score </param>
	void SetScore(int a_Score);

	/// <summary> This function return the number of the level. </summary>
	/// <return> int : m_LevelNb </return>
	int GetLevelNb();

	/// <summary> This function set the number of the level. </summary>
	/// <param name="a_Level"> int : number of the level </param>
	void SetLevelNb(int a_Level);

private:
	SDL_Surface* m_Surface = nullptr; // Pointer of SDL_Surface that the UI will be draw.
	SDL_Rect* m_Rect = nullptr; // Pointer of SDL_Rect that will tell where all texts will be draw.
	SDL_Surface* m_Score = nullptr; // Text that will show the score
	SDL_Surface* m_Level = nullptr; // Text that will show the level
	SDL_Surface* m_Time = nullptr; // Text that will show the time
	SDL_Surface* m_Line = nullptr; // Text that will show the number of line
	SDL_Surface* m_HighestScore = nullptr; // Text that will show the text "highest score"
	SDL_Surface* m_HighestScoreNb = nullptr; // Text that will show the highest score
	TTF_Font* font = nullptr; // Font used for the text

	float m_StartTimer = 0; // Tell when the time start counting
	float m_Timer = 0; // Timer
	float m_Lines = 0; // Number of lines that the player did
	int m_ScoreNb = 0; // Score of the player
	int m_LevelNb = 0; // Which level is the game at
};
