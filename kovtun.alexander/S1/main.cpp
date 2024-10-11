#include <iostream>

template< typename T >
struct Node
{
  Node(Node * prev, Node * next, T val) :
    prev(prev),
    next(next),
    val(val)
  {};
  ~Node() = default;

  Node * prev;
  Node * next;
  T val;
};

template< typename T >
class List
{
public:
  List() :
    head_(nullptr),
    tail_(nullptr),
    size_(0)
  {};
  ~List() = default;

private:
  Node< T > * head_;
  Node< T > * tail_;
  size_t size_;
};

template< typename T >
class ConstIterator
{
public:
  using this_t = ConstIterator< T >;

  ConstIterator() :
    node_(nullptr)
  {};
  ~ConstIterator() = default;
  ConstIterator(const this_t &) = default;
  this_t & operator=(const this_t &) = default;

private:
  Node< T > * node_;
};



int main()
{
  List< int > * list = new List< int >();

  return 0;
}
