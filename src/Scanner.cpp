#include "../include/Scanner.hpp"


const std::unordered_map<std::string , TokenType> KEYWORDS = {
    {"program" , PROGRAM},
    {"class" , CLASS},
    {"print" , PRINT},
    {"read" , READ},
    {"return" , RETURN},
    {"break" , BREAK},
    {"void" , VOID},
    {"final" , FINAL},
    {"new" , NEW},
    {"class" , IF},
    {"else" , ELSE},
    {"for" , FOR},
    {"while" , WHILE},
    {"int" , INT},
    {"char" , CHAR},
};


Scanner::Scanner(const char* file_path , const unsigned int buffer_size)
{
    filePath = file_path;
    source = NULL;

    start = 0;
    current = 0;
    line = 1;
}

Scanner::Scanner(const char* file_path)
{
    filePath = file_path;
    source = NULL;
    
    start = 0;
    current = 0;
    line = 1;
}

Scanner::~Scanner()
{
    if (source != NULL)
        free(source);

    int len = tokens.size();

    for (int i = 0 ; i < len ; i++)
    {
        if (tokens[i].idenValue != NULL)
            free((void*)tokens[i].idenValue);
    }

    tokens.clear();
}

void Scanner::openFileAll()
{
    FILE* file = fopen(filePath , "r");
    
    if (!file)
    {
        printf("[ERROR] Failed to read file\n");
        return;
    }

    fseek(file , 0 , SEEK_END);
    bufferSize = ftell(file);
    rewind(file);

    source = (char*)malloc(sizeof(char) * (bufferSize + 1));

    size_t got = fread(source , 1 , bufferSize , file);
    source[got] = '\0';

    fclose(file);
}


std::vector<Token>* Scanner::generateToken()
{
    openFileAll();

    if (source == NULL)
    {
        printf("[ERROR] Failed to retrieve the source file\n");
        return NULL;
    }

    while (!isAtEnd())
    {
        start = current;
        scanToken();
    }

    addToken(END_OF_FILE);

    return &tokens;
}

void Scanner::scanToken()
{
    char c = advance();

    switch (c)
    {
        case '(' : addToken(LEFT_PAREN); break;
        case ')' : addToken(RIGHT_PAREN); break;
        case '{' : addToken(LEFT_BRACE); break;
        case '}' : addToken(RIGHT_BRACE); break;
        case '[' : addToken(LEFT_BRACKET); break;
        case ']' : addToken(RIGHT_BRACKET); break;
        case ',' : addToken(COMMA); break;
        case '.' : addToken(DOT); break;
        case ';' : addToken(SEMICOLON); break;
        case '*' : addToken(STAR); break;
        case '%' : addToken(REM); break;
        case '-' : 
            if (peek() == '-')
            {
                addToken(MINUS_MINUS);
                advance();
            }
            else
            {
                addToken(MINUS);
            }
            break;

        case '+' : 
            if (peek() == '+')
            {
                addToken(PLUS_PLUS);
                advance();
            }
            else
            {
                addToken(PLUS);
            }
            break;

        case '!' :
            if (peek() == '=')
            {
                addToken(BANG_EQUAL);
                advance();
            }
            else
            {
                addToken(BANG);
            }
            break;

        case '=' :
            if (peek() == '=')
            {
                addToken(EQUAL_EQUAL);
                advance();
            }
            else
            {
                addToken(EQUAL);
            }
            break;

        case '<' :
            if (peek() == '=')
            {
                addToken(LESS_EQUAL);
                advance();
            }
            else
            {
                addToken(LESS);
            }
            break;

        case '>' :
            if (peek() == '=')
            {
                addToken(GREATER_EQUAL);
                advance();
            }
            else
            {
                addToken(GREATER);
            }
            break;

        case '|' :
            if (peek() == '|')
            {
                addToken(OR);
                advance();
            }
            else
            {
                break;
                // this must raise error
            }

        case '&' :
            if (peek() == '&')
            {
                addToken(AND);
                advance();
            }
            else
            {
                break;
                // this must raise error
            }

        case ' ' : break;
        case '\t' : break;
        case '\r' : break;

        case '\n' :
            line++;
            break;

        case '/' :
            if (peek() == '/')
            {
                advance();

                while (peek() != '\n' && !isAtEnd())
                    advance();
            }
            else if (peek() == '*')
            {
                advance();

                while (!isAtEnd())
                {
                    if (peek() == '*' && peek(1) == '/')
                    {
                        advance();
                        advance();
                        break;
                    }
                    
                    advance();
                }
            }
            else
            {
                addToken(SLASH);
            }

        default :
            if (isDigit(c))
            {
                _number();
            }
            else if (c == '\'')
            {
                _char();
            }
            else if (isAlpha(c))
            {
                identifier();
            }
            else
            {
                break;
            }

    }
}

char Scanner::peek(int n)
{
    return source[current + n];
}

char Scanner::advance()
{
    return source[current++];
}

bool Scanner::isAtEnd()
{
    return current >= bufferSize;
}

bool Scanner::isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool Scanner::isAlpha(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Scanner::isAlphaNumeric(char c)
{
    return isDigit(c) || isAlpha(c);
}

bool Scanner::isWhitespace(char c)
{
    return c == '\n' || c == ' ' || c == '\t' || c == '\r';
}

void Scanner::_number()
{
    bool has_left_side = false;
    bool is_float = false;
    bool has_right_side = false;

    char num[64];
    int idx = 0;

    num[idx++] = peek(-1);

    while (isDigit(peek()))
    {
        num[idx++] = peek();
        advance();
        has_left_side = true;
    }

    num[idx] = '\0';

    addToken(NUMBER , '\0' , std::atof(num));   
}

void Scanner::_char()
{
    char c;

    c = peek();

    advance();
    
    if (peek() != '\'')
        printf("The char is not valid\n");

    advance();

    addToken(STRING , c);
}

// void Scanner::_string()
// {
//     char c;

//     while (peek() != '\'')
//     {
//         str[idx++] = peek();
//         advance();
//     }

//     str[idx] = '\0';
//     advance();

//     addToken(STRING , c);
// }

void Scanner::identifier()
{
    char iden[64];
    int idx = 0;
    
    iden[idx++] = peek(-1);

    while (isAlphaNumeric(peek()))
    {
        iden[idx++] = peek();
        advance();
    }

    iden[idx] = '\0';


    auto it = KEYWORDS.find(std::string(iden));

    if (it != KEYWORDS.end())
    {
        addToken(it->second);
    }
    else
    {
        char* iden_alloc = (char*)malloc(idx + 1);
        memcpy(iden_alloc , (char*)iden , idx + 1);

        addToken(IDENTIFIER , '\0' , 0 , iden_alloc);
    }
}


void Scanner::addToken(TokenType token_type , char c , int val , const char* iden)
{
    tokens.push_back((Token){iden , val , line , token_type , c});
}