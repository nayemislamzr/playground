#ifndef STACK_HEADER_INCLUDED
#define STACK_HEADER_INCLUDED
#include <iostream>

template <typename T>
class stack
{
  public:
  T value;
  stack* link;
  stack<T>* top_node = NULL;
  void push(T val);
  void pop();
  void top();
};

template <typename T>
void stack<T>::push(T val)
{
  stack<T>* new_node = new stack;
  new_node->value = val;
  if(this->top_node)
    new_node->link = top_node ;
  top_node = new_node ;
}

template <typename T>
void stack<T>::pop()
{
   this->top_node = this->top_node->link;
}

template <typename T>
void stack<T>::top()
{
	(this->top_node)?(std::cout << this->top_node->value):std::cout << "Underflow!!!" ;
    std::cout << std::endl ;
}

#endif