#pragma once
#include <vector>
#include <iostream>
#include "Actor/Actor.h"

//enum class UI_Type : int
//{
//	FIGHT = 0,
//	ACTOR = 1,
//	ITEM = 2,
//	MERCY = 3,
//	NONE = 5,
//};

class Speech_UI : public Actor
{
	RTTI_DECLARATIONS(Speech_UI, Actor)

public:
	Speech_UI(const char* filePath, Color color, const
		Vector2& position);

	virtual void Render() override;

	//1000¿Ã 1√ 
	void SayTalking(const char* say,Vector2 position,DWORD talkSpeed,
		bool EndSleep);
	void BlackOut();

	//char* GetTag() const;

private:
	std::vector<std::string> lines;

	//UI_Type UItype;

	//char* NameTag = nullptr;
};