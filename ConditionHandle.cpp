//
// Created by Tzach on 23/01/2020.
//

#include "ConditionHandle.h"
#include "ExpressionHandler.h"
/***
 * handles a condition of a While or if
 * @return if the condition is true currently
 */
bool ConditionHandle::isTrue()
{
    // Assuming the condition is false
    bool result = false;

    // According to the logical expression, return if the condition is true
    switch (logicEx)
    {
        // Lesser than
        case lt:
        {
            if (leftEx->calculate() < rightEx->calculate())
                result = true;
            break;
        }
            // Lesser equals
        case le:
        {
            if (leftEx->calculate() <= rightEx->calculate())
                result = true;
            break;
        }
            // Equals
        case eq:
        {
            if (leftEx->calculate() == rightEx->calculate())
                result = true;
            break;
        }
            // Greater equals
        case ge:
        {
            if (leftEx->calculate() >= rightEx->calculate())
                result = true;
            break;
        }
            // Greater than
        case gt:
        {
            if (leftEx->calculate() > rightEx->calculate())
                result = true;
            break;
        }
        default:
            break;
    }

    return result;
}

/***
 *
 * @param lines -fly.txt parsed and lexed
 * @param index - index of the vector
 * @param isActive - is the loop still active
 * @return
 */
int ConditionHandle::execute(vector<string> lines, int index, bool isActive)
{
    // In case we're in an inner condition, proceed to execute only if it's true
    if (isActive)
    {
        // Get the Singleton instance of the interpreter in order to analyze the condition parameters
        Interpreter *interpreter = interpreter->instance();

        // A string to represent the logical expression
        string logicExp = "=";

        // Define regex to capture the different parts of the condition and a captures array
        regex expression("(.*)\\b\\s*([=<>]+)\\s*(.*)");
        smatch matchArr;

        // A match counter in order to put the found values in the correct order
        int indicator = 0;

        // The expression to check
        strExpression = lines[index + 1];

        // Check if the regex found a match
        if (regex_search(strExpression, matchArr, expression))
        {
            // Iterate over the matches array
            for (int i = 1; i < matchArr.size(); i++)
            {
                // If we found 3 matches, we don't have to proceed
                if (indicator == 3)
                    break;
                if (matchArr[i].matched)
                {
                    switch (indicator)
                    {
                        // First match is left expression
                        case 0:
                            leftEx = interpreter->interpret(matchArr[i]);
                            indicator++;
                            break;
                            // Second match is logical expression
                        case 1:
                            logicExp = matchArr[i];
                            indicator++;
                            break;
                            // Third match is right expression
                        case 2:
                            rightEx = interpreter->interpret(matchArr[i]);
                            indicator++;
                            break;
                    }
                }
            }
        }

        // Change the logical expression if it was different than '='
        if (logicExp == "<")
            logicEx = lt;
        else if (logicExp == "<=")
            logicEx = le;
        else if (logicExp == ">=")
            logicEx = ge;
        else if (logicExp == ">")
            logicEx = gt;
    }

    // Move 2 cells in the strings vector
    return 2;
}

void ConditionHandle::update()
{
    // Get the Singleton instance of the interpreter in order to analyze the condition parameters
    Interpreter *interpreter = interpreter->instance();

    // Define regex to capture the different parts of the condition and a captures array
    regex expression("(.*)\\b\\s*([=<>]+)\\s*(.*)");
    smatch matchArr;

    // A match counter in order to put the found values in the correct order
    int indicator = 0;

    // Check if the regex found a match
    if (regex_search(strExpression, matchArr, expression))
    {
        // Iterate over the matches array
        for (int i = 1; i < matchArr.size(); i++)
        {
            if (matchArr[i].matched)
            {
                switch (indicator)
                {
                    // First match is left expression
                    case 0:
                        leftEx = interpreter->interpret(matchArr[i]);
                        indicator++;
                        break;
                        // Third match is right expression
                    case 2:
                        rightEx = interpreter->interpret(matchArr[i]);
                        indicator++;
                        break;
                }
            }
        }
    }
}