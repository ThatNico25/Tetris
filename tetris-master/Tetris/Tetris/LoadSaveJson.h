#pragma once
#include "json/json.h"
#include <iostream>
#include <fstream>

/// <summary> This class is responsable to load and save the highest score of the player into a .json file. </summary>
class LoadSaveJson
{
public:
	/// <summary> This function will load the highest score. </summary>
	/// <return> SDL_Surface* : Return the image loaded. </return>
	int static Load();

	/// <summary> This function will save the highest score. </summary>
	/// <param name="a_Score"> const int: It's the score that will be saved! </param>
	void static Save(const int a_Score);

private:
	/// <summary> This function will save the highest score. </summary>
	/// <param name="a_Score"> const int: It's the score that will be saved! </param>
	/// <param name="a_Element"> Json::Value&: It's the Jason value that will keep the score. </param>
	void static CreateSaveIntElement(const int a_Score, Json::Value& a_Element);
};

