#pragma once
#pragma warning(disable: 4251) //DLL �ܺη� ���ø� ������ �� �߻��ϴ� ��� ����
#pragma warning(disable: 4172) //���������� �ּҸ� ��ȯ�� �� �߻��ϴ� ��� ����

//#define BuildEngineDLL 0
#if BuildEngineDLL
#define Engine_API __declspec(dllexport)

#else
#define Engine_API __declspec(dllimport)
#endif


//�޸� ���� �Լ�
template <typename T>
void SafeDelete(T*& target)
{
	if (target != nullptr)
	{
		delete target;
		target = nullptr;
	}
}

template <typename T>
void SafeDeleteArray(T*& target)
{
	if (target != nullptr)
	{
		delete[] target;
		target = nullptr;
	}
}
