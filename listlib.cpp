#include "listlib.h"
#include <iostream>
#include <exception>


List::~List() //Деструктор
{
    clear();
}

void List::clear()
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail=Head->Next; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head=Tail; //Смена адреса начала на адрес следующего элемента
    }
    count=0;
}

void List::push_back(Data x)
{
    Node *temp=new Node; //Выделение памяти под новый элемент структуры
    temp->Next=NULL;  //Указываем, что изначально по следующему адресу пусто
    temp->x=x;//Записываем значение в структуру

    if (Head!=NULL) //Если список не пуст
    {
        temp->Prev=Tail; //Указываем адрес на предыдущий элемент в соотв. поле
        Tail->Next=temp; //Указываем адрес следующего за хвостом элемента
        Tail=temp; //Меняем адрес хвоста
    }
    else                //Если список пустой
    {
        temp->Prev=NULL; //Предыдущий элемент указывает в пустоту
        Head=Tail=temp;  //Голова=Хвост=тот элемент, что сейчас добавили
    }
    count++;
}

void List::push_front(Data x)
{
    Node *temp=new Node; //Выделение памяти под новый элемент структуры
    temp->Prev=NULL;     //Указываем, что перед элементом пусто
    temp->x=x;           //Записываем значение в структуру

    if (Head!=NULL)      //Если список не пуст
    {
        temp->Next=Head; //Указываем адрес на предыдущий элемент в соотв. поле
        Head->Prev=temp; //Указываем адрес следующего за хвостом элемента
        Head=temp;       //Меняем адрес хвоста
    }

    else                //Если список пустой
    {
        temp->Next=NULL; //Следующий элемент указывает в пустоту
        Head=Tail=temp;  //Голова=Хвост=тот элемент, что сейчас добавили
    }
    count++;
}

void List::output() const
{

    Node *temp=Head;    //Временно указываем на адрес первого элемента
    cout<<endl<<"Список:"<<endl;
    while (temp!=NULL)  //Пока не встретим пустое значение
    {
        cout<<temp->x<<" "; //Выводим каждое считанное значение на экран
        temp=temp->Next; //Смена адреса на адрес следующего элемента
    }
    cout<<endl<<"Элементов в списке: "<<count<<endl;
}

void List::onfront()
{
    Node *temp=Head;
    if (temp)
        cout<<temp->x<<" "<<endl;
}

void List::onback()
{
    Node *temp=Tail;
    if (temp)
        cout<<temp->x<<" "<<endl;
}

Data List::pop_back(Data x)
{
    Node *temp=Tail;
    if(temp)
    {
        Tail=Tail->Prev;
        Data member=temp->x;
        temp->x=0;
        Tail->Next=NULL;
        delete temp;
        temp=NULL;
        count--;
        return member;
    }

    return -1;
}

Data List::pop_front(Data x)
{
    Node *temp=Head;
    if(temp)
    {
        Head=Head->Next;
        Data member=temp->x;
        temp->x=0;
        temp->Prev=NULL;
        delete temp;
        temp=NULL;
        count--;
        return member;
    }

    return -1;
}


void List::insert(int pos_begin)
{
    if(pos_begin < 1 || pos_begin > count)
    {
        throw IncorrectPosition();
    }
    int i = 1;
    Node * Ins = Head;
    while(i < pos_begin)
    {
        Ins = Ins->Next;
        i++;
    }
    Node * PrevIns = Ins->Prev; // создаем указатель на элемент перед инс
    Node * temp = new Node;     // выделяем память под темп
    cout << "Введите новое число: ";
    cin >> temp->x;
    if(PrevIns != 0 && count != 1) // если ячейка перед инс не пустая и в списке Ю 1 элемента
        PrevIns->Next = temp;

    temp->Next = Ins; //после темпа идет инс
    temp->Prev = PrevIns; //перед темпом идет прев инс
    Ins->Prev = temp; //перед инсом идет темп

    count++;
}

void List::del(int pos_begin)

