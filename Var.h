//
// Created by Tzach on 18/01/2020.
//

#ifndef FLIGHTSIMULATOR_VAR_H
#define FLIGHTSIMULATOR_VAR_H

#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

// Using enum to represent the directions, since working with integers is more efficient than strings
enum direction {dirLeft = -1, dirEqual = 0, dirRight = 1};
class Var
{
private:
    // The data transfer direction of the var
    enum direction direction;

    // The var's scope
    int scope;

    // The var's value
    double value;

    // The var's name
    string varName;

    // The var's sim path
    string simPath;
public:
    // Value setter
    void setValue(double val);

    // Scope getter
    int getScope() { return scope; }

    // Constructor (gets var argument)
    Var(Var const &newVar);

    // Constructor (gets multiple fields arguments)
    Var(enum direction dir, int scope, double val, string name, string sim);

    // Sim path string getter
    string getSim();

    // Var value getter
    double getValue();

    // Direction getter
    enum direction getDir();

    // Destructor
    ~Var(){}
};


#endif //FLIGHTSIMULATOR_VAR_H