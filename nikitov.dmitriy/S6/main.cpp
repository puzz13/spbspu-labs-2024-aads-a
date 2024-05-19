#include <iostream>
#include <deque>
#include <forward_list>
#include <algorithm>
#include <iomanip>
#include <list.hpp>
#include "sortings.hpp"
#include "iterators_functions.hpp"
#include "sort_sequence.hpp"

int main(int argc, char* argv[])
{
  using namespace nikitov;
  if (argc != 4)
  {
    std::cerr << "Error: Wrong input parameters" << '\n';
    return 1;
  }

  try
  {
    size_t size = std::stoull(argv[3]);
    if (size == 0)
    {
      throw std::invalid_argument("Error: Wrong size parameter");
    }

    std::string sorting = argv[1];
    std::string type = argv[2];
    if (type == "ints")
    {
      sortSequence< int >(sorting, type, size);
    }
    else if (type == "floats")
    {
      sortSequence< float >(sorting, type, size);
    }
    else
    {
      throw std::invalid_argument("Error: Wrong type parameter");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  return 0;
}
