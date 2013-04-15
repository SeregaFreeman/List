#ifndef LISTLIB_H
#define LISTLIB_H
using namespace std;
typedef int Data;
#ifndef NULL
#define NULL 0
#endif

struct Node       //Структура являющаяся звеном списка
{
    Data x;     //Значение x будет передаваться в список
    Node *Next,*Prev; //Указатели на адреса следующего и предыдущего элементов списка
};

class List   //Создаем тип данных Список
{
    Node *Head,*Tail; //Указатели на адреса начала списка и его конца
    int count;
    int pos_begin, pos_begin1;
public:
    List():Head(NULL),Tail(NULL)
    {count=0;}; //Инициализируем адреса как пустые
    ~List(); //Деструктор
    void output() const; //Функция отображения списка на экране
    void onfront(); //вывод первого значения
    void onback(); //вывод последнего
    void push_back(Data x); //Функция добавления элементов в конец
    void push_front(Data x); //Функция добавления элементов в начало
    void del(int pos_begin); // Удаление узла
    void insert(int pos_begin1); //вставка элемента
    void clear();
    Data pop_back(Data x); //Функция удаления последнего элемента
    Data pop_front(Data x); //Функция удаления первого элемента
};
void menu(); // Вывод менюшки
#endif
