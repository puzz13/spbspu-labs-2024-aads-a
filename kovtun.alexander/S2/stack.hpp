#ifndef STACK_HPP
#define STACK_HPP

#include "../common/list/list.hpp"

namespace kovtun
{
  template< typename T >
  class Stack
  {
  public:
    Stack() = default;
    ~Stack() = default;
    
    void push(const T & val);
    void pop();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > list_;
  };

  template< typename T >
  void Stack< T >::push(const T & val)
  {
    list_.push_back(val);
  }

  template< typename T >
  void Stack< T >::pop()
  {
    list_.pop_back();
  }

  template< typename T >
  size_t Stack< T >::size() const noexcept
  {
    return list_.size();
  }

  template< typename T >
  bool Stack< T >::empty() const noexcept
  {
    return size() == 0;
  }
}

#endif
