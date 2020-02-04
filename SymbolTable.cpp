//
// Created by Tzach on 18/01/2020.
//

#include "SymbolTable.h"

/***
 * Creates a Variable and inserts it to the SymbolTable
* @param dir - direction of influence - to sim, from sim, and equal
 * @param scp - scope of the var
 * @param val - value
 * @param name - name of variable
 * @param sim - sim address
 */
void SymbolTable::createVar(direction dir, int scope, double val, string name, string sim) {
    // Insert the new var to the map
    symbolTableMap.insert(pair<string, Var>(name, Var(dir, scope, val, name, sim)));

    // Chain a string called data, which will be formatted: 'name' + '=' + 'val'
    string data = name + "=" + to_string(val);

    // Use the string to create the new var in the interpreter map
    interpreter->setVariables(data);
}

/***
 * Method which updates a given Var's value
 * @param name
 * @param val
 */
void SymbolTable::updateVar(string name, double val) {
    // Update the new var value in the map
    symbolTableMap.at(name).setValue(val);

    // Chain a string called data, which will be formatted: 'name' + '=' + 'val'
    string data = name + "=" + to_string(val);

    // Use the string to update the var in the interpreter map
    interpreter->setVariables(data);
}

SymbolTable *SymbolTable::singleton = 0;

/***
 * Our table is a singleton, thus we will use the same instance of the table throughout our program
 * That way we won't have to create and edit multiple tables in each class
 * @return the instance of the table
 */
SymbolTable *SymbolTable::instance() {
    if (singleton == 0)
        singleton = new SymbolTable();
    return singleton;
}



void SymbolTable::removeWithScope(int scope) {
    for (auto it = symbolTableMap.begin(); it != symbolTableMap.end(); ++it) {
        if (it->second.getScope() == scope)
            symbolTableMap.erase(it);
    }
}