#include "AttackUI_Width.h"

AttackUI_Width::AttackUI_Width(const Vector2& position,Color color)
	:Actor("_", color, position, true, IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
