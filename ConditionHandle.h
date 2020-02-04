//
// Created by Tzach on 23/01/2020.
//

#ifndef FLIGHTSIMULATOR_CONDITIONHANDLE_H
#define FLIGHTSIMULATOR_CONDITIONHANDLE_H


#include "Command.h"
#include "Expression.h"

// Using enum to represent the logical expression, since working with integers is more efficient than strings
enum logicalEx {lt = -2, le = -1, eq = 0, ge = 1, gt = 2};

/**
 * ConditionHandle class
 */
class ConditionHandle : public Command
{
private:
    // Represents the left expression in the condition
    Expression *leftEx = 0;

    // Represents the right expression in the condition
    Expression *rightEx = 0;

    // Represents the logical "middle" expression in the condition
    logicalEx logicEx = eq;

    // A string representation of the condition
    string strExpression;

public:
    //Constructor
    ConditionHandle(){}

    // Destructor
    ~ConditionHandle(){}

    // Returns if the condition is true
    bool isTrue();

    // Updates the values of the variables in the condition on case we're in a loop
    void update();

    // Analyze the condition and decides how to proceed
    virtual int execute(vector<string> lines, int index, bool isActive);
};

#endif //FLIGHTSIMULATOR_CONDITIONHANDLE_H