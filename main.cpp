//Created by Tzach Cohen and Zohar Rafter
//Git : https://github.com/NotAHoe/FlightSimP1
#include <stdio.h>
#include "Lexer.h"
#include "openDataServerCommand.h"
#include "connectCommand.h"
#include "Parser.h"

using namespace std;

int main()
{
    //read the fly.txt file
    Lexer lex = Lexer("fly.txt");
    vector<string> data = lex.readFile();
    Parser parser = Parser();
    parser.Parse(data);
}

