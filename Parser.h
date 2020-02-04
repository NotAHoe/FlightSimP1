#include "Command.h"
#include "unordered_map"
#include "openDataServerCommand.h"
#include "DefineVarCommand.h"
#include "ConditionHandle.h"
#include "connectCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#pragma once

/**
 * Parser class
 */
class Parser
{
private:
    // A map to match between a keyword and the command type that it represents
    unordered_map <string , Command*> funcMap;
public:
    // Constructor
    Parser();

    // Destructor
    ~Parser(){}

    // Interpret the lines and execute the code written in them
    void Parse(vector<string> lines);
};