//
// Created by Tzach on 18/01/2020.
//

#ifndef FLIGHTSIMULATOR_SYMBOLTABLE_H
#define FLIGHTSIMULATOR_SYMBOLTABLE_H

#include <stdio.h>
#include "Var.h"
#include "unordered_map"
#include "ExpressionHandler.h"

/**
 * SymbolTable class
 */
class SymbolTable {
private:
    // The map containing every variable in the given code
    unordered_map<string, Var> symbolTableMap;

    // Singleton instance of this class
    static SymbolTable *singleton;

    // Interpeter to work with in order to have a synchronized variables value while interpreting expressions
    Interpreter* interpreter;

    // Constructor
    SymbolTable(){ interpreter = interpreter->instance(); }
public:
    // Public Singleton constructor
    static SymbolTable *instance();

    // The map getter
    unordered_map<string, Var> getMap() { return symbolTableMap; }

    // Destructor
    ~SymbolTable() { delete (singleton); }

    // The interpreter getter
    Interpreter* getInterpreter() { return interpreter->instance(); }

    // Create a new var
    void createVar(direction dir, int scope, double val, string name, string sim);

    // Update the value of an existing var
    void updateVar(string name, double val);

    // Delete all vars created within an inner scope
    void removeWithScope(int scope);
};


#endif //FLIGHTSIMULATOR_SYMBOLTABLE_H