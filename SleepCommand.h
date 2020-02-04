//
// Created by zohar on 28/01/2020.
//

#ifndef FLIGHTSIM_SLEEPCOMMAND_H
#define FLIGHTSIM_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand: public Command {

public:
    SleepCommand(){}

    int execute(vector<string> vector, int index, bool isActive) override;
    ~SleepCommand(){}
};


#endif //FLIGHTSIM_SLEEPCOMMAND_H
