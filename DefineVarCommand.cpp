//
// Created by Tzach on 07/01/2020.
//

#include "DefineVarCommand.h"
/***
 * assigns values to a variable
 * @param lines - fly.txt parsed and lexed
 * @param index - index of vector
 * @return amount of parameters used in lines
 */
int DefineVarCommand::execute(vector<string> lines, int index, bool isActive)
{
    // In case we're in an inner condition, proceed to execute only if it's true
    if(isActive)
    {
        // Separating the data into strings
        string varName = lines[index + 1];
        string varDir = lines[index + 2];
        string strValue = lines[index + 3];
        direction dir = dirEqual;

        // If variable is found, no need to create new var, just update the value (Since after creation it can only receive expression values)
        if (symbolTable->getMap().find(varName) != symbolTable->getMap().end())
        {
            Expression *e = symbolTable->getInterpreter()->interpret(strValue);
            symbolTable->updateVar(varName, e->calculate());
        }
            // If variable isn't found, create it
        else
        {
            // If the value isn't an expression, but a sim path
            if (strValue[0] == '/') {
                // Default direction is =, check if it's -> or <-
                if (varDir.compare("<-"))
                    dir = dirLeft;
                else if (varDir.compare("->"))
                    dir = dirRight;
                symbolTable->createVar(dir, varScope, 0, varName, strValue);
            }
                // If the value is an expression
            else
            {
                Expression *e = symbolTable->getInterpreter()->interpret(strValue);
                symbolTable->createVar(dir, varScope, e->calculate(), varName, "");
            }
        }
    }

    // Move 4 cells in the strings vector
    return 4;
}

