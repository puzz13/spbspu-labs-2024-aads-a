#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../common/list/list.hpp"

namespace kovtun
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    ~Queue() = default;

    void push_back(const T & val);
    void pop_front();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > list_;
  };

  template< typename T >
  void kovtun::Queue< T >::push_back(const T & val)
  {
    list_.push_back(val);
  }

  template< typename T >
  void kovtun::Queue< T >::pop_front()
  {
    list_.pop_front();
  }

  template< typename T >
  size_t kovtun::Queue< T >::size() const noexcept
  {
    return list_.size();
  }

  template< typename T >
  bool kovtun::Queue< T >::empty() const noexcept
  {
    return size() == 0;
  }
}

#endif
