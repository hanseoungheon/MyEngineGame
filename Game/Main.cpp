#include <iostream>

int Random(int num1, int num2);

int main()
{
	//srand(time(nullptr));
	for (int j = 0; j < 10; j++)
	{
		for (int i = 0; i < 10; ++i)
			std::cout << Random(30, 10) << " ";

		std::cout << "\n";
	}

}

int Random(int num1, int num2) // ��, num1 > num2
{
	//ex 10���� 30������ ���߿��� ���� 30 -10 = 20
	int randNumRange = (num1 - num2) + 1;

	return ((rand() * randNumRange) / (RAND_MAX + 1)) + num2;

}