#pragma once

#include "Level/Level.h"
#include "Actor/Actor.h"
class MainMap : public Level
{
	RTTI_DECLARATIONS(MainMap, Level)
public:
	MainMap(const char* fileName);
	void Rending();
	void DeleteMap();
private:
	char filePath[256] = {};
};