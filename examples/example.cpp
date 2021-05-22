#include <iostream>
#include <source_location/source_location.hpp>

int main()
{
   source_location loc(source_location::current());
   std::cout << loc.file_name() << std::endl;
   std::cout << loc.function_name() << std::endl;
   std::cout << loc.line() << std::endl;
}
