#include "AttackUI_Length.h"

AttackUI_Length::AttackUI_Length(const Vector2& position,Color color)
	:Actor("|", color, position, true, IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
