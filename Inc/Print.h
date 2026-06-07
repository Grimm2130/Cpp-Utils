#if !defined(__PRINT_H__)
#define __PRINT_H__

#include "CppTemplates/Templates.h"
#include <stdio.h>
#include <stdarg.h>

#define DEFAULT_BUFFER_SIZE 0x800

namespace Utils
{
    #define ANSI_COLOR_RED "\x1b[31m"
    #define ANSI_COLOR_GREEN "\x1b[32m"
    #define ANSI_COLOR_YELLOW "\x1b[33m"
    #define ANSI_COLOR_BLUE "\x1b[34m"
    #define ANSI_COLOR_MAGENTA "\x1b[35m"
    #define ANSI_COLOR_CYAN "\x1b[36m"
    #define ANSI_COLOR_RESET "\x1b[0m"
    
    class Print
    {
    private:

        enum class Type
        {
            Error,
            Warn,
            Info,
            Success
        };

    public:

        static void Info( const char * msg, ... )
        {
            va_list arg;
            va_start( arg, msg );
            _Print(Type::Info, msg, &arg );
            va_end( arg );
        }

        static void Warning( const char * msg, ... )
        {
            va_list arg;
            va_start( arg, msg );
            _Print(Type::Warn, msg, &arg );
            va_end( arg );
        }

        static void Error( const char * msg, ... )
        {
            va_list arg;
            va_start( arg, msg );
            _Print(Type::Error, msg, &arg );
            va_end( arg );
        }

        static void Success( const char * msg, ... )
        {
            va_list arg;
            va_start( arg, msg );
            _Print(Type::Success, msg, &arg );
            va_end( arg );
        }

    private:

        static inline void _Print( const Type format, const char * msg, va_list *argPtr )
        {
            char buffer[DEFAULT_BUFFER_SIZE];
            buffer[0] = '\0';

            int len = vsnprintf( buffer, DEFAULT_BUFFER_SIZE, msg, (*argPtr) );

            if( len > 0 )
            {
                switch (format)
                {
                case Type::Info:
                    printf( ANSI_COLOR_BLUE "%s%s\n", buffer, ANSI_COLOR_RESET );
                break;
                case Type::Warn:
                    printf( ANSI_COLOR_YELLOW "%s%s\n", buffer, ANSI_COLOR_RESET );
                break;
                case Type::Error:
                    printf( ANSI_COLOR_RED "%s%s\n", buffer, ANSI_COLOR_RESET );
                break;
                case Type::Success:
                    printf( ANSI_COLOR_GREEN "%s%s\n", buffer, ANSI_COLOR_RESET );
                break;
                    
                default:
                    printf( "%s\n", buffer );
                    break;
                }
            }
        }

    CLASS_IS_STATIC_ONLY(Print);
    };
    
} // namespace Utils


#endif // __PRINT_H__