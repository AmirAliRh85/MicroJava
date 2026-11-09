#include "./MicroJava.hpp"
#include <stdio.h>

void interpretFile(const char* file_path)
{
    Scanner scanner(file_path);
    std::vector<Token>* tokens = scanner.generateToken();

    for (Token t : *tokens)
    {
        printf("%i | %.1f , %s , %s\n" , t.line , t.numValue , t.strValue , tokenTypeToStr(t.tokenType));
    }
}

int main(int argc , char* argv[])
{
    if (argc == 1)
    {
        printf("Usage: yapl [filename.mj]");
    }
    else if (argc == 2)
    {
        interpretFile(argv[argc - 1]);
    }
    else
    {
        printf("yapl compiler does not support flags");
    }

    return 0;
}