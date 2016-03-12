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

//��������: ������������� ������� ������
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
//�������: ���������� ���� � ������
int printBooks(Book *head);

//��������: ���������� ������ ������ � ������ �������
//�������: ��������� �� ������ ������
BookHead **addList(BookHead **heads);

//��������: ���� �������� ������
//�������: ��������� �� ������ ������ ������
char *inputNameOfList(void);

//��������: ��������, ���������� �� ������ � ����� �� ������
//�������: (1/0)
int hasHadsThatName(char *name, BookHead **heads);

//��������: ����� ������
//�������: ���������� ����� ������
int setListId(BookHead **heads);

//��������: ���������� ����� � ������ ������
void addFirstBook(Book **head);

//��������: ���������� ����� � ����� ������
void addLastBook(Book **head);

//��������: �������� ������ � ������ �����
void deleteFirstBook(Book **head);

//��������: �������� ��������� � ������ �����
void deleteLastBook(Book **head);

//��������: ����� ��������� � ������ �����
//�������: ��������� �� ��������� ����� � ������
Book *getLastBook(Book *head);

//��������: ����� ������������� � ������ �����
//�������: ��������� �� ������������� � ������ �����
Book *getLastButOneBook(Book *head);

//��������: ����� ������ �����
//�������: ����� �����
int getBookId(Book *head, Book *book);

//��������: ������������ ������ ������������ ������
void freeList(Book *head);

//��������: ����� ����� �� �� ������ � ������
//�������: ��������� �� �����
Book* getBookById(Book *head, int BookId);

//��������: �������� ������
//�������: ��������� �� ������ ������� ������
BookHead **deleteList(BookHead **heads, int listId);

//��������: ���� ������ �����
//�������: ����� �����
int setBookId(int bookCt);

//��������: ������������ ���� ���� � ������
Book *swapBooks(Book *head, int i, int j);

//��������: ���������� ���� � ������
//�������: ��������� �� ������ �����
Book *sortBooks(Book *head, int(*bookCompare)(Book *book1, Book *book2));

//��������: ������� ����� ������
//�������: ��������� �� ������ ����� ������
Book *listCopy(Book *head1);

#ifndef _BOOK_
#define _BOOK_
#include "book.cpp"
#endif
