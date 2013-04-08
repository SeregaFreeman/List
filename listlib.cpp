#include "listlib.h"
#include <iostream>


List::~List() //Деструктор
{
    while (Head) //Пока по адресу на начало списка что-то есть
    {
        Tail=Head->Next; //Резервная копия адреса следующего звена списка
        delete Head; //Очистка памяти от первого звена
        Head=Tail; //Смена адреса начала на адрес следующего элемента
    }
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
}

void List::push_front(Data x)
{
    Node *temp=new Node; //Выделение памяти под новый элемент структуры
    temp->Prev=NULL;  //Указываем, что перед элементом пусто
    temp->x=x;//Записываем значение в структуру

    if (Head!=NULL) //Если список не пуст
    {
        temp->Next=Head; //Указываем адрес на предыдущий элемент в соотв. поле
        Head->Prev=temp; //Указываем адрес следующего за хвостом элемента
        Head=temp; //Меняем адрес хвоста
    }

    else //Если список пустой
    {
        temp->Prev=NULL; //Предыдущий элемент указывает в пустоту
        Head=Tail=temp; //Голова=Хвост=тот элемент, что сейчас добавили
    }
}

void List::output() const
{

    Node *temp=Head; //Временно указываем на адрес первого элемента
    while (temp!=NULL) //Пока не встретим пустое значение
    {
        cout<<temp->x<<" "; //Выводим каждое считанное значение на экран
        temp=temp->Next; //Смена адреса на адрес следующего элемента
    }
    cout<<"\n";
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
        return member;
    }
    return -1;

}

/*void List::del(Data pos)

{
   // если параметр отсутствует или равен 0, то запрашиваем его
   if(pos == 0)
   {
       cout << "Введите позицию: ";
       cin >> pos;
   }
   // Позиция от 1 до Count?
   if(pos < 1 || pos > count)
   {
      // Неверная позиция
      cout << "Incorrect position !!!\n";
   }

   // Счетчик
   int i = 1;

   Node * Del = Head;

   while(i < pos)
   {
      // Доходим до элемента,
      // который удаляется
      Del = Del->Next;
      i++;
   }

   // Доходим до элемента,
   // который предшествует удаляемому
   Node * PrevDel = Del->Prev;
   // Доходим до элемента, который следует за удаляемым
   Node * AfterDel = Del->Next;

   // Если удаляем не голову
   if(PrevDel != 0 && count != 1)
      PrevDel->Next = AfterDel;
   // Если удаляем не хвост
    if(AfterDel != 0 && count != 1)
      AfterDel->Prev = PrevDel;

   // Удаляются крайние?
   if(pos == 1)
       Head = AfterDel;
   if(pos == count)
       Tail = PrevDel;

   // Удаление элемента
   delete Del;

   count--;
}
*/

void menu()
{
    List lst; //Объявляем переменную, тип которой есть список
    while(1)
    {

    cout<<"Выберите действие: 1 - добавить элементы в конец списка, 2 - в начало, 3 - удалить с конца, 4 - удалить с начала, 5 - показать первый элемент, 7 - очистка, 0 - выход"<<endl;
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

        /*case 6:
         cout<<"Удаление и-того"<<endl;
         lst.del(member);*/

         case 7:
          lst.clear();
          lst.output(); //Отображаем список на экране
          cout<<"Список пуст"<<endl;
         break;

        case 0:
         break;
    }
    }
}
