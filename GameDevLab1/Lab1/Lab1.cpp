// Псевдокод:
//     1)Ввод данных пользователем
//	   2)Проверка корректности ввода
//	   3)Вычисление и вывод высоты прыжка в зависимости от времени
//		а)Вывод момента середины прыжка
//		б)Вывод времени окончания прыжка

#include "stdafx.h"
#include <cmath>

bool AskAndCheckHeight(int &inputHeight)
{
	printf("inputHeight: ");
	if (0 == scanf_s("%d", &inputHeight))
	{
		printf("\n" "expected integer-point number" "\n");
		return false;
	}
	if ((inputHeight <= 0) || (inputHeight >= INT_MAX))
	{
		return false;
	}
	return true;
}

void CalcHeight(float maxRiseTime, const float &gravityConst)
{
	bool isJumpEnd = false;
	float initSpeed = gravityConst * maxRiseTime;
	float currentHeight;
	for (float flyTime = 0; flyTime < maxRiseTime * 2; flyTime += 0.1f)
	{
		if (flyTime > maxRiseTime && !isJumpEnd)
		{
			isJumpEnd = true;
			currentHeight = initSpeed * maxRiseTime - 0.5f * gravityConst * pow(maxRiseTime, 2);
			printf("flyTime=%f, currentHeight=%f\n", maxRiseTime, currentHeight);
		}
		currentHeight = initSpeed * flyTime - 0.5f * gravityConst * pow(flyTime, 2);
		printf("flyTime=%f, currentHeight=%f\n", flyTime, currentHeight);
	}
	currentHeight = initSpeed * (maxRiseTime * 2) - 0.5f * gravityConst * pow(maxRiseTime * 2, 2);
	printf("flyTime=%f, currentHeight=%f\n", maxRiseTime * 2, currentHeight);
}

int main(int, char *[])
{
	const float gravityConst = 9.8f;
	float maxRiseTime;
	int inputHeight;
	if (!AskAndCheckHeight(inputHeight))
	{
		exit(1);
	}
	maxRiseTime = sqrt(inputHeight * 2 / gravityConst);
	printf("maxRiseTime=%f\n", maxRiseTime);
	CalcHeight(maxRiseTime, gravityConst);
	return 0;
}