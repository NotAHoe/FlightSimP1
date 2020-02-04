//
// Created by zohar on 19/12/2019.
//

#ifndef FLIGHTSIM_OPENDATASERVERCOMMAND_H
#define FLIGHTSIM_OPENDATASERVERCOMMAND_H

#include "Command.h"
#include <unordered_map>
#include <vector>

using namespace std;

class openDataServerCommand : public Command {
    double port;


public:



    openDataServerCommand() {}


    int execute(vector<string> lines, int index, bool isActive) override;

    ~openDataServerCommand() {}
    void serverThread(int client);
    vector<string> splitValues(string str);
};


#endif //FLIGHTSIM_OPENDATASERVERCOMMAND_H
