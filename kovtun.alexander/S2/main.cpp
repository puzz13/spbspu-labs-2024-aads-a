#include <iostream>
#include <cassert>

#include "stack.hpp"
#include "queue.h"

int main()
{
  kovtun::Stack< int > stack;

  for (int i = 0; i < 10; i++)
  {
    stack.push_back(i);
    stack.pop_back();
    stack.push_back(i + 1);
  }

  assert(stack.size() == 10);

  kovtun::Queue< int > queue;

  for (int i = 0; i < 10; i++)
  {
    queue.push_back(i);
    queue.pop_front();
    queue.push_back(i + 1);
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
