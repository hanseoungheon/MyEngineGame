#include "AttackUI_Mini_Width.h"

AttackUI_Mini_Width::AttackUI_Mini_Width(const Vector2& position,Color color)
	:Actor("-", color, position, true, IsString::STR_FALSE)
{
	SetSortingOrder(0);
}
