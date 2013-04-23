#include "listlib.h"
#include <iostream>


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
    else //Если список пустой
    {
        temp->Prev=NULL; //Предыдущий элемент указывает в пустоту
        Head=Tail=temp; //Голова=Хвост=тот элемент, что сейчас добавили
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

    else //Если список пустой
    {
        temp->Next=NULL; //Следующий элемент указывает в пустоту
        Head=Tail=temp; //Голова=Хвост=тот элемент, что сейчас добавили
    }
    count++;
}

void List::output() const
{

    Node *temp=Head; //Временно указываем на адрес первого элемента
    while (temp!=NULL) //Пока не встретим пустое значение
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


void List::insert(int pos_begin1)
{
    if(pos_begin1 < 1 || pos_begin1> count + 1)
    {
        cout << "Incorrect position !!!\n";
        return;
    }
    int i = 1;
    Node * Ins = Head;
    while(i < pos_begin1)
    {
        Ins = Ins->Next;
        i++;
    }
    Node * PrevIns = Ins->Prev;
    Node * temp = new Node;
    cout << "Введите новое число: ";
    cin >> temp->x;
    if(PrevIns != 0 && count != 1)
        PrevIns->Next = temp;
    temp->Next = Ins;
    temp->Prev = PrevIns;
    Ins->Prev = temp;

    count++;
}

void List::del(int pos_begin)

{
    if(pos_begin < 1 || pos_begin > count)
    {
        cout<<"Неверная позиция!"<<endl;
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
    // Если удаляем не голову
    if(PrevDel != 0 && count != 1)
        PrevDel->Next = AfterDel;
    // Если удаляем не хвост
    if(AfterDel != 0 && count != 1)
        AfterDel->Prev = PrevDel;
    // Удаляются крайние?
    if(pos_begin == 1)
        Head = AfterDel;
    if(pos_begin == count)
        Tail = PrevDel;
    // Удаление элемента
    delete Del;
    count--;
}


void menu()
{
    List lst; //Объявляем переменную, тип которой есть список
    bool cntinue;
    while(cntinue)
    {

        cout<<"Выберите действие:"<<endl<<"1 - добавить элементы в конец списка"<<endl<<"2 - в начало"<<endl<<"3 - удалить с конца"<<endl<<"4 - удалить с начала"<<endl<<"5 - показать первый элемент"<<endl<<"6 - удаление конкретных элементов"<<endl<<"7 - очистка списка"<<endl<<"8 - вставка элемента"<<endl<<"0 - выход"<<endl;
        int choice, num, member;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cout<<"Сколько элементов вы хотите добавить в конец?"<<endl;
            cin>>num;
            cout<<"Введите "<<num<<" элементов (в конец):"<<endl;
            for (int i=0; i<num; i++)
            {
                cin>>member;
                lst.push_back(member); //Добавляем в список элементы
            }
            cout<<"Список:"<<endl;
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
            cout<<"Список:"<<endl;
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
            lst.onfront();
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
                lst.del(pos_begin);
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

        case 7:
            lst.clear();
            lst.output(); //Отображаем список на экране
            cout<<"Список пуст"<<endl;
            break;

        case 8:
            int pos_begin1;
            cout<<"Введите позицию вставки: ";
            cin>>pos_begin1;
            lst.insert(pos_begin1);
            lst.output();
            break;

        case 0:
            break;
        }
        cout<<"Нажмите 1, если хотите продолжить или 0, если хотите прекратить"<<endl;
        cin>>cntinue;
    }
}
