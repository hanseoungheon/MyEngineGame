#include "Wall_Length.h"

Wall_Length::Wall_Length(const Vector2& position)
	:Actor("|", Color::White,position)
{
	SetSortingOrder(0);
}
