#pragma once

#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"

//프로젝트에서 다양하게 사용할 수 있는 여러가지 유틸리티 기능 제공
namespace Utils
{
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	//콘솔에 문자를 출력 및 제어하는 핸들을 가져오는 함수
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	//콘솔 커서위치 이동함수
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}
	//오버로딩
	inline void SetConsolePosition(const Vector2& position)
	{
		SetConsolePosition(static_cast<COORD>(position));
	}

	//콘솔 텍스트 색상 설정 함수
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}
	//오버로딩
	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}
}

