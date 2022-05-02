#include <iostream>
#include "array.h"
#include "string.h"
#include <vector>
#include "list.h"

bool fun(int b)
{
  return b < 4;
}
int main()
{
  try
  {
    ds::list<int> ls;


    ls.push_back(3);
    ls.push_back(3);
    ls.push_back(3);
    ls.replace(3, 1);
    ls.display();
  }

  catch (std::exception &e)
  {
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
  }
}

// std::ifstream ifs{"mark2"};

// Marks marks;
// ifs >> marks;
// std::string s = "test";
// Student stud(1, s, s, Date(Month(2), 2,1999), Date( Month(1), 1,2005), marks);
// stud.symbolic_print(std::cout);