#ifndef TOKEN_HPP
#define TOKEN_HPP


// enum TokenType
// {
//     // Single-character tokens.
//     LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
//     COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
//     AND , OR ,

//     // One or two character tokens.
//     BANG, BANG_EQUAL,
//     EQUAL, EQUAL_EQUAL,
//     GREATER, GREATER_EQUAL,
//     LESS, LESS_EQUAL,

//     // Literals.
//     IDENTIFIER, STRING, NUMBER,

//     // Keywords.
//     CLASS, ELSE, FALSE, FUN, FOR, IF, NIL,
//     PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE
// };

#ifdef X
    #undef X
#endif

#define TOKEN_TYPE_LIST(X) \
    X(LEFT_PAREN)       \
    X(RIGHT_PAREN)      \
    X(LEFT_BRACE)       \
    X(RIGHT_BRACE)      \
    X(LEFT_BRACKET)     \
    X(RIGHT_BRACKET)    \
    X(COMMA)            \
    X(DOT)              \
    X(SEMICOLON)        \
                        \
    X(MINUS)            \
    X(MINUS_MINUS)      \
    X(PLUS)             \
    X(PLUS_PLUS)        \
    X(SLASH)            \
    X(STAR)             \
    X(REM)              \
                        \
    X(AND)              \
    X(OR)               \
    X(BANG)             \
    X(BANG_EQUAL)       \
    X(EQUAL)            \
    X(EQUAL_EQUAL)      \
    X(GREATER)          \
    X(GREATER_EQUAL)    \
    X(LESS)             \
    X(LESS_EQUAL)       \
                        \
    X(NUMBER)           \
    X(STRING)           \
    X(IDENTIFIER)       \
                        \
    X(PROGRAM)          \
    X(CLASS)            \
    X(PRINT)            \
    X(READ)             \
    X(RETURN)           \
    X(BREAK)            \
    X(VOID)             \
    X(FINAL)            \
    X(NEW)              \
    X(IF)               \
    X(ELSE)             \
    X(FOR)              \
    X(WHILE)            \
    X(INT)              \
    X(CHAR)             \
    


typedef enum
{
    #define X(n) n,
        TOKEN_TYPE_LIST(X)
    #undef X

    END_OF_FILE
} TokenType;

inline const char* tokenTypeToStr(TokenType token_type)
{

    static const char* token_type_string[] = {
        #define X(n) #n ,
            TOKEN_TYPE_LIST(X)
        #undef X
        
        "END_OF_FILE"
    };


    return token_type_string[(int)token_type];
}


typedef struct Token 
{
    const char* idenValue;
    int numValue;
    int line;
    TokenType tokenType;
    char charValue;
} Token;


#endif