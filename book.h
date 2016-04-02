extern struct Book;
extern struct BookHead;
extern char **genres;

//Описание: ввод данных новой книги
//Возврат: указатель на книгу
Book *inputBook(void);

//Описание: ввод названия книги
//Возврат: указатель на первый символ строки
char *setTitleOfBook(void);

//Описание: ввод информации об авторе книги
//Возврат: указатель на первый символ строки
char *setAuthorOfBook(void);

//Описание: ввод жанра книги
//Возврат: указатель на первый символ строки
char *setGenreOfBook(void);

//Описание: ввод количества авторских листов книги
//Возврат: количество авторских листов книги
int setPageCtOfBook(void);

//Описание: инициализация массива жанров
void genresInitialization(void);

//Описание: проверка, есть ли жанр в списке жанров
//Возврат: (1/0)
int hasGenresGenre(char *genre);

//Описание: поиск количества жанров в массиве жанров
//Возврат: количество жанров
int genresCt(void);

//Описание: ввод нового жанра книги
//Возврат: указатель на первый символ строки
char *inputGenre(void);

//Описание: добавление жанра в массив жанров
void addGenre(char *genre);

//Описание: вывод шапки таблицы на экран
void printHeadOfTable(void);

//Описание: закрывает таблицу
void endPrintOfTable(void);

//Описание: вывод списка книг на экран
//Возврат: количество вниг в списке
int printBooks(Book *head);

//Описание: добавление нового списка в массив списков
//Возврат: указатель на голову списка
BookHead **addList(BookHead **heads);

//Описание: ввод названия списка
//Возврат: указатель на первый символ строки
char *inputNameOfList(void);

//Описание: проверка, существует ли список с таким же именем
//Возврат: (1/0)
int hasHadsThatName(char *name, BookHead **heads);

//Описание: выбор списка
//Возврат: порядковый номер списка
int setListId(BookHead **heads);

//Описание: добавление книги в начало списка
void addFirstBook(Book **head);

//Описание: добавление книги в конец списка
void addLastBook(Book **head);

//Описание: удаление первой в списке книги
void deleteFirstBook(Book **head);

//Описание: удаление последней в списке книги
void deleteLastBook(Book **head);

//Описание: удаляет книгу из списка
//Возврат: указатель на первую книгу в списке
Book *deleteBookByLink(Book *head, Book *book);

//Описание: поиск последней в списке книги
//Возврат: указатель на последнюю книгу в списке
Book *getLastBook(Book *head);

//Описание: поиск предпоследней в списке книги
//Возврат: указатель на предпоследнюю в списке книгу
Book *getLastButOneBook(Book *head);

//Описание: поиск номера книги
//Возврат: номер книги
int getBookId(Book *head, Book *book);

//Описание: освобождение памяти односвязного списка
void freeList(Book *head);

//Описание: поиск книги по ее номеру в списке
//Возврат: указатель на книгу
Book* getBookById(Book *head, int BookId);

//Описание: удаление списка
//Возврат: указатель на голову первого списка
BookHead **deleteList(BookHead **heads, int listId);

//Описание: ввод номера книги
//Возврат: номер книги
int setBookId(int bookCt);

//Описание: перестановка двух книг в списке по номеру
Book *swapBooksById(Book *head, int i, int j);

//Описание: перестановка двух книг в списке по ссылке
Book *swapBooksByLink(Book *head, Book *book1, Book *book2);

//Описание: сортировка книг в списке
//Возврат: указатель на первую книгу списка
Book *sortBooks(Book *head, int(*cmp1)(Book *book1, Book *book2), int(*cmp2)(Book *book1, Book *book2),
	int isFunc1Increase, int isFunc2Increse);

//Описание: копирует данные из одной книги в другую
void bookCopy(Book *origin, Book *copy);

//Описание: создает копию списка
//Возврат: указатель на первую книгу списка-копии
Book *listCopy(Book *head1);

//Описание: сравнение книг по названию
int bookTitleCompare(Book *book1, Book *book2);

//Описание: сравнение книг по автору
int bookAuthorCompare(Book *book1, Book *book2);

//Описание: сравнение книг по жанру
int bookGenreCompare(Book *book1, Book *book2);

//Описание: сравнение книг по количеству авторских листов
int bookPageCtCompare(Book *book1, Book *book2);

//Описание: поиск книг по критерию
//Возврат: указатель на первую книгу результирующего списка
Book *findBooks(Book *head, char *str, int(*isBookFit)(Book *book, char *str));

//Описание: удаление книг по критерию
//Возврат: указатель на первую книгу результирующего списка
Book *deleteBooks(Book *head, char *str, int(*isBookFit)(Book *book, char *str));

//Описание: проверка, совпадает ли название книги со строкой
//Возврат: (1/0)
int isBookTitleFit(Book *book, char *str);

//Описание: проверка, совпадает ли имя автора книги со строкой
//Возврат: (1/0)
int isBookAuthorFit(Book *book, char *str);

//Описание: проверка, совпадает ли жанр книги со строкой
//Возврат: (1/0)
int isBookGenreFit(Book *book, char *str);

//Описание: освобождение памяти книги
//Возврат: nullptr
void freeBook(Book *book);

//Описание: освобождение памяти структуры BookHead
void freeBookHead(BookHead *bookHead);

//Описание: поиск предшествующей в списке книги
//Возврат: указатель на книгу
Book *getPreviousBook(Book *head, Book *book);

//Описание: перемещает книгу на позицию перед выбранной
//Возврат: указатель на первую книгу списка
Book *moveBook(Book *head, Book *dest, Book *src);

#ifndef _BOOK_
#define _BOOK_
#include "book.cpp"
#endif
