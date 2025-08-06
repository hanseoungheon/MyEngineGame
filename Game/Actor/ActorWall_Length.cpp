#include "ActorWall_Length.h"

ActorWall_Length::ActorWall_Length(const Vector2& position,Color color)
	:Actor("|",color,position,true,IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
