//
// Created by zohar on 28/01/2020.
//

#ifndef FLIGHTSIM_PRINTCOMMAND_H
#define FLIGHTSIM_PRINTCOMMAND_H


#include "Command.h"
#include <iostream>

/**
 * PrintCommand class
 */
class PrintCommand: public Command {


public:
    PrintCommand(){};

    int execute(vector<string> vector, int index, bool isActive) override;
    ~PrintCommand(){};
};


#endif //FLIGHTSIM_PRINTCOMMAND_H