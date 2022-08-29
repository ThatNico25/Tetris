#include "LoadSaveJson.h"

int LoadSaveJson::Load()
{
	std::ifstream file("File.json");
	Json::Value score;
	file >> score;

	return score["score"].asInt();
}

void LoadSaveJson::Save(const int aScore)
{
	std::ofstream jsonFile;
	jsonFile.open("File.json");
	Json::Value scoreValue(Json::objectValue);
	CreateSaveIntElement(aScore, scoreValue);
	jsonFile << scoreValue;
	jsonFile.close();
}

void LoadSaveJson::CreateSaveIntElement(const int aScore, Json::Value& a_Element)
{
	a_Element["score"] = aScore;
}

