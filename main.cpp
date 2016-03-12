#include <stdio.h>
#include <Windows.h>
#include "ndgstrings.h"
#include "book.h"

//��������: ����� ���� �� ����� � ����� ������
//�������: ����� ����
int menu(void);

//��������: ����� ������� �� �����
void reference(void);

//��������: ����� ���� ���������� ���� � ����� ������
//�������: ����� ���� ����������
int getAddType(void);

//��������: ����� ���� �������� ���� � ����� ������
//�������: ����� ���� ��������
int getDeleteType(void);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ��2 ����������� ������ ����� �/�++");
	genresInitialization();

	int word1Ct = 0, word2Ct = 0, isProgEnd = 0, listId, addType, deleteType;
	void((*addBook[])(Book**)) = {addFirstBook, addLastBook};  //������ ������� ���������� ����
	void((*deleteBook[])(Book**)) = { deleteFirstBook, deleteLastBook };  //������ ������� �������� ����
	BookHead **heads = (BookHead**)malloc(sizeof(BookHead*));

	*heads = nullptr;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //���������� ������
			heads = addList(heads);
			break;
		case 2: //�������� ������
			system("cls");
			printf("=�������� ������=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				heads = deleteList(heads, listId);
				printf("�������� ������ ���������!\n");
			}
			else
				printf("��� �� ������ ������, ����� �������!\n");
			waitForEnter();
			break;
		case 3: //���������� �����
			system("cls");
			printf("=���������� �����=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				system("cls");
				addType = getAddType();
				system("cls");
				addBook[addType](&(*(heads + listId))->head);
				system("cls");
				printf("=���������� �����=\n"
					"���������� ����� ���������!\n");
			}
			else
				printf("\a��� �� ������ ������! ������� �������� ������.\n");
			waitForEnter();
			break;
		case 4: //�������� �����
			system("cls");
			printf("=�������� �����=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				system("cls");
				if ((*(heads + listId))->head != nullptr)
				{
					deleteType = getDeleteType();
					system("cls");
					deleteBook[deleteType](&(*(heads + listId))->head);
					system("cls");
					printf("=�������� �����=\n"
						"�������� ����� ���������!\n");
				}
				else
					printf("=�������� �����=\n"
						"\a������ ����!\n");
			}
			else
				printf("\a��� �� ������ ������! ������� �������� ������.\n");
			waitForEnter();
			break;
		case 5: //������ �� �������
			heads = addList(heads);
			(*(heads + 1))->head = listCopy((*(heads))->head);
			/*if (*heads != nullptr)
			{
				system("cls");
				printf("=������ �� �������=\n");
				listId = setListId(heads);
			}
			else
				printf("\a��� �� ������ ������! ������� �������� ������.\n");
			waitForEnter();
			break;*/
		case 6: //����� ������
			system("cls");
			printf("=����� ������=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				printBooks((*(heads + listId))->head);
			}
			else
			{
				printf("��� �� ������ ������! ������� �������� ������.\n");
				waitForEnter();
			}
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


//��������: ����� ���� �� ����� � ����� ������
//�������: ����� ����
int menu(void)
{
	int res, isInputCorrect = 0;
	printf(
		"=����=\n"
		"1 - ���������� ������\n"
		"2 - �������� ������\n"
		"3 - ���������� �����\n" //�������, ����������, �-����
		"4 - �������� �����\n" //�������, ����������, �-����, �� ��������
		"5 - ������ �� �������\n"
		"6 - ����� ������\n" //���������, �� ���������
		"7 - �������\n"
		"0 - �����");
	do
	{
		printf("\n�������� ����� ����: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (res < 0 || res > 7)
		{
			printf("\a������! ������ ������ ���� ���.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return res;
}


//��������: ����� ���� ���������� ���� � ����� ������
//�������: ����� ���� ����������
int getAddType(void)
{
	int addType, isInputCorrect = 0;
	printf("=���������� �����=\n"
		"=����� ���� ���������� �����=\n"
		"1 - �������� ����� � ������ ������.\n"
		"2 - �������� ����� � ����� ������.");
	do
	{
		printf("\n������� ��� ����������: ");
		if (scanf("%d", &addType) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (addType < 1 || addType > 2)
		{
			printf("\a������! ��� ���� � ����� �������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return addType - 1;
}


//��������: ����� ���� �������� ���� � ����� ������
//�������: ����� ���� ��������
int getDeleteType(void)
{
	int deleteType, isInputCorrect = 0;
	printf("=�������� �����=\n"
		"=����� ���� �������� �����=\n"
		"1 - ������� ������ ����� ������.\n"
		"2 - ������� ��������� ����� ������.");
	do
	{
		printf("\n������� ��� ��������: ");
		if (scanf("%d", &deleteType) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (deleteType < 1 || deleteType > 2)
		{
			printf("\a������! ��� ���� � ����� �������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return deleteType - 1;
}


//��������: ����� ������� �� �����
void reference(void)
{

}