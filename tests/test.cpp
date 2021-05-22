#include <iostream>
#include <source_location/source_location.hpp>




source_location function()
{
  
  
  
  
  
  return source_location(source_location::current());
}


void toto(source_location loc)
{
  std::cout << loc.file_name() << std::endl;
    std::cout << loc.function_name() << std::endl;
    std::cout << loc.line() << std::endl;
}



int main()
{
    source_location loc = function();
    std::cout << loc.file_name() << std::endl;
    std::cout << loc.function_name() << std::endl;
    std::cout << loc.line() << std::endl;
    
    
    
    
    toto(loc);
    
    
    
    toto(source_location::current());
    
    
    
    return 0;
}
