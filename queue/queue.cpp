#include <iostream>
#include "queue.h"

int main()
{
    queue hello;
    hello.add(12);
    std::cout << hello.front->value << " " << hello.rear->value << std::endl;
    hello.add(23);
    hello.show();
    hello.add(89);
    hello.del();
    std::cout << hello.front->value << " " << hello.rear->value << std::endl;
    hello.del();
    std::cout << hello.front->value << " " << hello.rear->value << std::endl;
    hello.show();
}