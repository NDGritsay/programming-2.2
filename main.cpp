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

//Описание: вывод меню сортировки книг и выбор пункта
//Возврат: номер типа сортировки
int getSortType(void);

//Описание: вывод меню поиска книг и выбор пункта
//Возврат: указатель на функцию поиска книг
int getFitType(char **str);

//Описание: вывод меню поиска книг и выбор пункта
//Возврат: указатель на функцию поиска книг
int getProcType(void);

int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("title = ЛР2 Односвязные списки языка С/С++");
	genresInitialization();

	int word1Ct = 0, word2Ct = 0, isProgEnd = 0, listId, newListId, addType, deleteType, compType, sortType, fitType, isInputCorrect, isCreateNewList, isPrintList;
	void((*addBook[])(Book**)) = {addFirstBook, addLastBook};  //массив функций добавления книг
	void((*deleteBook[])(Book**)) = { deleteFirstBook, deleteLastBook };  //массив функций удаления книг
	int((*compareBooks[])(Book*, Book*)) = {bookTitleCompare, bookAuthorCompare, bookGenreCompare, bookPageCtCompare};  //массив функций сравнения книг
	int((*isBookFit[])(Book*, char*)) = {isBookTitleFit, isBookAuthorFit, isBookGenreFit};  //массив функций поиска книг по критерию
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
				if (listId != -1)
				{
					heads = deleteList(heads, listId);
					printf("Удаление списка завершено!\n");
				}
				else
					printf("Выход в главное меню.\n");
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
				if (listId != -1)
				{
					system("cls");
					addType = getAddType();
					system("cls");
					addBook[addType](&(*(heads + listId))->head);
					system("cls");
					printf("=Добавление книги=\n"
						"Добавление книги завершено!\n");
				}
				else
					printf("Выход в главное меню.\n");
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
				if (listId != -1)
				{
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
					printf("Выход в главное меню.\n");
			}
			else
				printf("\aНет ни одного списка! Сначала создайте список.\n");
			waitForEnter();
			break;
		case 5: //работа со списком
			system("cls");
			printf("=Работа со списком=\n");
			if (*heads != nullptr)
			{
				listId = setListId(heads);
				system("cls");
				printf("=Работа со списком=\n");
				if (listId != -1)
				{
						printf("1 - совершить работу над списком.\n"
						"2 - записать результат в новый список.\n");

					isInputCorrect = 0;
					do
					{
						printf("Введите ваше решение: ");
						if (scanf("%d", &isCreateNewList) != 1)
							printf("\aОшибка! Вы ввели не число.\n");
						else if (isCreateNewList < 1 || isCreateNewList > 2)
							printf("\aОшибка! Результат может быть 1 или 2");
						else
							isInputCorrect = 1;
						if (!isInputCorrect)
							waitForEnter();
					} while (!isInputCorrect);
					isCreateNewList--;

					if (isCreateNewList)
					{
						heads = addList(heads);
						for (newListId = 0; *(heads + newListId + 1) != nullptr; newListId++) //поиск последнего списка
							;
					}

					system("cls");
					printf("=Работа со списком=\n");
					char *str;
					switch (getProcType())
					{
					case 1:  //сортировка книг
						system("cls");
						printf("=Работа со списком=\n"
							"=Сортировка книг=\n");
						sortType = getSortType();
						if (isCreateNewList)
						{
							((*(heads + newListId))->head) = listCopy((*(heads + listId))->head);
							(*(heads + newListId))->head = sortBooks((*(heads + newListId))->head, compareBooks[sortType]);
						}
						else
							(*(heads + listId))->head = sortBooks((*(heads + listId))->head, compareBooks[sortType]);
						break;
					case 2:  //поиск книг по критерию
						system("cls");
						printf("=Работа со списком=\n"
							"=Поиск по критерию=\n");
						fitType = getFitType(&str);
						if (isCreateNewList)
						{
							((*(heads + newListId))->head) = listCopy((*(heads + listId))->head);
							(*(heads + newListId))->head = findBooks((*(heads + newListId))->head, str, isBookFit[fitType]);
						}
						else
							(*(heads + listId))->head = findBooks((*(heads + listId))->head, str, isBookFit[fitType]);
						break;
					case 3:  //удаление книг по критерию
						system("cls");
						printf("=Работа со списком=\n"
							"=Поиск по критерию=\n");
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
					printf("=Работа со списком=\n"
						"Работа завершена!\n");
				}
				else
					printf("Выход в главное меню.\n");
			}
			else
				printf("\aНет ни одного списка! Сначала создайте список.\n");
			waitForEnter();
			break;
		case 6: //вывод списка
			if (*heads != nullptr)
			{
				system("cls");
				printf("=Вывод списка=\n");
				listId = setListId(heads);
				if (listId != -1)
				{
					Book *temp = listCopy((*(heads + listId))->head);
					do
					{
						system("cls");
						printf("=Вывод списка=\n"
							"1 - Добавить критерий.\n"
							"2 - Вывести список.\n");
						isInputCorrect = 0;
						do
						{
							printf("Сделайте выбор: ");
							if (scanf("%d", &isPrintList) != 1)
								printf("\aОшибка! Вы ввели не число.\n");
							else if (--isPrintList < 0 || isPrintList > 1)
								printf("\aОшибка! Введите 1 или 2.\n");
							else
								isInputCorrect = 1;
							if (!isInputCorrect)
								waitForEnter();
						} while (!isInputCorrect);

						if (!isPrintList)
						{
							char *str;
							system("cls");
							printf("=Вывод списка=\n");
							fitType = getFitType(&str);
							temp = findBooks(temp, str, isBookFit[fitType]);
						}
					} while (!isPrintList);
					printBooks(temp);
					freeList(temp);
				}
				else
					printf("Выход в главное меню.\n");
			}
			else
			{
				system("cls");
				printf("=Вывод списка=\n"
					"\aНет ни одного списка! Сначала создайте список.\n");
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


//Описание: вывод меню сортировки книг и выбор пункта
//Возврат: номер типа сортировки
int getSortType(void)
{
	int compareType, isInputCorrect = 0;
	printf("=Выбор типа сортировки книг=\n"
		"1 - Сортировка по названию.\n"
		"2 - Сортировка по автору.\n"
		"3 - Сортировка по жанру.\n"
		"4 - Сортировка по количеству авторских листов.");
	do
	{
		printf("\nВведите тип сортировки: ");
		if (scanf("%d", &compareType) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (compareType < 1 || compareType > 4)
		{
			printf("\aОшбика! Нет типа с таким номером.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return compareType - 1;
}


//Описание: вывод меню поиска книг и выбор пункта
//Возврат: указатель на функцию поиска книг
int getFitType(char **str)
{
	int fitType, isInputCorrect = 0;
	printf("=Выбор критерия=\n"
		"1 - По названию.\n"
		"2 - По автору.\n"
		"3 - По жанру.\n");
	do
	{
		printf("\nВведите критерий: ");
		if (scanf("%d", &fitType) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (fitType < 1 || fitType > 3)
		{
			printf("\aОшбика! Нет критерия с таким номером.\n");
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


//Описание: вывод меню поиска книг и выбор пункта
//Возврат: указатель на функцию поиска книг
int getProcType(void)
{
	int procType, isInputCorrect = 0;
	printf("=Выбор типа обработки списка=\n"
		"1 - Сортировка книг.\n"
		"2 - Поиск книг по критерию.\n"
		"3 - Удаление книг по критерию.\n");
	do
	{
		printf("\nВведите тип обработки: ");
		if (scanf("%d", &procType) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (procType < 1 || procType > 3)
		{
			printf("\aОшбика! Нет типа с таким номером.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return procType ;
}


//Описание: вывод справки на экран
void reference(void)
{

}