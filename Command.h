//
// Created by Zohar on 19/12/2019.
//

#ifndef FLIGHTSIM_COMMAND_H
#define FLIGHTSIM_COMMAND_H


#include <string>
#include <vector>
using namespace std;

/**
 * Command Interface
 */
class Command
{
public:
    // The function to execute the command
    virtual int execute(vector<string> lines, int index, bool isActive) = 0;

    // Destructor
    virtual ~Command(){}
};

#endif //FLIGHTSIM_COMMAND_H