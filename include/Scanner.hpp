#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include "./Token.hpp"

#define MAX_BUFFER_SIZE 4096

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)


extern const std::unordered_map<std::string , TokenType> KEYWORDS;

class Scanner
{
    private :
        const char* filePath;
        unsigned int bufferSize;
        char* source;
        std::vector<Token> tokens;

        int start;
        int current;
        int line;

        void openFileAll();
        void openFileBuffer();
        void scanToken();

        char peek(int n = 0);

        char advance();
        bool isAtEnd();

        bool isDigit(char c);
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);
        bool isWhitespace(char c);

        void number();
        void string();

        void identifier();

        void report();

        void addToken(TokenType token_type , const char* str_val = NULL , double val = 0.0);

    public :
        Scanner(const char* file_path , const unsigned int buffer_size);
        Scanner(const char* file_path);
        
        std::vector<Token>* generateToken();

        ~Scanner();
};

#endif