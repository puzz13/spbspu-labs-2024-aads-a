#include <iostream>
#include <cassert>

#include "../common/stack.hpp"
#include "../common/queue.h"

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
  long long ll;
};

struct Token
{
  TokenType type;
  TokenValue value;
};

int main()
{
  kovtun::Queue< kovtun::Queue< Token > > expressions;
  while (!std::cin.eof())
  {
    std::cin >> std::noskipws;
    kovtun::Queue< Token > postfixExpression;
    kovtun::Stack< Token > operationHandler;
    char c = 0;

    while (std::cin >> c && c != '\n')
    {
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
        Token t = { TokenType::OPERAND };
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

      if (c == '\n')
      {
        break;
      }
    }

    while (!operationHandler.empty())
    {
      Token t = operationHandler.top();
      postfixExpression.push(t);
      operationHandler.pop();
    }

    if (!postfixExpression.empty())
    {
      expressions.push(postfixExpression);
    }
  }

  kovtun::Stack< long long > result;
  while (!expressions.empty()) {
    kovtun::Stack<Token> counter;
    auto postfixExpression = expressions.front();

    while (!postfixExpression.empty()) {
      Token t = postfixExpression.front();

      if (t.type == TokenType::OPERAND) {
        counter.push(t);
      }

      if (t.type == TokenType::OPERATOR) {
        long long operands[2] = {0, 0};
        for (int i = 0; i < 2; i++) {
          if (counter.empty()) {
            std::cerr << "invalid expression\n";
            return 1;
          }

          auto operand = counter.top();
          if (operand.type != TokenType::OPERAND) {
            std::cerr << "invalid expression\n";
            return 1;
          }

          operands[1 - i] = operand.value.ll;
          counter.pop();
        }

        char _operator = t.value.c;
        long long result = 0;

        const long long min = std::numeric_limits< long long >::min();
        const long long max = std::numeric_limits< long long >::max();
        if (_operator == '+')
        {
          if (max - operands[0] < operands[1])
          {
            std::cerr << "overflow\n";
            return 1;
          }
          result = operands[0] + operands[1];
        }
        else if (_operator == '-')
        {
          if (min + operands[0] > operands[1])
          {
            std::cerr << "overflow\n";
            return 1;
          }
          result = operands[0] - operands[1];
        }
        else if (_operator == '*')
        {
          if (max / operands[1] < operands[0])
          {
            std::cerr << "overflow\n";
            return 1;
          }

          if (operands[1] != 0 && min / operands[1] > operands[0])
          {
            std::cerr << "underflow\n";
            return 1;
          }
          result = operands[0] * operands[1];
        }
        else if (_operator == '/')
        {
          if (operands[1] == 0)
          {
            std::cerr << "zero division\n";
            return 1;
          }

          if (operands[1] == -1 && operands[0] == min)
          {
            std::cerr << "overflow\n";
            return 1;
          }
          result = operands[0] / operands[1];
        }
        else if (_operator == '%')
        {
          if (operands[1] == 0)
          {
            std::cerr << "zero division\n";
            return 1;
          }

          const long long mod = operands[0] % operands[1];
          if (mod < 0)
          {
            result += mod;
          }

          result = operands[0] % operands[1];
        }

        Token resultToken = {TokenType::OPERAND};
        resultToken.value.ll = result;
        counter.push(resultToken);
      }

      postfixExpression.pop();
    }

    if (counter.size() != 1) {
      std::cerr << "invalid expression\n";
      return 1;
    }

    auto expressionResult = counter.top();
    result.push(expressionResult.value.ll);
    expressions.pop();
  }

  while (!result.empty())
  {
    std::cout << result.top();
    result.pop();
    if (!result.empty())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  return 0;
}
