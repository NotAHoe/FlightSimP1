//
// Created by Tzach on 28/01/2020.
//

#include "Parser.h"


Parser::Parser()
{
    // Defining the keywords and their command counterparts
    this->funcMap["openDataServer"] = new openDataServerCommand();
    this->funcMap["var"] = new DefineVarCommand();
    this->funcMap["while"] = new ConditionHandle();
    this->funcMap["if"] = new ConditionHandle();
    this->funcMap["connectControlClient"] = new connectCommand();
    this->funcMap["Print"]= new PrintCommand();
    this->funcMap["Sleep"] = new SleepCommand();
}

void Parser::Parse(vector<string> lines)
{
    // Current function index
    int index = 0;
    int scope = 0;
    string lastString = "";
    // The map will store data like this: key - the scope, value - a pair: (location/index of the first command after the loop, the command itself)
    // Map for while-s
    unordered_map<int, pair<int, ConditionHandle*>> loopMap;
    // Map for if-s
    unordered_map<int, pair<int, ConditionHandle*>> condMap;

    while (index < lines.size())
    {
        lastString = lines[index];
        if (lines[index] == "{")
        {
            scope++;
            index++;
        }
        else if (lines[index] == "}")
        {
            index++;
            // Checking if } is the end of if
            // In case the last condition was if or the loop has reached the final lap
            if (condMap.find(scope) != condMap.end())
            {
                SymbolTable* st = st->instance();
                st->removeWithScope(scope);
                condMap.erase(scope);
                scope--;
            }
            else
            {
                (loopMap[scope].second)->update();
                if ((loopMap[scope].second)->isTrue())
                    index = loopMap[scope].first;
                else
                {
                    SymbolTable *st = st->instance();
                    st->removeWithScope(scope);
                    loopMap.erase(scope);
                    scope--;
                }
            }
        }
        else
        {
            Command* c = funcMap.at(lines[index]);

            if (c != nullptr)
            {
                // If the current scope we are in is true (Or is the general scope)
                if ((condMap.find(scope) != condMap.end() && (condMap[scope].second)->isTrue()) ||
                    (loopMap.find(scope) != loopMap.end() && (loopMap[scope].second)->isTrue()) || scope == 0)
                {
                    // If the word is var, it means we're going to create/update a variable, so we set it's scope first
                    if (lines[index] == "var")
                        ((DefineVarCommand*)c)->setScope(scope);

                    // Move forward in cells while executing the current command
                    index += c->execute(lines, index, true);

                    // If we've encountered a loop, define a proper cell in the relevant map
                    if (lastString == "while")
                        loopMap[scope + 1] = {index + 1, (ConditionHandle *) c};
                    if (lastString == "if")
                        condMap[scope + 1] = {index + 1, (ConditionHandle *) c};
                }
                else
                    // If the current scope we're in is a false condition, just move without executing
                    index += c->execute(lines, index, false);
            }
        }
    }
}