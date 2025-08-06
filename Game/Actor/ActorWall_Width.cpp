#include "ActorWall_Width.h"

ActorWall_Width::ActorWall_Width(const Vector2& position, Color color)
	:Actor("_",color,position,true,IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