{
    if(pos_begin < 1 || pos_begin > count)
    {
        throw IncorrectPosition();
    }
    int i = 1;
    Node * Del = Head;
    while(i < pos_begin)
    {
        Del = Del->Next;
        i++;
    }
    Node * PrevDel = Del->Prev;
    Node * AfterDel = Del->Next;

    if(PrevDel != 0 && count != 1) // Если удаляем не голову
        PrevDel->Next = AfterDel;

    if(AfterDel != 0 && count != 1) // Если удаляем не хвост
        AfterDel->Prev = PrevDel;

    if(pos_begin == 1)  // Удаляются крайние?
        Head = AfterDel;
    if(pos_begin == count)
        Tail = PrevDel;

    delete Del; // Удаление элемента

    count--;
}


void menu()
{
    List lst; //Объявляем переменную, тип которой есть список
    bool cntinue;
    while(cntinue)
    {

        cout<<"\033[32mВыберите действие:"<<endl<<"1 - добавить элементы в конец списка"<<endl<<"2 - в начало"<<endl<<"3 - удалить элемент с конца"<<endl<<"4 - удалить с начала"<<endl<<"5 - показать первый и последний элементы"<<endl<<"6 - удаление элементов"<<endl<<"7 - очистка списка"<<endl<<"8 - вставка элемента"<<endl<<"0 - выход из программы\033[0m"<<endl;
        int choice, num, member;

        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Сколько элементов вы хотите добавить в конец?"<<endl;
            cin>>num;
            if (num>0)
                cout<<"Введите "<<num<<" элементов (в конец):"<<endl;
            else cerr<<"Ошибка ввода";
            for (int i=0; i<num; i++)
            {
                cin>>member;
                lst.push_back(member); //Добавляем в список элементы
            }
            lst.output(); //Отображаем список на экране
            break;

        case 2:
            cout<<"Сколько элементов вы хотите добавить в начало?"<<endl;
            cin>>num;
            cout<<"Введите элементы (в начало):"<<endl;
            for (int i=0; i<num; i++)
            {
                cin>>member;
                lst.push_front(member); //Добавляем в список элементы
            }

            lst.output(); //Отображаем список на экране
            break;

        case 3:
            cout<<"Удаляем последний элемент..."<<endl;
            lst.pop_back(member);
            cout<<"Последний элемент удален:"<<endl;
            lst.output();
            break;

        case 4:
            cout<<"Удаляем первый элемент..."<<endl;
            lst.pop_front(member);
            cout<<"Первый элемент удален:"<<endl;
            lst.output();
            break;

        case 5:
            cout<<"Первый элемент: "<<endl;
            lst.onfront();
            cout<<"Последний элемент: "<<endl;
            lst.onback();
            break;

        case 6:
            int howmany;
            cout<<"Удаление конкретного элемента"<<endl;
            cout<<"Если вы хотите удалить один элемент, нажмите 1. Если хотите удалить промежуток, нажмите 2."<<endl;
            cin>>howmany;
            switch(howmany)
            {
                int pos_begin, pos_end;
            case 1:
                cout<<"Введите позицию: ";
                cin>>pos_begin;
                try
                {
                    lst.del(pos_begin);
                }
                catch (exception &err)
                {
                    cout<<err.what()<<endl;
                }
                lst.output();
                break;
            case 2:
                cout<<"Введите начальную позицию: ";
                cin>>pos_begin;
                cout<<"Введите конечную позицию: ";
                cin>>pos_end;
                for (int temp=((pos_end-pos_begin)+1); temp>0; temp--)
                {
                    lst.del(pos_begin);
                }
                lst.output();
                break;
            }
            break;

        case 7:
            lst.clear();
            lst.output(); //Отображаем список на экране
            cout<<"Список пуст"<<endl;
            break;

        case 8:
            int pos_begin1, ch;
            cout<<"Нажмите 1, чтобы добавить 1 элемент или нажмите 2, чтобы добавить несколько."<<endl;
            cin>>ch;
            switch(ch)
            {
            case 1:
                cout<<"Введите позицию вставки: ";
                cin>>pos_begin1;
                lst.insert(pos_begin1);
                lst.output();
                break;
            case 2:
                cout<<"\033[32mВведите начальную позицию: ";
                cin>>pos_begin1;
                cout<<"Введите количество элементов: ";
                cin>>num;
                for (int i=0; i<num; i++)
                {
                    lst.insert(pos_begin1);
                }
                lst.output();
                break;
            }
            break;



        case 0:
            break;
        }
        cout<<endl<<"Нажмите 1, если хотите продолжить или 0, если хотите прекратить"<<endl;
        cin>>cntinue;
    }
}
