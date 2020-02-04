//
// Created by Tzach on 07/01/2020.
//

#ifndef FLIGHTSIMULATOR_DEFINEVARCOMMAND_H
#define FLIGHTSIMULATOR_DEFINEVARCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

/**
 * DefineVarCommand Class
 */
class DefineVarCommand : public Command
{
private:
    // Holds the Singleton instance of the symbol table
    SymbolTable* symbolTable;

    // Represents the scope of the variable we create\update
    int varScope = 0;
public:
    // Checks if the given var needs to be created or rather updated
    virtual int execute(vector<string> lines, int index, bool isActive);

    // Sets the var scope
    void setScope(int scp) { this->varScope = scp; }

    // Constructor
    DefineVarCommand(){ symbolTable = symbolTable->instance(); }

    // Destructor
    ~DefineVarCommand(){}
};


#endif //FLIGHTSIMULATOR_DEFINEVARCOMMAND_H