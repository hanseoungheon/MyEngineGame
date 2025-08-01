#pragma once

#include <Windows.h>
#include "Math/Vector2.h"
#include "Math/Color.h"

//������Ʈ���� �پ��ϰ� ����� �� �ִ� �������� ��ƿ��Ƽ ��� ����
namespace Utils
{
	template<typename T>
	void Swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	//�ֿܼ� ���ڸ� ��� �� �����ϴ� �ڵ��� �������� �Լ�
	inline HANDLE GetConsoleHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}

	//�ܼ� Ŀ����ġ �̵��Լ�
	inline void SetConsolePosition(COORD coord)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleCursorPosition(handle, coord);
	}
	//�����ε�
	inline void SetConsolePosition(const Vector2& position)
	{
		SetConsolePosition(static_cast<COORD>(position));
	}

	//�ܼ� �ؽ�Ʈ ���� ���� �Լ�
	inline void SetConsoleTextColor(WORD color)
	{
		static HANDLE handle = GetConsoleHandle();
		SetConsoleTextAttribute(handle, color);
	}
	//�����ε�
	inline void SetConsoleTextColor(Color color)
	{
		SetConsoleTextColor(static_cast<WORD>(color));
	}
}

