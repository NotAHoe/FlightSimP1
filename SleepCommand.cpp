//
// Created by zohar on 28/01/2020.
//

#include <thread>
#include "SleepCommand.h"

/***
 * Execute a standart sleep (included in POSIX)
 * @return the amount of parameters used in lines vector
 */
int SleepCommand::execute(vector<string> lines, int index, bool isActive) {
    if (isActive) {

        int time = stoi(lines[index + 1]);
        this_thread::sleep_for(chrono::milliseconds(time));
    }
    return 2;
}