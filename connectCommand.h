//
// Created by zohar on 22/01/2020.
//

#ifndef FLIGHTSIM_CONNECTCOMMAND_H
#define FLIGHTSIM_CONNECTCOMMAND_H


#include "Command.h"

class connectCommand: public Command {

    double port;
    string hostIP;

public:
    connectCommand(){}

    int execute(vector<string> vector, int index, bool isActive) override;
    void clientConncetion(int connection);

    ~connectCommand() override{}
};


#endif //FLIGHTSIM_CONNECTCOMMAND_H
