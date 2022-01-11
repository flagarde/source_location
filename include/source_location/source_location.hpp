#ifndef SOURCE_LOCATION_H_
#define SOURCE_LOCATION_H_

#if !defined(__has_include)
 #define __has_include(include) 0
#endif

#if (__cplusplus >= 202002L && __has_include(<source_location>) && !defined(__clang__)) || (_MSVC_LANG > 202002L) || (_MSC_VER > 1928 && _MSVC_LANG > 201703L)
  #include <source_location>
  using source_location = std::source_location;
#elif __has_include(<experimental/source_location>) && !defined(__clang__) && __cplusplus >= 201402L
  #include <experimental/source_location>
  using source_location = std::experimental::source_location;
#else
  #if (__cplusplus >= 201103L && !defined(__clang__) && defined(__GNUC__) && __GNUC__>5) || (defined(_MSC_VER) && _MSC_VER >= 1900)
    #define NO_EXCEPT noexcept
    #define CONSTEXPR constexpr
  #else
    #define NO_EXCEPT
    #define CONSTEXPR
  #endif

  class source_location
  {
  public:
    #if (defined(__clang__) && __clang_major__ >= 9) || _MSC_VER > 1925
      static source_location current(const long int& line = __builtin_LINE(),const long int& column = __builtin_COLUMN(), const char* file_name = __builtin_FILE(), const char* function_name = __builtin_FUNCTION())
      {
        return source_location(line,column,file_name,function_name);
      }
    #elif defined(__GNUC__) &&  __GNUC__ >= 5
      static source_location current(const long int& line = __builtin_LINE(),const long int& column = 0, const char* file_name = __builtin_FILE(), const char* function_name = __builtin_FUNCTION())
      {
        return source_location(line,column,file_name,function_name);
      }
    #else
      static source_location current(const long int& line = 0,const long int& column = 0 ,const char* file_name = "Not available !" ,const char* function_name = "Not available !")
      {
        return source_location(line,column,file_name,function_name);
      }
    #endif
    
    source_location() NO_EXCEPT : _line(0), _column(0), _file_name(""), _function_name("") {}

    source_location(const source_location& other): _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}

    #ifdef __cpp_rvalue_references
      source_location(source_location&& other) NO_EXCEPT : _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}
    #endif // __cpp_rvalue_references
    source_location(const long int& line,const long int& column, const char* file_name, const char* function_name): _line(line), _column(column), _file_name(file_name), _function_name(function_name){}

    ~source_location() {}
    #if defined(__GNUC__)
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wpedantic"
    #endif
      inline CONSTEXPR long int line() const NO_EXCEPT { return _line; }
      inline CONSTEXPR long int column() const NO_EXCEPT { return _column; }
      inline CONSTEXPR const char* file_name() const NO_EXCEPT { return _file_name; }
      inline CONSTEXPR const char* function_name() const NO_EXCEPT { return _function_name; }
    #if defined(__GNUC__)
      #pragma GCC diagnostic pop
    #endif
    private:
      const int _line;
      const int _column;
      const char* _file_name;
      const char* _function_name;
    };

    #undef CONSTEXPR
    #undef NO_EXCEPT

    #if defined(_MSC_VER) &&  _MSC_VER <= 1925
      #define current() current( __LINE__ , 0, __FILE__ , "Not available !" )
    #elif defined(__clang__) && __clang_major__ < 9
      #define current(args...) current( __LINE__ , 0, __FILE__ , __PRETTY_FUNCTION__ )
    #elif defined(__GNUC__) && __GNUC__ < 5 && !defined(__clang__)
      #define current(args...) current( __LINE__ , 0, __FILE__ , __PRETTY_FUNCTION__ )
   #endif
#endif

    
#endif //SOURCE_LOCATION_H_
