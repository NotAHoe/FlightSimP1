//
// Created by Tzach on 18/01/2020.
//

#include "Var.h"

/***
 * Var constructor from a given var
 * @param a given Variable
 */
Var::Var(Var const &newVar) {
    this->varName = newVar.varName;
    this->direction = newVar.direction;
    this->scope = newVar.scope;
    this->simPath = newVar.simPath;
    this->value = newVar.value;
}
/***
 *Var constructor from given fields
 * @param dir - direction of influence - to sim, from sim, and equal
 * @param scp - scope of the var
 * @param val - value
 * @param name - name of variable
 * @param sim - sim address
 */
Var::Var(enum direction dir, int scp, double val, string name, string sim) {
    this->varName = name;
    this->direction = dir;
    this->scope = scp;
    this->simPath = sim;
    this->value = val;
}
//setting the value of a given variable
void Var::setValue(double val) {
    this->value = val;
}
//sim adress getter
string Var::getSim() {
    return this->simPath;
}
//sim value getter
double Var::getValue() {
    return this->value;
}
//sim direction getter
enum direction Var::getDir() {
    return this->direction;
}