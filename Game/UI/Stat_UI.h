#pragma once
#include "Actor/Actor.h"

class Stat_UI: public Actor
{
	RTTI_DECLARATIONS(Stat_UI,Actor)

public:
	Stat_UI(const char * name,Color color,const Vector2& position);

	virtual void Tick(float DeltaTime) override;
private:

};