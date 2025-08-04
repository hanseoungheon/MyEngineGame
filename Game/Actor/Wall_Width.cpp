#include "Actor/Wall_Width.h"

Wall_Width::Wall_Width(const Vector2& position)
	:Actor("_",Color::White,position)
{
	SetSortingOrder(0);
}
