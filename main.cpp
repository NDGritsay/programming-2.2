#include <stdio.h>
#include <Windows.h>
#include "ndgstrings.h"
#include "book.h"

int menu(void);
void reference(void);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ЛР2 Односвязные списки языка С/С++");

	Word *words1 = 0, *words2 = 0;
	int word1Ct = 0, word2Ct = 0, isProgEnd = 0;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //Ввод исходного списка
			break;
		case 2: //Вывод исходного массива структур
			break;
		case 3: //Формирование результирующего массива структур
			break;
		case 4: //Вывод результирующего массива структур
			break;
		case 5: //Вывод справки
			reference();
			waitForEnter();
			break;
		case 0: //Выход из программы
			system("cls");
			isProgEnd = 1;
			printf("До свидания!\n");
			waitForEnter();
			break;
		}
	} while (!isProgEnd);
	return 0;
}

int menu(void)
{
	int res, isInputCorrect = 0;
	printf(
		"=Меню=\n"
		"1 - Ввод списка\n"
		"2 - Добавление элемента\n" //первого, последнего, н-ного
		"3 - Удаление элемента\n" //первого, последрего, н-ного, по критерию
		"4 - Вывод списка\n" //полностью, по критериям
		"5 - Сортировка списка\n"
		"6 - Справка\n"
		"0 - Выход");
	do
	{
		printf("\nВыберите пункт меню: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\aОшбика! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (res < 0 || res > 6)
		{
			printf("\aОшибка! Такого пункта меню нет.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return res;
}

void reference(void)
{

}