#pragma once
#include "Actor/Actor.h"

class Stat_UI: public Actor
{
	RTTI_DECLARATIONS(Stat_UI,Actor)

public:
	Stat_UI(const char * name,Color color,const Vector2& position,
		char Tag = 'd'); //default

	virtual void Tick(float DeltaTime) override;

	char GetSingleStatImage() const;
	void SetSingleStatImage(const char statimage);

	void SetStringStatImage(int number);

	char GetTag() const;
private:

	char Tag = ' ';

};