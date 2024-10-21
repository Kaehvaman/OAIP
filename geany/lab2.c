#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <locale.h>

#define PI 3.14159265358979323846

void vector_angle() {
	float x1, y1, x2, y2;
	printf("Введите координаты векторов\n");
	printf("x1 = ");
	scanf_s("%f", &x1);
	printf("y1 = ");
	scanf_s("%f", &y1);
	printf("x2 = ");
	scanf_s("%f", &x2);
	printf("y2 = ");
	scanf_s("%f", &y2);
	printf("%.2f градусов", 57.3 * acos((x1 * x2 + y1 * y2) / (sqrt(x1 * x1 + y1 * y1) * sqrt(x2 * x2 + y2 * y2))));
}

void lc_freq() {
	float L, C;
	printf("L = ");
	scanf_s("%f", &L);
	printf("C = ");
	scanf_s("%f", &C);
	printf("%.2f Гц", 1 / (2 * PI * sqrt(L * C)));
}

void deposit() {
	int money, days;
	float rate, eff, result;
	printf("ставка в %% = ");
	scanf_s("%f", &rate);
	printf("сумма депозита = ");
	scanf_s("%d", &money);
	printf("сколько дней капитализации в год = ");
	scanf_s("%d", &days);
	result = money * pow((1 + (rate / 100) / days), days);
	eff = (result - money) / money * 100;
	printf("эффективная ставка = %.2f%%  доход = %.2f", eff, result - money);
}

int main() {
	//setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int num;
	printf("1. Рассчитать угол между двумя двухмерными векторами.\n");
	printf("2. Рассчитать резонансную частоту LC-контура.\n");
	printf("3. Рассчитать доход по вкладу за год.\n");

	printf("Выберите программу: ");
	scanf_s("%d", &num);

	switch (num)
	{
	case 1:
		vector_angle();
		break;
	case 2:
		lc_freq();
		break;
	case 3:
		deposit();
		break;
	default:
		printf("Не тот номер!");
		break;
	}
	return 0;
}
