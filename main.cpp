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

//��������: ����� ���� ���������� ���� � ����� ������
//�������: ����� ���� ����������
int getSortType(void);

//��������: ����� ���� ������ ���� � ����� ������
//�������: ��������� �� ������� ������ ����
int getFitType(char **str);

//��������: ����� ���� ������ ���� � ����� ������
//�������: ��������� �� ������� ������ ����
int getProcType(void);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ��2 ����������� ������ ����� �/�++");
	genresInitialization();

	int word1Ct = 0, word2Ct = 0, isProgEnd = 0, listId, newListId, addType, deleteType, compType, sortType, fitType, isInputCorrect, isCreateNewList, isPrintList;
	void((*addBook[])(Book**)) = {addFirstBook, addLastBook};  //������ ������� ���������� ����
	void((*deleteBook[])(Book**)) = { deleteFirstBook, deleteLastBook };  //������ ������� �������� ����
	int((*compareBooks[])(Book*, Book*)) = {bookTitleCompare, bookAuthorCompare, bookGenreCompare, bookPageCtCompare};  //������ ������� ��������� ����
	int((*isBookFit[])(Book*, char*)) = {isBookTitleFit, isBookAuthorFit, isBookGenreFit};  //������ ������� ������ ���� �� ��������
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
				if (listId != -1)
				{
					heads = deleteList(heads, listId);
					printf("�������� ������ ���������!\n");
				}
				else
					printf("����� � ������� ����.\n");
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
				if (listId != -1)
				{
					system("cls");
					addType = getAddType();
					system("cls");
					addBook[addType](&(*(heads + listId))->head);
					system("cls");
					printf("=���������� �����=\n"
						"���������� ����� ���������!\n");
				}
				else
					printf("����� � ������� ����.\n");
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
				if (listId != -1)
				{
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
					printf("����� � ������� ����.\n");
			}
			else
				printf("\a��� �� ������ ������! ������� �������� ������.\n");
			waitForEnter();
			break;
		case 5: //������ �� �������
			system("cls");
			printf("=������ �� �������=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				system("cls");
				printf("=������ �� �������=\n");
				if (listId != -1)
				{
						printf("1 - ��������� ������ ��� �������.\n"
						"2 - �������� ��������� � ����� ������.\n");

					isInputCorrect = 0;
					do
					{
						printf("������� ���� �������: ");
						if (scanf("%d", &isCreateNewList) != 1)
							printf("\a������! �� ����� �� �����.\n");
						else if (isCreateNewList < 1 || isCreateNewList > 2)
							printf("\a������! ��������� ����� ���� 1 ��� 2");
						else
							isInputCorrect = 1;
						if (!isInputCorrect)
							waitForEnter();
					} while (!isInputCorrect);
					isCreateNewList--;

					if (isCreateNewList)
					{
						heads = addList(heads);
						for (newListId = 0; *(heads + newListId + 1) != nullptr; newListId++) //����� ���������� ������
							;
					}

					system("cls");
					printf("=������ �� �������=\n");
					char *str;
					switch (getProcType())
					{
					case 1:  //���������� ����
						system("cls");
						printf("=������ �� �������=\n"
							"=���������� ����=\n");
						sortType = getSortType();
						if (isCreateNewList)
						{
							((*(heads + newListId))->head) = listCopy((*(heads + listId))->head);
							(*(heads + newListId))->head = sortBooks((*(heads + newListId))->head, compareBooks[sortType]);
						}
						else
							(*(heads + listId))->head = sortBooks((*(heads + listId))->head, compareBooks[sortType]);
						break;
					case 2:  //����� ���� �� ��������
						system("cls");
						printf("=������ �� �������=\n"
							"=����� �� ��������=\n");
						fitType = getFitType(&str);
						if (isCreateNewList)
						{
							((*(heads + newListId))->head) = listCopy((*(heads + listId))->head);
							(*(heads + newListId))->head = findBooks((*(heads + newListId))->head, str, isBookFit[fitType]);
						}
						else
							(*(heads + listId))->head = findBooks((*(heads + listId))->head, str, isBookFit[fitType]);
						break;
					case 3:  //�������� ���� �� ��������
						system("cls");
						printf("=������ �� �������=\n"
							"=����� �� ��������=\n");
						fitType = getFitType(&str);
						if (isCreateNewList)
						{
							((*(heads + newListId))->head) = listCopy((*(heads + listId))->head);
							(*(heads + newListId))->head = deleteBooks((*(heads + newListId))->head, str, isBookFit[fitType]);
						}
						else
							(*(heads + listId))->head = deleteBooks((*(heads + listId))->head, str, isBookFit[fitType]);
						break;
					}
					system("cls");
					printf("=������ �� �������=\n"
						"������ ���������!\n");
				}
				else
					printf("����� � ������� ����.\n");
			}
			else
				printf("\a��� �� ������ ������! ������� �������� ������.\n");
			waitForEnter();
			break;
		case 6: //����� ������
			if (*heads != nullptr)
			{
				system("cls");
				printf("=����� ������=\n");
				listId = setListId(heads);
				if (listId != -1)
				{
					Book *temp = listCopy((*(heads + listId))->head);
					do
					{
						system("cls");
						printf("=����� ������=\n"
							"1 - �������� ��������.\n"
							"2 - ������� ������.\n");
						isInputCorrect = 0;
						do
						{
							printf("�������� �����: ");
							if (scanf("%d", &isPrintList) != 1)
								printf("\a������! �� ����� �� �����.\n");
							else if (--isPrintList < 0 || isPrintList > 1)
								printf("\a������! ������� 1 ��� 2.\n");
							else
								isInputCorrect = 1;
							if (!isInputCorrect)
								waitForEnter();
						} while (!isInputCorrect);

						if (!isPrintList)
						{
							char *str;
							system("cls");
							printf("=����� ������=\n");
							fitType = getFitType(&str);
							temp = findBooks(temp, str, isBookFit[fitType]);
						}
					} while (!isPrintList);
					printBooks(temp);
					freeList(temp);
				}
				else
					printf("����� � ������� ����.\n");
			}
			else
			{
				system("cls");
				printf("=����� ������=\n"
					"��� �� ������ ������! ������� �������� ������.\n");
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


//��������: ����� ���� ���������� ���� � ����� ������
//�������: ����� ���� ����������
int getSortType(void)
{
	int compareType, isInputCorrect = 0;
	printf("=����� ���� ���������� ����=\n"
		"1 - ���������� �� ��������.\n"
		"2 - ���������� �� ������.\n"
		"3 - ���������� �� �����.\n"
		"4 - ���������� �� ���������� ��������� ������.");
	do
	{
		printf("\n������� ��� ����������: ");
		if (scanf("%d", &compareType) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (compareType < 1 || compareType > 4)
		{
			printf("\a������! ��� ���� � ����� �������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return compareType - 1;
}


//��������: ����� ���� ������ ���� � ����� ������
//�������: ��������� �� ������� ������ ����
int getFitType(char **str)
{
	int fitType, isInputCorrect = 0;
	printf("=����� ��������=\n"
		"1 - �� ��������.\n"
		"2 - �� ������.\n"
		"3 - �� �����.\n");
	do
	{
		printf("\n������� ��������: ");
		if (scanf("%d", &fitType) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (fitType < 1 || fitType > 3)
		{
			printf("\a������! ��� �������� � ����� �������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	system("cls");
	switch (fitType)
	{
	case 1:
		*str = setTitleOfBook();
		break;
	case 2:
		*str = setAuthorOfBook();
		break;
	case 3:
		*str = setGenreOfBook();
		break;
	}

	return fitType - 1;
}


//��������: ����� ���� ������ ���� � ����� ������
//�������: ��������� �� ������� ������ ����
int getProcType(void)
{
	int procType, isInputCorrect = 0;
	printf("=����� ���� ��������� ������=\n"
		"1 - ���������� ����.\n"
		"2 - ����� ���� �� ��������.\n"
		"3 - �������� ���� �� ��������.\n");
	do
	{
		printf("\n������� ��� ���������: ");
		if (scanf("%d", &procType) != 1)
		{
			printf("\a������! �� ����� �� �����.\n");
			waitForEnter();
		}
		else if (procType < 1 || procType > 3)
		{
			printf("\a������! ��� ���� � ����� �������.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return procType ;
}


//��������: ����� ������� �� �����
void reference(void)
{

}