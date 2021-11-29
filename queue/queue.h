#ifndef stack_header_included
#define stack_header_included

#include <iostream>

class box
{
public:
   int value;
   box* link;
};

class queue
{
private:
   box* q;
public:
   box* front=NULL;
   box* rear=NULL;
   void add(int val);
   void del();
   void show();
};

void queue::add(int val)
{
    q = new box;
    q->value = val;
    q->link = this->rear;
    this->rear=q;
    if (this->front==NULL)
      this->front = q ;
}

void queue::del()
{
    box* ptr=(this->rear);
    this->rear = this->rear->link ;
    delete ptr;
}

void queue::show()
{
    if(this->rear!=NULL)
    std::cout << this->rear->value << std::endl;
    else std::cout << "Underfolow!!!" << std::endl ;
}

#endif