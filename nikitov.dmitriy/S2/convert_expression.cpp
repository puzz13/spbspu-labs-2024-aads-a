#include "convert_expression.hpp"
#include <exception>
#include "queue.hpp"
#include "stack.hpp"
#include "expression_type.hpp"
#include "postfix_expression.hpp"

nikitov::PostfixExpression nikitov::convertExpression(Queue< InfixType > infixExpression)
{
  PostfixExpression postfixExpression;
  Stack< StackType > operandsStack;
  while (!infixExpression.empty())
  {
    InfixType type = infixExpression.drop();
    if (type.typeName != TypeName::operand)
    {
      if (type.typeName == TypeName::bracket)
      {
        if (type.bracket.symb == ')')
        {
          while (!operandsStack.empty() && operandsStack.top().typeName != TypeName::bracket)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = TypeName::operation;
            newPostfixType.operation = operandsStack.drop().operation;
            postfixExpression.add(newPostfixType);
          }
          if (operandsStack.empty())
          {
            throw std::logic_error("Error: Wrong brackets");
          }
          operandsStack.drop();
        }
        else
        {
          StackType newStackType;
          newStackType.typeName = TypeName::bracket;
          newStackType.bracket = type.bracket;
          operandsStack.push(newStackType);
        }
      }
      else
      {
        while (!operandsStack.empty() && operandsStack.top().typeName != TypeName::bracket)
        {
          if (type.operation <= operandsStack.top().operation)
          {
            PostfixType newPostfixType;
            newPostfixType.typeName = TypeName::operation;
            newPostfixType.operation = operandsStack.drop().operation;
            postfixExpression.add(newPostfixType);
          }
          else
          {
            break;
          }
        }
        StackType newStackType;
        newStackType.typeName = TypeName::operation;
        newStackType.operation = type.operation;
        operandsStack.push(newStackType);
      }
    }
    else
    {
      PostfixType newPostfixType;
      newPostfixType.typeName = TypeName::operand;
      newPostfixType.operand = type.operand;
      postfixExpression.add(newPostfixType);
    }
  }

  while (!operandsStack.empty())
  {
    StackType type = operandsStack.drop();
    if (type.typeName == TypeName::bracket)
    {
      throw std::logic_error("Error: Wrong brackets");
    }
    PostfixType newPostfixType;
    newPostfixType.typeName = TypeName::operation;
    newPostfixType.operation = type.operation;
    postfixExpression.add(newPostfixType);
  }
  return postfixExpression;
}
