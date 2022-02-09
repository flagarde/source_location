#ifndef SOURCE_LOCATION_H_
#define SOURCE_LOCATION_H_

#if !defined(__has_include)
 #define __has_include(include) 0L
#endif

#if __cplusplus >= 202002L && __has_include(<source_location>)
  #include <source_location>
  using source_location = std::source_location;
#elif __cplusplus >= 201402L && __has_include(<experimental/source_location>)
  #include <experimental/source_location>
  using source_location = std::experimental::source_location;
#else
  #if __cplusplus >= 201103L || _MSVC_LANG >= 201103L
    #include <cstdint>
  #endif
  #if (__cplusplus >= 201103L && !defined(__clang__) && defined(__GNUC__) && __GNUC__>5) || (defined(_MSC_VER) && _MSC_VER >= 1900)
    #define NOEXCEPT noexcept
    #define CONSTEXPR constexpr
  #else
    #define NOEXCEPT noexcept
    #define CONSTEXPR constexpr
  #endif

  #if !defined(__has_builtin)
    #define __has_builtin(builtin) OL
  #endif

  class source_location
  {
  private:
    #if __cplusplus >= 201103L || _MSVC_LANG >= 201103L
      using intType = std::uint_least32_t;
    #else
      typedef int intType;
    #endif
    const intType m_line;
    const intType m_column;
    const char* m_file_name;
    const char* m_function_name;
    explicit CONSTEXPR source_location(const intType& line=0,const intType& column=0,const char* file_name="unsupported",const char* function_name="unsupported") NOEXCEPT : m_line(line), m_column(column), m_file_name(file_name), m_function_name(function_name) {}

  public:
    #if __has_builtin(__builtin_FUNCTION)
      #if __has_builtin(__builtin_COLUMN)
        static CONSTEXPR source_location current(const intType& line=__builtin_LINE(),const intType& column=__builtin_COLUMN(),const char* file_name=__builtin_FILE(),const char* function_name=__builtin_FUNCTION()) NOEXCEPT
      #else
        static CONSTEXPR source_location current(const intType& line=__builtin_LINE(),const intType& column=0,const char* file_name=__builtin_FILE(),const char* function_name=__builtin_FUNCTION()) NOEXCEPT
      #endif
    #else
      static CONSTEXPR source_location current(const intType& line=0,const intType& column=0,const char* file_name="unsupported",const char* function_name="unsupported") NOEXCEPT
    #endif
    {
      return source_location(line, column, file_name, function_name);
    }

    CONSTEXPR intType line() const NOEXCEPT
    {
      return m_line;
    }

    CONSTEXPR intType column() const NOEXCEPT
    {
      return m_column;
    }

    CONSTEXPR const char* file_name() const NOEXCEPT
    {
      return m_file_name;
    }

    CONSTEXPR const char* function_name() const NOEXCEPT
    {
      return m_function_name;
    }
  };

  #undef NOEXCEPT
  #undef CONSTEXPR

#endif

#endif //SOURCE_LOCATION_H_
