#include <iostream>
#include <cassert>

#include "stack.hpp"

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

  return 0;
}
