#include <iostream>
#include <source_location/source_location.hpp>

source_location function()
{
  return source_location(source_location::current());
}


void function2(const source_location& loc)
{
  std::cout << loc.file_name() << std::endl;
  std::cout << loc.function_name() << std::endl;
  std::cout << loc.line() << std::endl;
  std::cout << loc.column() << std::endl;
}

int main()
{
  source_location loc = function();
  std::cout << loc.file_name() << std::endl;
  std::cout << loc.function_name() << std::endl;
  std::cout << loc.line() << std::endl;
  std::cout << loc.column() << std::endl;
  
  function2(loc);
    
  function2(source_location::current());
  return 0;
}
