extern struct Book;
extern struct BookHead;
extern char **genres;

//��������: ���� ������ ����� �����
//�������: ��������� �� �����
Book *inputBook(void);

//��������: ���� �������� �����
//�������: ��������� �� ������ ������ ������
char *setTitleOfBook(void);

//��������: ���� ���������� �� ������ �����
//�������: ��������� �� ������ ������ ������
char *setAuthorOfBook(void);

//��������: ���� ����� �����
//�������: ��������� �� ������ ������ ������
char *setGenreOfBook(void);

//��������: ���� ���������� ��������� ������ �����
//�������: ���������� ��������� ������ �����
int setPageCtOfBook(void);

//��������: �������������� ������ ������
void genresInitialization(void);

//��������: ��������, ���� �� ���� � ������ ������
//�������: (1/0)
int HasGenresGenre(char *genre);

//��������: ����� ���������� ������ � ������� ������
//�������: ���������� ������
int genresCt(void);

//��������: ���� ������ ����� �����
//�������: ��������� �� ������ ������ ������
char *inputGenre(void);

//��������: ���������� ����� � ������ ������
void addGenre(char *genre);

//��������: ����� ����� ������� �� �����
void printHeadOfTable(void);

//��������: ��������� �������
void endPrintOfTable(void);

//��������: ����� ������� ���������� �� ����� �� �����
void printBooks(Book *head);

//��������: ���������� ������ ������ � ������ �������
//�������: ��������� �� ������ ������
BookHead **addHead(BookHead **heads);

//��������: ���� �������� ������
//�������: ��������� �� ������ ������ ������
char *inputNameOfList(void);

//��������: ��������, ���������� �� ������ � ����� �� ������
//�������: (1/0)
int hasHadsThatName(char *name, BookHead **heads);

//��������: ����� ������
//�������: ���������� ����� ������
int getListId(BookHead **heads);

//��������: ���������� ����� � ����� ������
void addLastBook(Book **head);

//��������: ����� ��������� � ������ �����
//�������: ��������� �� ��������� ����� � ������
Book *getLastBook(Book *head);

//��������: ����� ������������� � ������ �����
//�������: ��������� �� ������������� � ������ �����
Book *getLastButOneBook(Book *head);

//��������: ���� ������ �����
//�������: ����� �����
int getBookId(int bookCt);

#ifndef _BOOK_
#define _BOOK_
#include "book.cpp"
#endif
