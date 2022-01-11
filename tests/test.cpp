#include <iostream>
#include <doctest/doctest.h>
#include "source_location/source_location.hpp"

source_location src_clone(source_location a = source_location::current())
{
    return a;
}

TEST_CASE("Test source_location")
{
   source_location loc(source_location::current());
   std::cout<<"Line : "<< loc.line() <<" Column : "<< loc.column() << " File : "<<loc.file_name()<<" Function : "<<loc.function_name()<<std::endl;
   CHECK(loc.line()==12);
   source_location s2 = src_clone();          // location should point here
   CHECK(s2.line()==15);
   std::cout<<"Line : "<<  s2.line() <<" Column : "<<  s2.column() << " File : "<< s2.file_name()<<" Function : "<< s2.function_name()<<std::endl;
}
