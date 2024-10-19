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

  assert(queue.size() == 10);

  return 0;
}
