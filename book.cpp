#include <stdio.h>

#include "ndgstrings.h"

#define TITLE_MAX_SIZE 35
#define AUTHOR_NAME_MAX_SIZE 15
#define PAGE_CT_MIN 10
#define PAGE_CT_MAX 500
#define GENRE_MAX_SIZE 30
#define LIST_NAME_MAX_SIZE 25

struct Book {
	char *title;
	char *author;
	char *genre;
	int pageCt;
	Book *next;
};

struct BookHead {
	Book *head;
	char *name;
};

char **genres;

//Описание: ввод названия книги
//Возврат: указатель на первый символ строки
char *setTitleOfBook(void)
{
	char *title = 0;

	printf("=Ввод названия книги=\n"
		"Название книги должно включать не менее 1 и не более %d символов.\n"
		"Все пробельные символы справа и слева от названия книги не учитываются\n"
		"  и будут удалены.", TITLE_MAX_SIZE);
	do
	{
		free(title);
		printf("\n\nВведите название книги: ");
		title = getStr(TITLE_MAX_SIZE);
		if (strlen(title) == TITLE_MAX_SIZE)
			printf("\aВнимание! Количество символов достигло максимума.\n");
		title = deleteSpace(title);
		if (!strlen(title))
		{
			printf("\aОшибка! Название книги должно состоять хотя бы из одного символа.\n");
			waitForEnter();
		}
	} while (!strlen(title));
	printf("Ввод названия завершен!\n");
	waitForEnter();

	return title;
}


