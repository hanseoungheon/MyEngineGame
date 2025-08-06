#include "Wall_Length.h"

Wall_Length::Wall_Length(const Vector2& position)
	:Actor("|",Color::White,position,false,IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
