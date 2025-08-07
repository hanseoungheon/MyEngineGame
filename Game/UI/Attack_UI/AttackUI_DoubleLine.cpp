#include "AttackUI_DoubleLine.h"

AttackUI_DoubleLine::AttackUI_DoubleLine(const Vector2& position,Color color)
	:Actor("=", color, position, true, IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
