#pragma once

enum class Color :int
{
	Blue = 1,
	Green = 2,
	Red = 4,
	While = Red | Green | Blue,
	Intensity = 8,
};
