#include <stdio.h>
#include <Windows.h>
#include "ndgstrings.h"
#include "book.h"

//Описание: вывод меню на экран и выбор пункта
//Взоврат: пункт меню
int menu(void);

//Описание: вывод справки на экран
void reference(void);

//Описание: вывод меню добавления книг и выбор пункта
//Возврат: номер типа добовления
int getAddType(void);

//Описание: вывод меню удаления книг и выбор пункта
//Возврат: номер типа удаления
int getDeleteType(void);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ЛР2 Односвязные списки языка С/С++");
	genresInitialization();

	int word1Ct = 0, word2Ct = 0, isProgEnd = 0, listId, addType, deleteType;
	void((*addBook[])(Book**)) = {addFirstBook, addLastBook};  //массив функций добавления книг
	void((*deleteBook[])(Book**)) = { deleteFirstBook, deleteLastBook };  //массив функций удаления книг
	BookHead **heads = (BookHead**)malloc(sizeof(BookHead*));

	*heads = nullptr;

	do
	{
		system("cls");
		switch (menu())
		{
		case 1: //добавление списка
			heads = addList(heads);
			break;
		case 2: //удаление списка
			system("cls");
			printf("=Удаление списка=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				heads = deleteList(heads, listId);
				printf("Удаление списка завершено!\n");
			}
			else
				printf("Нет ни одного списка, чтобы удалить!\n");
			waitForEnter();
			break;
		case 3: //добавление книги
			system("cls");
			printf("=Добавление книги=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				system("cls");
				addType = getAddType();
				system("cls");
				addBook[addType](&(*(heads + listId))->head);
				system("cls");
				printf("=Добавление книги=\n"
					"Добавление книги завершено!\n");
			}
			else
				printf("\aНет ни одного списка! Сначала создайте список.\n");
			waitForEnter();
			break;
		case 4: //удаление книги
			system("cls");
			printf("=Удаление книги=\n");
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
					printf("=Удаление книги=\n"
						"Удаление книги завершено!\n");
				}
				else
					printf("=Удаление книги=\n"
						"\aСписок пуст!\n");
			}
			else
				printf("\aНет ни одного списка! Сначала создайте список.\n");
			waitForEnter();
			break;
		case 5: //работа со списком
			heads = addList(heads);
			(*(heads + 1))->head = listCopy((*(heads))->head);
			/*if (*heads != nullptr)
			{
				system("cls");
				printf("=Работа со списком=\n");
				listId = setListId(heads);
			}
			else
				printf("\aНет ни одного списка! Сначала создайте список.\n");
			waitForEnter();
			break;*/
		case 6: //вывод списка
			system("cls");
			printf("=Вывод списка=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				printBooks((*(heads + listId))->head);
			}
			else
			{
				printf("Нет ни одного списка! Сначала создайте список.\n");
				waitForEnter();
			}
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


//Описание: вывод меню на экран и выбор пункта
//Взоврат: пункт меню
int menu(void)
{
	int res, isInputCorrect = 0;
	printf(
		"=Меню=\n"
		"1 - Добавление списка\n"
		"2 - Удаление списка\n"
		"3 - Добавление книги\n" //первого, последнего, н-ного
		"4 - Удаление книги\n" //первого, последрего, н-ного, по критерию
		"5 - Работа со списком\n"
		"6 - Вывод списка\n" //полностью, по критериям
		"7 - Справка\n"
		"0 - Выход");
	do
	{
		printf("\nВыберите пункт меню: ");
		if (scanf("%d", &res) != 1)
		{
			printf("\aОшбика! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (res < 0 || res > 7)
		{
			printf("\aОшибка! Такого пункта меню нет.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return res;
}


//Описание: вывод меню добавления книг и выбор пункта
//Возврат: номер типа добовления
int getAddType(void)
{
	int addType, isInputCorrect = 0;
	printf("=Добавление книги=\n"
		"=Выбор типа добавления книги=\n"
		"1 - Добавить книгу в начало списка.\n"
		"2 - Добавить книгу в конец списка.");
	do
	{
		printf("\nВведите тип добавления: ");
		if (scanf("%d", &addType) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (addType < 1 || addType > 2)
		{
			printf("\aОшбика! Нет типа с таким номером.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return addType - 1;
}


//Описание: вывод меню удаления книг и выбор пункта
//Возврат: номер типа удаления
int getDeleteType(void)
{
	int deleteType, isInputCorrect = 0;
	printf("=Удаление книги=\n"
		"=Выбор типа удаления книги=\n"
		"1 - Удалить первую книгу списка.\n"
		"2 - Удалить последнюю книгу списка.");
	do
	{
		printf("\nВведите тип удаления: ");
		if (scanf("%d", &deleteType) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (deleteType < 1 || deleteType > 2)
		{
			printf("\aОшбика! Нет типа с таким номером.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return deleteType - 1;
}


//Описание: вывод справки на экран
void reference(void)
{

}