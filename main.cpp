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
	system("title = ��2 ����������� ������ ����� �/�++");

	Word *words1 = 0, *words2 = 0;
	int word1Ct = 0, word2Ct = 0, isProgEnd = 0;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //���� ��������� ������
			break;
		case 2: //����� ��������� ������� ��������
			break;
		case 3: //������������ ��������������� ������� ��������
			break;
		case 4: //����� ��������������� ������� ��������
			break;
		case 5: //����� �������
			reference();
			waitForEnter();
			break;
		case 0: //����� �� ���������
			system("cls");
			isProgEnd = 1;
			printf("�� ��������!\n");
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
		"=����=\n"
		"1 - ���� ������\n"
		"2 - ���������� ��������\n" //�������, ����������, �-����
		"3 - �������� ��������\n" //�������, ����������, �-����, �� ��������
		"4 - ����� ������\n" //���������, �� ���������
		"5 - ���������� ������\n"
		"6 - �������\n"
		"0 - �����");
	do
	{
		printf("\n�������� ����� ����: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (res < 0 || res > 6)
		{
			printf("\a������! ������ ������ ���� ���.\n");
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