#include "Actor/Wall_Width.h"

Wall_Width::Wall_Width(const Vector2& position)
	:Actor("_",Color::White,position,false,IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
