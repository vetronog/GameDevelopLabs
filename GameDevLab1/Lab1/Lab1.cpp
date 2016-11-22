// ���������:
//     1)���� ������ �������������
//	   2)�������� ������������ �����
//	   3)���������� � ����� ������ ������ � ����������� �� �������
//		�)����� ������� �������� ������
//		�)����� ������� ��������� ������

#include "stdafx.h"
#include <cmath>
const float GRAVITY = 9.8f;

int AskAndGetHeight()
{
	int inputHeight;
	printf("inputHeight: ");
	if (0 == scanf_s("%d", &inputHeight))
	{
		printf("\n" "expected integer-point number" "\n");
		return -1;
	}
	if ((inputHeight <= 0) || (inputHeight >= INT_MAX))
	{
		return -1;
	}
	return inputHeight;
}

void PrintTimeAndHeight(float maxRiseTime, float &currentHeight, float initSpeed)
{
	currentHeight = initSpeed * maxRiseTime - 0.5f * GRAVITY * pow(maxRiseTime, 2);
	printf("flyTime = %f, currentHeight = %f\n", maxRiseTime, currentHeight);
}

void CalcHeight(float maxRiseTime)
{
	bool isJumpEnd = false;
	float initSpeed = GRAVITY * maxRiseTime;
	float currentHeight;
	for (float flyTime = 0; flyTime < maxRiseTime * 2; flyTime += 0.1f)
	{
		if (flyTime > maxRiseTime && !isJumpEnd)
		{
			isJumpEnd = true;
			PrintTimeAndHeight(maxRiseTime, currentHeight, initSpeed);			
		}PrintTimeAndHeight(flyTime, currentHeight, initSpeed);
	}PrintTimeAndHeight(maxRiseTime * 2, currentHeight, initSpeed);
}

int main(int, char *[])
{
	int inputHeight = AskAndGetHeight();
	if (inputHeight == -1)
	{
		exit(1);
	}
	float maxRiseTime = sqrt(inputHeight * 2 / GRAVITY);
	printf("maxRiseTime=%f\n", maxRiseTime);
	CalcHeight(maxRiseTime);
	return 0;
}