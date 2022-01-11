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
  #if __cplusplus >= 201103L
    #include <cstdint>
  #endif

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
    #if (defined(__clang__) and __clang_major__ >= 9) || _MSC_VER > 1925
      static source_location current(const long long& line = __builtin_LINE(),const long long& column = __builtin_COLUMN(), const char* file_name = __builtin_FILE(), const char* function_name = __builtin_FUNCTION())
      {
        return source_location(line,column,file_name,function_name);
      }
    #elif defined(__GNUC__) and  __GNUC__ >= 5
      static source_location current(const long long& line = __builtin_LINE(),const long long& column = 0, const char* file_name = __builtin_FILE(), const char* function_name = __builtin_FUNCTION())
      {
        return source_location(line,column,file_name,function_name);
      }
    #else
      static source_location current(const long long& line,const long long& column,const char* file_name, const char* function_name)
      {
        return source_location(line,column,file_name,function_name);
      }
    #endif
    
    source_location() NO_EXCEPT : _line(0), _column(0), _file_name(""), _function_name("") {}

    source_location(const source_location& other): _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}

    #ifdef __cpp_rvalue_references
      source_location(source_location&& other) NO_EXCEPT : _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}
    #endif // __cpp_rvalue_references
    #if __cplusplus >= 201103L
      source_location(const std::uint_least32_t& line,const std::uint_least32_t& column, const char* file_name, const char* function_name): _line(line), _column(column), _file_name(file_name), _function_name(function_name){}
    #else
      source_location(const int& line,const int& column, const char* file_name, const char* function_name): _line(line), _column(column), _file_name(file_name), _function_name(function_name){}
    #endif

    ~source_location() {}
    #if __cplusplus >= 201103L
      inline CONSTEXPR std::uint_least32_t line() const NO_EXCEPT { return _line; }
      inline CONSTEXPR std::uint_least32_t column() const NO_EXCEPT { return _column; }
    #else
      inline CONSTEXPR int line() const NO_EXCEPT { return _line; }
      inline CONSTEXPR int column() const NO_EXCEPT { return _column; }
    #endif
    inline CONSTEXPR const char* file_name() const NO_EXCEPT { return _file_name; }
    inline CONSTEXPR const char* function_name() const NO_EXCEPT { return _function_name; }

    private:
      #if __cplusplus >= 201103L
        const std::uint_least32_t _line{0};
        const std::uint_least32_t _column{0};
      #else
        const int _line;
        const int _column;
      #endif
      const char* _file_name;
      const char* _function_name;
    };

    #undef CONSTEXPR
    #undef NO_EXCEPT

    #if defined(_MSC_VER) &&  _MSC_VER <= 1925
      #define current() current( __LINE__ , 0, __FILE__ , "Not available !" )
    #elif defined(__clang__) and __clang_major__ < 9
      #define current(args...) current( __LINE__ , 0, __FILE__ , __PRETTY_FUNCTION__ )
    #elif defined(__GNUC__) and __GNUC__ < 5 and !defined(__clang__)
      #define current(args...) current( __LINE__ , 0, __FILE__ , __PRETTY_FUNCTION__ )
   #endif
#endif

    
#endif //SOURCE_LOCATION_H_
