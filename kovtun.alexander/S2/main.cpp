#include <iostream>
#include <cassert>

#include "stack.hpp"
#include "queue.h"

bool isOperation(char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

bool isOpenPar(char c)
{
  return c == '(';
}

bool isClosePar(char c)
{
  return c == ')';
}

int getPriority(char c)
{
  if (!isOperation(c))
  {
    return -1;
  }

  if (c == '+' || c == '-')
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

enum class TokenType
{
  PARENTHESIS = 0,
  OPERATOR = 1,
  OPERAND = 2
};

union TokenValue
{
  char c;
  size_t ll;
};

struct Token
{
  TokenType type;
  TokenValue value;
};

int main()
{
  kovtun::Stack< size_t > result;

  std::cin >> std::noskipws;
  while (!std::cin.eof())
  {
    kovtun::Queue< Token > postfixExpression;
    kovtun::Stack< Token > operationHandler;
    char c = 0;

    while (std::cin && c != '\n')
    {
      std::cin >> c;

      if (c == ' ')
      {
        continue;
      }

      if (isOpenPar(c))
      {
        Token t = {TokenType::PARENTHESIS, c};
        operationHandler.push(t);
      }

      if (isClosePar(c))
      {
        Token stackOperation = operationHandler.top();
        while (stackOperation.type != TokenType::PARENTHESIS)
        {
          operationHandler.pop();
          postfixExpression.push(stackOperation);

          if (operationHandler.empty())
          {
            std::cerr << "invalid expression: check parenthesis location\n";
            return 1;
          }
          stackOperation = operationHandler.top();
        }

        operationHandler.pop();
      }

      if (isOperation(c))
      {
        Token queueOperation = {TokenType::OPERATOR, c};
        if (operationHandler.empty())
        {
          operationHandler.push(queueOperation);
          continue;
        }

        Token stackOperation = operationHandler.top();
        while (stackOperation.type == TokenType::OPERATOR)
        {
          if (getPriority(queueOperation.value.c) > getPriority(stackOperation.value.c))
          {
            break;
          }
          operationHandler.pop();
          postfixExpression.push(stackOperation);

          if (operationHandler.empty())
          {
            break;
          }
          stackOperation = operationHandler.top();
        }

        operationHandler.push(queueOperation);
      }

      if (isdigit(c))
      {
        Token t = {TokenType::OPERAND};
        std::string num;
        while (c != ' ' && c != '\n')
        {
          num.push_back(c);
          std::cin >> c;
        }

        try
        {
          t.value.ll = std::stoll(num);
        }
        catch (...)
        {
          std::cerr << "invalid operand's type\n";
          return 1;
        }

        postfixExpression.push(t);
      }
    }

    while (!operationHandler.empty())
    {
      Token t = operationHandler.top();
      postfixExpression.push(t);
      operationHandler.pop();
    }

    while (!postfixExpression.empty())
    {
      if (postfixExpression.front().type == TokenType::OPERAND)
      {
        std::cout << postfixExpression.front().value.ll << " ";
      }
      else
      {
        std::cout << postfixExpression.front().value.c << " ";
      }
      postfixExpression.pop();
    }
    std::cout << "\n";
  }

  return 0;
}
