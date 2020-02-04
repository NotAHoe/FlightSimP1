//
// Created by Zohar on 28/01/2020.
//
#include "PrintCommand.h"
#include "ExpressionHandler.h"
/***
 * Print Command either prints a string or a given variable
 * @return the amount of parameters used in lines vector
 */
int PrintCommand::execute(vector<string> lines, int index, bool isActive) {
    //operates if active (e.g in a loop)
    if (isActive) {
        string data = lines[index + 1];
        //if it's a string, prints the string
        if (data[0] == '"') {
            data.erase(data.begin());
            data.erase(data.end() - 1);
            cout << data;
        } else {
            //if it's a variable, prints it's value based on the Interpreter
            Interpreter *interpreter = interpreter->instance();
            Expression *e = interpreter->interpret(data);
            cout << e->calculate();
        }
        cout << "\n";
    }
    return 2;
}
