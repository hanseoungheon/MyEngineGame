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

	~Speech_UI();

	virtual void Render() override;
	virtual void Tick(float DeltaTime) override;

	//1000이 1초
	void SayTalking(const char* say,Vector2 position,DWORD talkSpeed,
		bool EndSleep,const char* name);
	void BlackOut();

	bool CheckTag(const char* name);

private:
	std::vector<std::string> lines;
	//bool CharaTalking = false;
	char* NameTag = nullptr;

private:
	//전역변수 선언
	int lineoffset = 0;
	int maxWidth = 0;
	Vector2 cursor = Vector2::Zero;
	Vector2 StartPosition = Vector2::Zero;
};