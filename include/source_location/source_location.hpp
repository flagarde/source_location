#pragma once

#if __cplusplus >= 202002L and __has_include(<source_location>) and !defined(__clang__)
  #include <source_location>
  using source_location = std::source_location;
#elif __has_include(<experimental/source_location>)
  #include <experimental/source_location>
  using source_location = std::experimental::source_location;
#else
  #include <cstdint>
  
  #if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    #define NO_EXCEPT noexcept
    #define CONSTEXPR constexpr
  #else
    #define NO_EXCEPT
    #define CONSTEXPR
  #endif

  class source_location
  {
  public:
    static source_location current(const std::uint_least32_t& line,const std::uint_least32_t& column, const char* file_name, const char* function_name)
    {
      return source_location(line,column,file_name,function_name);
    }
    
    source_location() NO_EXCEPT : _line(0), _column(0), _file_name(""), _function_name("") {}

    source_location(const source_location& other): _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}

    #ifdef __cpp_rvalue_references
      source_location(source_location&& other) NO_EXCEPT : _line(other.line()), _column(other.column()), _file_name(other.file_name()), _function_name(other.function_name()){}
    #endif // __cpp_rvalue_references

    source_location(const std::uint_least32_t& line,const std::uint_least32_t& column, const char* file_name, const char* function_name): _line(line), _column(column), _file_name(file_name), _function_name(function_name){}

    ~source_location() {}

    inline CONSTEXPR uint_least32_t line() const NO_EXCEPT { return _line; }

    inline CONSTEXPR uint_least32_t column() const NO_EXCEPT { return _column; }

    inline CONSTEXPR const char* file_name() const NO_EXCEPT { return _file_name; }

    inline CONSTEXPR const char* function_name() const NO_EXCEPT { return _function_name; }

    private:
      const std::uint_least32_t _line;
      const std::uint_least32_t _column;
      const char* _file_name;
      const char* _function_name;
    };
    
    #undef CONSTEXPR
    #undef NO_EXCEPT
  
    #if defined(_MSC_VER)
      #define current() current( __LINE__ , 0, __FILE__ , __func__ )
    #else
      #define current(args...) current( __LINE__ , 0, __FILE__ , __PRETTY_FUNCTION__ )
    #endif
#endif
