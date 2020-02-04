#include "Command.h"

#pragma once
class Lexer
{
private:
    string fileName;
public:
    Lexer(string name);
    ~Lexer();
    vector<string> readFile();
};
