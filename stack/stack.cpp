#include <iostream>
#include "stack.h"

int main()
{
	stack<double> hello;
	hello.push(112.123);
	hello.push(13);
	hello.top();
	hello.pop();
	hello.top();
	hello.pop();
	hello.top();
	hello.push(123);
	hello.top();
}