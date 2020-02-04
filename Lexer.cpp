#include <regex>
#include <fstream>
#include "Lexer.h"

Lexer::Lexer(string name)
{
    this->fileName = name;
}


Lexer::~Lexer()
{
}

vector<string> Lexer::readFile()
{
    // Defining the input file stream
    std::ifstream inputStream(this->fileName);

    // Defining the string array to return now that we know how many lines there are
    vector<string> fileData;
    smatch matchArr;
    //command(,)
    regex command("^\\s*([^\\s]*)\\((?:(\"*[^,\"]*\"*)?\\,)*(\"*[^,\"]+\"*)?\\)\\s*(\\})?");
    //sim assignment
    regex sim("\\s*(var)\\s?([^\\s]*)\\s?(\\=|<-|->)\\s?sim\\(\"(.*)\"\\)\\s*(\\})?");
    //var assignment
    regex var("\\s*(?:(var)\\s)?([^\\s]*)\\s?(\\=)\\s?(.*)\\s*(\\})?");
    //while handling/if
    regex cond("^\\s*(while|if)\\s(?:([^\\{]+)\\s)+(\\{?)\\s*(\\})?");
    // } handling
    regex close("\\s*(\\})\\s*");

    // Read the file and store the lines in an array
    string currLine;
    while (getline(inputStream, currLine))
    {
        if (regex_search(currLine, matchArr, command) ||
            regex_search(currLine, matchArr, sim) ||
            regex_search(currLine, matchArr, cond) ||
            regex_search(currLine, matchArr, close))
            for (int i = 1; i < matchArr.size(); i++)
            {
                if (matchArr[i].matched)
                    fileData.insert(fileData.end(), matchArr[i]);
            }
        else if (regex_search(currLine, matchArr, var))
        {
            int checkVar = 1;
            for (int i = 1; i < matchArr.size(); i++)
            {
                if (matchArr[i].matched)
                {
                    if (matchArr[i] != "var" && checkVar)
                    {
                        fileData.insert(fileData.end(), "var");
                        checkVar = 0;
                    }
                    else if (matchArr[i] == "var")
                        checkVar = 0;
                    fileData.insert(fileData.end(), matchArr[i]);
                }
            }
        }
    }

    inputStream.close();

    return fileData;
}