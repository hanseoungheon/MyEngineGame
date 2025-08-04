#include "Stat_UI.h"

Stat_UI::Stat_UI(const char* name,Color color
	,const Vector2& position) 
	: Actor(name, color, position, true)
{
	SetSortingOrder(1);

	SetPosition(position);
}

void Stat_UI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
