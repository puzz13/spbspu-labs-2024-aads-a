#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list.hpp>

namespace nikitov
{
  template< class T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& other) = default;
    Queue(Queue< T >&& other) noexcept;
    ~Queue() = default;

    Queue< T >& operator=(const Queue< T >& other) = default;
    Queue< T >& operator=(Queue< T >&& other) noexcept;

    void push(const T& value);
    T drop();

    size_t size() const noexcept;
    bool empty() const noexcept;

  private:
    List< T > data_;
  };

  template< class T >
  Queue< T >::Queue(Queue< T >&& other) noexcept:
    data_(std::move(other.data_))
  {}

  template< class T >
  Queue< T >& Queue< T >::operator=(Queue< T >&& other) noexcept
  {
    if (std::addressof(other) != this)
    {
      std::swap(data_, other.data_);
      other.data_.clear();
    }
    return *this;
  }

  template< class T >
  void Queue< T >::push(const T& value)
  {
    data_.push_front(value);
  }

  template< class T >
  T Queue< T >::drop()
  {
    T value = data_.back();
    data_.pop_back();
    return value;
  }

  template< class T >
  size_t Queue< T >::size() const noexcept
  {
    return data_.size();
  }

  template< class T >
  bool Queue< T >::empty() const noexcept
  {
    return data_.empty();
  }
}
#endif