//Описание: ввод информации об авторе книги
//Возврат: указатель на первый символ строки
char *setAuthorOfBook(void)
{
	int authorCt, isAuthorHasName, isInputCorrect;
	char *author = 0, *name = 0;

	printf("=Ввод автора книги=\n"
		"Фамилия/псевдоним и имя автора должны состоять из букв латиницы и\n"
		"  кириллицы, и не могут превышать %d символ%s.\n"
		"Фамилия/псевдоним и имя автора начинаются с прописной буквы, а все\n"
		"  остальные символы являются строчными.\n"
		"Имя автора должно быть не менее 2 символов, а его фамилия/псевдоним - 1го.\n"
		"Все пробельные символы в имени и фамилии/псевдониме не\n"
		"  учитываются и будут удалены.\n"
		"Если у книги несколько авторов, то вводится информация только о главном,\n"
		"  или если такого нет, о первом авторе в лексикографическом порядке.", AUTHOR_NAME_MAX_SIZE,
		(AUTHOR_NAME_MAX_SIZE % 10) > 4 ? "ов" : ((AUTHOR_NAME_MAX_SIZE % 10) == 1 ? "" : "а"));

	isInputCorrect = 0;  //ввод кол-ва авторов
	do
	{
		printf("\n\nУ книги есть автор?(Да-1/Нет-0): ");
		if (scanf("%d", &authorCt) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (authorCt != 1 && authorCt != 0)
		{
			printf("\aОшибка! Введите 1 или 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (authorCt)
	{
		do  //ввод фамилии/псевдонима
		{
			free(author);
			printf("\nВведите фамилию/псевдоним автора: ");
			author = getName(AUTHOR_NAME_MAX_SIZE);
			if (!strlen(author))
			{
				printf("\aОшибка! Фамилия/псевдоним автора должны состоять хотя бы из одного символа.\n");
				waitForEnter();
			}
			else if (strlen(author) == AUTHOR_NAME_MAX_SIZE)
			{
				printf("\aВнимание! Количество символов достигло максимума.\n");
			}
		} while (!strlen(author));

		*author = toUpper(*author);  //экранирование фамилии/псевдонима
		for (int i = 1; *(author + i) != '\0'; i++)
			*(author + i) = toLower(*(author + i));

		printf("Ввод фамилии/псевдонима автора завершен!\n");
		waitForEnter();

		isInputCorrect = 0;  //проверка наличия имени
		do
		{
			printf("\n\nУ автора есть имя?(Да-1/Нет-0): ");
			if (scanf("%d", &isAuthorHasName) != 1)
			{
				rewind(stdin);
				printf("\aОшибка! Вы ввели не число.\n");
				waitForEnter();
				isAuthorHasName = -1;
			}
			else if (isAuthorHasName != 1 && isAuthorHasName != 0)
			{
				printf("\aОшибка! Введите 1 или 0.\n");
				waitForEnter();
			}
			else isInputCorrect = 1;
		} while (!isInputCorrect);

		if (isAuthorHasName)
		{
			do  //ввод имени
			{
				free(name);
				printf("\nВведите имя автора: ");
				name = getName(AUTHOR_NAME_MAX_SIZE);
				if (strlen(name) < 2)
				{
					printf("\aОшибка! Имя автора должно состоять хотя бы из двух символов.\n");
					waitForEnter();
				}
				else if (strlen(name) == AUTHOR_NAME_MAX_SIZE)
				{
					printf("\aВнимание! Количество символов достигло максимума.\n");
				}
			} while (strlen(name) < 2);

			*name = toUpper(*name); //экранирование имени
			for (int i = 1; *(name + i) != '\0'; i++)
				*(name + i) = toLower(*(name + i));

			author = strAddition(author, " ");  //конкатенация фамилии/псевдонима и имени
			author = strAddition(author, name);
			free(name);
		}
	}
	else
		author = "нет автора";
	printf("Ввод автора завершен!\n");
	waitForEnter();
	return author;
}


//Описание: ввод количества авторских листов книги
//Возврат: количество авторских листов книги
int setPageCtOfBook(void)
{
	int pageCt, isInputCorrect;

	printf("=Ввод количества авторских листов книги=\n"
		"Количество авторских листов должно быть не менее %d и не более %d.", PAGE_CT_MIN, PAGE_CT_MAX);
	isInputCorrect = 0;
	do
	{
		printf("\n\nВведите количество авторских листов: ");
		if (scanf("%d", &pageCt) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			pageCt = -1;
		}
		else if (pageCt < PAGE_CT_MIN)
		{
			printf("\aОшибка! Количество авторских листов не может быть меньше %d.\n", PAGE_CT_MIN);
			waitForEnter();
		}
		else if (pageCt > PAGE_CT_MAX)
		{
			printf("\aОшибка! Количество авторских листов не может быть больше %d.\n", PAGE_CT_MAX);
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	printf("Ввод завершен!\n");
	waitForEnter();
	return pageCt;
}


//Описание: ввод жанра книги
//Возврат: указатель на первый символ строки
char *setGenreOfBook(void)
{
	int isBookHasGenre, genreId, isInputCorrect;
	char *genre;

	printf("=Ввод жанра книги=\n");
	
	isInputCorrect = 0;
	do
	{
		printf("У книги есть жанр?(1-Да/0-Нет): ");
		if (scanf("%d", &isBookHasGenre) != 1)
		{
			rewind(stdin);
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
			isBookHasGenre = -1;
		}
		else if (isBookHasGenre != 0 && isBookHasGenre != 1)
		{
			printf("\aОшибка! Введите 1 или 0.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	if (isBookHasGenre)
	{
		printf("\n"); //Вывод списка жанров
		for (int i = 0; i < genresCt(); i++)
			printf("%d-%s  %c", i+1, *(genres + i), i % 5 == 4 ? '\n' : ' ');
		
		isInputCorrect = 0;
		do //Ввод номера жанра из списка
		{
			printf("\n\nВведите номер жанра из списка или 0, если хотите ввести новый жанр: ");
			if (scanf("%d", &genreId) != 1)
			{
				rewind(stdin);
				printf("\aОшибка! Вы ввели не число.\n");
				waitForEnter();
				genreId = -1;
			}
			else if (genreId < 0 || genreId > genresCt())
			{
				printf("\aОшибка! Такого номера жанра нет.\n");
				waitForEnter();
			}
			else
				isInputCorrect = 1;
		} while (!isInputCorrect);

		if (genreId)
			genre = *(genres + genreId - 1);
		else
		{
			genre = inputGenre();
			if (HasGenresGenre(genre))
				printf("\aВнимание! Жанр не добавлен, так как уже есть в списке жанров.\n");
			else
				addGenre(genre);
		}
	}
	else
		genre = "нет жанра";

	printf("Ввод жанра завершен!\n");
	waitForEnter();

	return genre;
}

//Описание: поиск количества жанров в массиве жанров
//Возврат: количество жанров
int genresCt(void)
{
	int res;
	for (res = 0; strlen(*(genres + res)); res++);
	return res;
}


//Описание: инициализирует массив жанров
void genresInitialization(void)
{
	//Обязательно оставлять нулевую строку для обозначения конца массива
	char *genres2[] = { "анекдоты", "античная литература", "военная история", "бизнес-литература", "история",
		"классическая литература", "компьютерная литература", "детектив", "рассказ", "роман", "лирика",
		"политическая литература", "проза", "сказки", "словарь", "поэзия", "обучение", "философия", "фантастика",
		"скетч", "эпопея", "эпос", "эссе", ""};
	int gCt = 0;

	while (strlen(*(genres2 + gCt)))  //поиск количества жанров
		gCt++;
	
	genres = (char**)malloc(sizeof(char*) * (gCt + 1));
	
	for (int i = 0; i < gCt; i++)
		*(genres + i) = genres2[i];
	*(genres + gCt) = "";
}


//Описание: проверка, есть ли жанр в списке жанров
//Возврат: (1/0)
int HasGenresGenre(char *genre)
{
	int res = 0;
	for (int i = 0; i < genresCt() && !res; i++)
		if (!strcmp(*(genres + i), genre))
			res = 1;
	return res;
}


//Описание: ввод нового жанра книги
//Возврат: указатель на первый символ строки
char *inputGenre(void)
{
	char *genre = 0;
	int hyphenCt, spaceCt, isHyphenNeareSpace, isInputFit, isInputCorrect;

	printf("Название жанра может состоять из символов кириллицы, одного\n"
		"  дефиса и одного пробела. Дефис и пробел не могут стоять рядом.\n"
		"Название жанра должно включать не менее 2 и не более %d символов.\n"
		"Все прописные символы будут преобразованы в строчные.", GENRE_MAX_SIZE);

	do
	{
		free(genre);
		hyphenCt = 0, spaceCt = 0, isHyphenNeareSpace = 0, isInputFit = 1;

		printf("\n\nВведите название жанра: ");
		genre = getStr(GENRE_MAX_SIZE);

		if (strlen(genre) == GENRE_MAX_SIZE)
			printf("\aВнимание! Количество символов достигло максимума.\n");

		genre = deleteSpace(genre);
		for (int i = 0; *(genre + i) != '\0'; )  //Преобразование рядом стоящих пробелов в один
			if (*(genre + i) == ' ' && *(genre + i + 1) == ' ')
				deleteChar(genre, i);
			else
				i++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //Подсчет количества дефисов и пробелов
			if (*(genre + i) == ' ')
				spaceCt++;
			else if (*(genre + i) == '-')
				hyphenCt++;
		for (int i = 0; *(genre + i) != '\0'; i++)  //Проверка, стоят ли рядом пробел и дефис
			if ((*(genre + i) == ' ' && *(genre + i + 1) == '-') || (*(genre + i) == '-' && *(genre + i + 1) == ' '))
				isHyphenNeareSpace = 1;
		for (int i = 0; *(genre + i) != '\0'; i++) //Проверка, удовлетворяют ли все символы условию
			if (!((*(genre + i) >= 'А' && *(genre + i) <= 'я') || *(genre + i) == ' ' || *(genre + i) == '-'))
				isInputFit = 0;

		for (int i = 0; *(genre + i) != '\0'; i++)  //экранирование названия жанра
			*(genre + i) = toLower(*(genre + i));

		isInputCorrect = 0;
		if (strlen(genre) < 2)
		{
			printf("\aОшибка! Количество символов должно быть не менее двух.\n");
			waitForEnter();
		}
		else if (!isInputFit)
		{
			printf("\aОшибка! Название жанра может состоять только из символов кириллицы,\n"
				"  пробела или дефиса.\n");
			waitForEnter();
		}
		else if (hyphenCt > 1)
		{
			printf("\aОшибка! В названии жанра может быть только один дефис.\n");
			waitForEnter();
		}
		else if (spaceCt > 1)
		{
			printf("\aОшибка! В названии жанра может быть только один пробел.\n");
			waitForEnter();
		}
		else if (isHyphenNeareSpace)
		{
			printf("\aОшибка! Дефис и пробел не могут стоять рядом.\n");
			waitForEnter();
		}
		else if (*(genre) == '-' || *(genre + strlen(genre) - 1) == '-')
		{
			printf("\aОшибка! Дефис должен стоять между буквами.\n");
			waitForEnter();
		}
		else if (!strcmp(genre, "нет жанра"))
		{
			printf("\aОшибка! Хорошая попытка, но так нельзя.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	/*printf("Ввод завершен!\n");
	waitForEnter();*/

	return genre;
}


//Описание: добавление жанра в массив жанров
void addGenre(char *genre)
{
	int genrCt = genresCt() + 1;
	genres = (char**)realloc(genres, sizeof(char*) * (genrCt + 1));
	*(genres + genrCt - 1) = genre;
	*(genres + genrCt) = "";
}


//Описание: ввод данных новой книги
//Возврат: указатель на книгу
Book *inputBook(void)
{
	Book *book = (Book*)malloc(sizeof(Book));

	printf("==Ввод данных о новой книге==\n");
	book->title = setTitleOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->author = setAuthorOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->genre = setGenreOfBook();
	system("cls");
	printf("==Ввод данных о новой книге==\n");
	book->pageCt = setPageCtOfBook();
	book->next = nullptr;

	system("cls");
	printf("==Ввод данных о новой книге==\n"
		"Ввод данных о новой книге завершен!\n");
	waitForEnter();

	return book;
}


//Описание: вывод списка книг на экран
//Возврат: количество книг в списке
int printBooks(Book *head)
{
	int i = 0, bookPrintCt, pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	system("cls");
	printf("==Вывод списка==");
	if (head == nullptr)
		printf("\nСписок пуст.\n");
	else
	{
		do
		{
			printf("\n\nСколько книг за один вывод вы хотите видеть?: ");
			if (scanf("%d", &bookPrintCt) != 1)
			{
				rewind(stdin);
				printf("\aОшибка! Вы ввели не число.\n");
				waitForEnter();
				bookPrintCt = -1;
			}
			else if (bookPrintCt <= 0)
			{
				printf("\aОшибка! Число должно быть больше 0.\n");
				waitForEnter();
			}
		} while (bookPrintCt <= 0);

		system("cls");
		printf("==Вывод списка==\n"
			"Книги будут выводиться по %d за раз. Для продолжения вывода нажимайте\n"
			"  клавишу space.\n\n", bookPrintCt);

		printHeadOfTable();
		while (head != nullptr)
		{
			i++;
			printf("|%-5d|%-*s|%-*s|%-*s|%-*d|\n",i, TITLE_MAX_SIZE, head->title, AUTHOR_NAME_MAX_SIZE * 2 + 1, head->author,
				GENRE_MAX_SIZE, head->genre, pageCtRank, head->pageCt);
			head = head->next;
			if (i % bookPrintCt == 0)
				while (_getch() != ' ')
					;
		}
		endPrintOfTable();
		printf("Вывод данных завершен!\n");
	}
	waitForEnter();
	return i;
}


//Описание: вывод шапки таблицы на экран
void printHeadOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	printf(" _____ ");  //верхняя строка
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf(" ");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("\n");

	printf("|%-5s|%-*s|%-*s|%-*s|%-*s|\n","Номер", TITLE_MAX_SIZE, "Название", AUTHOR_NAME_MAX_SIZE * 2 + 1, "Автор",
		GENRE_MAX_SIZE, "Жанр", pageCtRank, "АЛ");

	printf("|_____|");  //нижняя строка
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("|\n");
}


//Описание: закрывает таблицу
void endPrintOfTable(void)
{
	int pageCt = PAGE_CT_MAX, pageCtRank = 0;
	while (pageCt) //подсчет максимальной разрядности количества авторских листов
		pageCt /= 10, pageCtRank++;

	printf("|_____|");
	for (int i = 0; i < TITLE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < AUTHOR_NAME_MAX_SIZE * 2 + 1; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < GENRE_MAX_SIZE; i++)
		printf("_");
	printf("|");
	for (int i = 0; i < pageCtRank; i++)
		printf("_");
	printf("|\n");
}


//Описание: добавление нового списка в массив списков
//Возврат: указатель на голову первого списка
BookHead **addList(BookHead **heads)
{
	char *name;

	int i = -1;
	while (*(heads + ++i) != nullptr)
		;
	heads = (BookHead**)realloc(heads, sizeof(BookHead*) * (i + 2));

	system("cls");
	printf("=Добавление списка=\n");
	while (hasHadsThatName(name = inputNameOfList(), heads))
	{
		printf("\aОшибка! Уже есть список с таким именем.\n");
		waitForEnter();
		system("cls");
		printf("=Добавление списка=\n");
	}
	
	*(heads + i) = (BookHead*)malloc(sizeof(BookHead));
	(*(heads + i))->name = name;
	(*(heads + i))->head = nullptr;
	*(heads + i + 1) = nullptr;

	printf("Добавление списка завершено!\n");
	waitForEnter();
	
	return heads;
}


//Описание: удаление списка
//Возврат: указатель на голову первого списка
BookHead **deleteList(BookHead **heads, int listId)
{
	freeList((*(heads + listId))->head);
	free(*(heads + listId));
	int i = listId;
	do
	{
		*(heads + i) = *(heads + i + 1);
	} while (*(heads + i++) != nullptr);
	heads = (BookHead**)realloc(heads, sizeof(BookHead*) * i);
	return heads;
}


//Описание: ввод названия списка
//Возврат: указатель на первый символ строки
char *inputNameOfList(void)
{
	int isInputCorrect = 0, isInputFit, spaceCt;
	char *name;

	printf("=Ввод названия списка=\n"
		"Название списка может состоять из символов кирилицы и одного пробела.\n"
		"Все прописные буквы будут преобразованы в строчные.\n"
		"Минимальная длинна названия списка - 3 символа.");
	do
	{
		isInputFit = 1, spaceCt = 0;

		printf("\nВведие название списка: ");
		name = getStr(LIST_NAME_MAX_SIZE);
		if (strlen(name) == LIST_NAME_MAX_SIZE)
			printf("\aВнимание! Количество символов достигло максимума.\n");

		name = deleteSpace(name);

		for (int i = 1; *(name + i) != '\0'; i++) //Экранирование символов
			*(name + i) = toLower(*(name + i));
		for (int i = 0; *(name + i) != '\0'; )  //Преобразование рядом стоящих пробелов в один
			if (*(name + i) == ' ' && *(name + i + 1) == ' ')
				deleteChar(name, i);
			else
				i++;

		for (int i = 0; *(name + i) != '\0'; i++) //Проверка, удовлетворяют ли все символы условию
			if (!((*(name + i) >= 'А' && *(name + i) <= 'я') || *(name + i) == ' '))
				isInputFit = 0;

		for (int i = 0; *(name + i) != '\0'; i++)  //Подсчет количества дефисов и пробелов
			if (*(name + i) == ' ')
				spaceCt++;

		if (!isInputFit)
		{
			printf("\aОшибка! Название списка может состоять только из символов кирилицы и одного пробела.\n");
			waitForEnter();
		}
		else if (strlen(name) < 3)
		{
			printf("\aОшибка! Количество символов должно быть не менее трех.\n");
			waitForEnter();
		}
		else if (spaceCt > 1)
		{
			printf("\aОшибка! Количество пробелов не должно превышать 1.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);

	return name;
}


//Описание: проверка, существует ли список с таким же именем
//Возврат: (1/0)
int hasHadsThatName(char *name, BookHead **heads)
{
	int i = 0, res = 0;
	while (*(heads + i) != nullptr && !res)
	{
		if (!strcmp(name, (*(heads + i))->name))
			res = 1;
		i++;
	}
	return res;
}


//Описание: выбор списка
//Возврат: порядковый номер списка
int setListId(BookHead **heads)
{
	int i = 0, listId, isInputCorrect = 0;

	while (*(heads + i) != nullptr)
	{
		printf("%d - %s.\n", i + 1, (*(heads + i))->name);
		i++;
	}
	do
	{
		printf("\nВведите номер списка: ");
		if (scanf("%d", &listId) != 1)
		{
			printf("\aОшибка! Вы ввели не число.\n");
			waitForEnter();
		}
		else if (listId < 1 || listId > i)
		{
			printf("\aОшибка! Списка с таким номером нет.\n");
			waitForEnter();
		}
		else
			isInputCorrect = 1;
	} while (!isInputCorrect);
	return listId - 1;
}


//Описание: добавление книги в начало списка
void addFirstBook(Book **head)
{
	Book *next = *head;
	*head = inputBook();
	(*head)->next = next;
}


//Описание: добавление книги в конец списка
void addLastBook(Book **head)
{
	if (*head != nullptr)
		getLastBook(*head)->next = inputBook();
	else
		*head = inputBook();
}


//Описание: удаление первой в списке книги
void deleteFirstBook(Book **head)
{
	Book *temp = *head;
	*head = (*head)->next;
	free(temp);
}


//Описание: удаление последней в списке книги
void deleteLastBook(Book **head)
{
	Book *temp = getLastBook(*head);
	if ((*head)->next != nullptr)
		getLastButOneBook(*head)->next = nullptr;
	else
		(*head) = nullptr;
	free(temp);
}


//Описание: поиск последней в списке книге
//Возврат: указатель на последнюю книгу в списке
Book *getLastBook(Book *head)
{
	if(head != nullptr)
		while (head->next != nullptr)
			head = head->next;
	return head;
}


//Описание: поиск предпоследней в списке книги
//Возврат: указатель на предпоследнюю в списке книгу
Book *getLastButOneBook(Book *head)
{
	if (head->next == nullptr)
		head = nullptr;
	else
		while (head->next->next != nullptr)
			head = head->next;
	return head;
}


//Описание: поиск номера книги
//Возврат: номер книги
int getBookId(Book *head, Book *book)
{
	int i;
	for (i = 0; head != book; head = head->next)
		i++;
	return i;
}


//Описание: освобождение памяти односвязного списка
void freeList(Book *head)
{
	Book *previous;

	while (head != nullptr)
	{
		previous = head;
		head = head->next;
		free(previous);
	}
}


//Описание: поиск книги по ее номеру в списке
//Возврат: указатель на книгу
Book* getBookById(Book *head, int BookId)
{
	for (int i = 0; i < BookId; i++)
		head = head->next;
	return head;
}


//Описание: ввод номера книги
//Возврат: номер книги
int setBookId(int bookCt)
{
	int bookId, isInputCorrect = 0;
	do
	{
		printf("Введите номер книги: ");
		if (scanf("%d", &bookId) != 1)
			printf("\aОшибка! Вы ввели не число.\n");
		else if (bookId < 0 || bookId > bookCt)
			printf("\aОшибка! Нет такого номера книги.");
		else
			isInputCorrect = 1;
		if (!isInputCorrect)
			waitForEnter();
	} while (!isInputCorrect);
	return bookId;
}


//Описание: перестановка двух книг в списке
Book *swapBooks(Book *head, int i, int j)
{
	Book *iPtr, *iNextPtr, *jNextPtr;
	iPtr = getBookById(head, i);
	iNextPtr = iPtr->next;
	jNextPtr = getBookById(head, j)->next;

	if (i > 0)
		getBookById(head, i - 1)->next = getBookById(head, j);
	else
		head = getBookById(head, j);

	if (i - j != 1)
		getBookById(head, i)->next = iNextPtr;

	getBookById(head, j - 1)->next = iPtr;
	getBookById(head, j)->next = jNextPtr;

	return head;
}


//Описание: сортировка книг в списке
//Возврат: указатель на первую книгу
Book *sortBooks(Book *head, int(*bookCompare)(Book *book1, Book *book2))
{
	Book *book1, *book2;

	book1 = head;
	while (book1 != nullptr)
	{
		book2 = book1->next;
		while (book2 != nullptr)
		{
			if (bookCompare(book1, book2) > 0)
			{
				if (book1 == head)
					head = swapBooks(book1, 0, getBookId(book1, book2));
				else
					getBookById(book1, getBookId(head, book1) - 1)->next = swapBooks(book1, 0, getBookId(book1, book2));
				Book *temp = book1;
				book1 = book2;
				book2 = temp;
			}
			book2 = book2->next;
		}
		book1 = book1->next;
	}
	return head;
}


//Описание: создает копию списка
//Возврат: указатель на первую книгу списка
Book *listCopy(Book *head1)
{
	Book *head2, *temp;
	if (head1 == nullptr)
		head2 = nullptr;
	else
	{
		head2 = (Book*)malloc(sizeof(Book));
		temp = head2;
		while (head1->next != nullptr)
		{
			temp->title = head1->title;
			temp->author = head1->author;
			temp->genre = head1->genre;
			temp->pageCt = head1->pageCt;
			temp->next = (Book*)malloc(sizeof(Book));
			temp = temp->next;
			head1 = head1->next;
		}
		temp->title = head2->title;
		temp->author = head2->author;
		temp->genre = head2->genre;
		temp->pageCt = head2->pageCt;
		temp->next = nullptr;
	}
	return head2;
}