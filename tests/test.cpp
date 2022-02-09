#include <iostream>
#include <string>

#include <doctest/doctest.h>
#include "source_location/source_location.hpp"

source_location src_clone(source_location a = source_location::current())
{
    return a;
}

std::string name="Test source_location with standard  : "+static_cast<std::string>(STANDARD);

source_location function()
{
  source_location loc(source_location::current());
  return loc;
}

TEST_CASE(name.c_str())
{
   source_location loc(source_location::current());
   std::cout<<"Line : "<< loc.line() <<" Column : "<< loc.column() << " File : "<<loc.file_name()<<" Function : "<<loc.function_name()<<std::endl;
   source_location s2 = src_clone();          // location should point here
   std::cout<<"Line : "<<  s2.line() <<" Column : "<<  s2.column() << " File : "<< s2.file_name()<<" Function : "<< s2.function_name()<<std::endl;
   source_location from_function = function();
   std::cout<<"Line : "<<  from_function.line() <<" Column : "<<  from_function.column() << " File : "<< from_function.file_name()<<" Function : "<< from_function.function_name()<<std::endl;
   if(loc.function_name() != "unsupported !")
   {
     CHECK(loc.line()==22);
     CHECK(s2.line()==24);
     CHECK(from_function.line()==16);
   }
   else
   {
     CHECK(loc.line()==0);
     CHECK(s2.line()==0);
     CHECK(from_function.line()==0);
   }
}
