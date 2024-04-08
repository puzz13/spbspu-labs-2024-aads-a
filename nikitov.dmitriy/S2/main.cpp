#include <iostream>
#include <fstream>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_types.hpp"
#include "postfix_expression.hpp"
#include "input_expressions.hpp"
#include "convert_expression.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  Queue< Queue< InfixType > > infixQueue;

  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      inputExpressions(infixQueue, input);
    }
    else if (argc == 1)
    {
      inputExpressions(infixQueue, std::cin);
    }
    else
    {
      std::cerr << "Error: Wrong input parameters" << '\n';
      return 1;
    }

    Stack< PostfixExpression > postfixStack;
    while (!infixQueue.empty())
    {
      postfixStack.push(convertExpression(infixQueue.drop()));
    }

    bool isFirst = true;
    while (!postfixStack.empty())
    {
      if (!isFirst)
      {
        std::cout << ' ';
      }
      isFirst = false;
      std::cout << postfixStack.drop().solve();
    }
    std::cout << '\n';
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
