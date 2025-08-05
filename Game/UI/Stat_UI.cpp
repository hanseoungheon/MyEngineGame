#define _CRT_SECURE_NO_WARNINGS
#include "Stat_UI.h"
#include <iostream>
#include <string>
Stat_UI::Stat_UI(const char* name,Color color
	,const Vector2& position,char Tag) 
	: Actor(name, color, position, true)
{
	SetSortingOrder(1);

	SetPosition(position);

	this->Tag = Tag;
}

void Stat_UI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetColor(Color::Yellow);
	//image = "asdasd";
}

char Stat_UI::GetSingleStatImage() const
{
	return SingleImage;
}

void Stat_UI::SetSingleStatImage(const char statimage)
{
	SingleImage = statimage;
}

void Stat_UI::SetStringStatImage(int number)
{
	if (number > -1)
	{
		sprintf(image, "%d", number);
	}
}

char Stat_UI::GetTag() const
{
	return Tag;
}
