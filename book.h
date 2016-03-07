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

//Описание: инициализирует массив жанров
void genresInitialization(void);

//Описание: проверка, есть ли жанр в списке жанров
//Возврат: (1/0)
int HasGenresGenre(char *genre);

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

//Описание: вывод массива указателей на книги на экран
void printBooks(Book **books);

//Описание: добавление нового списка в массив списков
//Возврат: указатель на голову списка
BookHead **addHead(BookHead **heads);

//Описание: ввод названия списка
//Возврат: указатель на первый символ строки
char *inputNameOfList(void);

//Описание: проверка, существует ли список с таким же именем
//Возврат: (1/0)
int hasHadsThatName(char *name, BookHead **heads);

#ifndef _BOOK_
#define _BOOK_
#include "book.cpp"
#endif
