#include <iostream>
#include <cassert>

#include "stack.hpp"
#include "queue.h"

int main()
{
  kovtun::Stack< int > stack;

  for (int i = 0; i < 10; i++)
  {
    stack.push(i);
    stack.pop();
    stack.push(i + 1);
  }
  stack.top() += 5;

  assert(stack.size() == 10);
  assert(stack.top() == 15);

  kovtun::Queue< int > queue;

  for (int i = 0; i < 10; i++)
  {
    queue.push(i);
    queue.pop();
    queue.push(i + 1);
  }
  queue.front() += 5;
  queue.back() -= 1;

  assert(queue.size() == 10);
  assert(queue.back() == 9);
  assert(queue.front() == 10);

  kovtun::List< int > testList;
  testList.push_back(5);
  testList.front() += 5;
  testList.back() -= 3;

  assert(testList.front() == 7);

  return 0;
}
