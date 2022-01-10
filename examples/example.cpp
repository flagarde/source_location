#include <iostream>
#include <source_location/source_location.hpp>

source_location src_clone(source_location a = source_location::current())
{
    return a;
}

int main()
{
   source_location loc(source_location::current());
   std::cout << loc.file_name() << std::endl;
   std::cout << loc.function_name() << std::endl;
   std::cout << loc.line() << std::endl;
   source_location s2 = src_clone();          // location should point here 
   std::cout<< s2.line() << ' ' << s2.function_name() << '\n';
}
