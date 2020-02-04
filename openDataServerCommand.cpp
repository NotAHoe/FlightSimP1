//
// Created by zohar on 19/12/2019.
//
#include "openDataServerCommand.h"
#include "SymbolTable.h"
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include "string"
#include <strings.h>

/***
 *
 * @param lines - holds the information, parsed and lexed, from fly.txt file
 * @param index - where we at in the vector
 * @param isActive - loop boolean, is not relevant for this class
 * @return how many parameters we used
 */

int openDataServerCommand::execute(vector<string> lines, int index, bool isActive) {
    //port could be either a string or an expression, in both cases we can interpret it
    Interpreter *portConfig = portConfig->instance();
    Expression *portVal = portConfig->interpret(lines[index + 1]);
    this->port = portVal->calculate();

//Opening the server
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        cout << "socket error";
    }

    sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = INADDR_ANY;
    adress.sin_port = htons(port);
    int binding = bind(socketfd, (struct sockaddr *) &adress, sizeof(adress));

    if (binding == -1) {
        //could not bind socket to IP
        cout << "bind error";

        return -2;
    }

    if (listen(socketfd, 5) == -1) {
        cout << "listen error";
        return -3;
    }

    int client = accept(socketfd, (struct sockaddr *) &adress, (socklen_t *) &adress);
    if (client == -1) {
        cout << "accpet error";

        return -4;
    }

    //open the server thread using the serverThread method
    thread readFromServer(&openDataServerCommand::serverThread, this, client);
    readFromServer.detach();
    //this command uses it's call and the first parameter, thus returning 2
    return 2;

}


/***
 * this method splits the values from the simulator using a comma delimiter
 * @param buffer string to be split
 * @return the parsed values
 */
vector<string> openDataServerCommand::splitValues(string buffer) {
    vector<string> splitVec;
    string token;
    string curr;
    for (int i = 0; i < buffer.size(); ++i) {
        curr = buffer[i];
        if (curr == ",") {
            if (!token.empty()) {
                splitVec.push_back(token);
            }
            token = "";
            continue;
        }
        token += buffer[i];
    }
    if (!token.empty()) {
        splitVec.push_back(token);
    }
    return splitVec;
}

/***
 * updates the values from the simulator
 * @param vals - array of values
 */


/***
 * this method opens the server and iterates upon it
 * in addition, this method directs the data to its' place
 * either updating or parsing the data
 * @param client - client port we generated at the execute command
 */
void openDataServerCommand::serverThread(int client) {
    //accept using a buffer
    char buffer[1024];
    bzero(buffer, 1024);
    string data;
    string curr;
    vector<string> values;
    double vals[36];
    //we get values from the server endlessly, updating each new information
    while (true) {
        //read data coming from the client
        int valread = read(client, buffer, 1024);
        data.append(buffer, valread);
        //looking for \n in the text
        while (!data.find('\n')) {
            int valread = read(client, buffer, 1024);
            data.append(buffer, valread);
            //after geeting all the values, we send the to be split\parse


        }
        //we send curr to be split, getting the values without a \n
        curr = data.substr(0, data.find('\n'));
        //data is being converted to the next line
        data = data.substr(data.find_first_of('\n')+1, data.size() -1);
        //splitting the string to values
        values = splitValues(curr);
        //assigns all the values to the val array
        for (int i = 0; i < values.size(); ++i) {
            vals[i] = stod(values[i]);
        }

        //locks the thread due to data usage
        mutex datalock;
        datalock.lock();
        //creates a table instance
        SymbolTable *table = table->instance();
        //updates all the relevant values
        table->updateVar("airspeed", vals[0]);
        table->updateVar("warp", vals[1]);
        table->updateVar("magnetos", vals[2]);
        table->updateVar("heading", vals[3]);
        table->updateVar("alt", vals[4]);
        table->updateVar("roll", vals[7]);
        table->updateVar("pitch", vals[8]);
        table->updateVar("aileron", vals[20]);
        table->updateVar("elevator", vals[21]);
        table->updateVar("rudder", vals[22]);
        table->updateVar("throttle", vals[25]);
        table->updateVar("masteravionics", vals[26]);
        table->updateVar("starter", vals[27]);
        table->updateVar("autostart", vals[28]);
        table->updateVar("breaks", vals[29]);
        table->updateVar("brakeparking", vals[30]);
        table->updateVar("primer", vals[31]);
        table->updateVar("mixture", vals[32]);
        table->updateVar("masterbat", vals[33]);
        table->updateVar("masterlat", vals[34]);
        table->updateVar("rpm", vals[35]);
        datalock.unlock();

    }



}
