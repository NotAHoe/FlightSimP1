//
// Created by zohar on 22/01/2020.
//

#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include "connectCommand.h"
#include "Var.h"
#include "SymbolTable.h"
#include <arpa/inet.h>
#include <thread>
#include <mutex>


/***
 * this method creates a client and update the sever
 * @param lines - vector of the fly.txt file, parsed
 * @param index - index of location in the string vector
 * @param isActive
 * @return - how many parameters did we use
 */
int connectCommand::execute(vector<string> lines, int index, bool isActive) {


    if (isActive) {
        //port can be an expression or a number, we interpret it anyway
        Interpreter *portConfig = portConfig->instance();
        string toPort = lines[index + 2];
        Expression *portExpression = portConfig->interpret(toPort);
        this->port = portExpression->calculate();

        //creating a client and connecting to localhost
        int connectSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (connectSocket == -1) {
            //error
            return -3;
        }
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(port);

        int is_connect = connect(connectSocket, (struct sockaddr *) &address, sizeof(address));
        cout << "Connected" << endl;
        if (is_connect == -1) {
            //error
            return -2;
        }
        //creates a thread of the client connection
        thread client(&connectCommand::clientConncetion, this, is_connect);
        client.detach();

    }
    return 3;
}

/***
 * in this method, we update the server with each new value
 * the values that are being sent uses the dependency method of fly.txt
 * @param connection - client connection
 */
void connectCommand::clientConncetion(int connection) {

    int is_sent = 0;
    mutex mute;
    //creates a SymbolTable instance, containing all the variables
    SymbolTable *senders = senders->instance();
    string prompt;
    //Getting the map of variables
    unordered_map<string, Var> value = senders->getMap();
    Interpreter *inter = senders->getInterpreter();
    auto iter = value.begin();
    while (true) {
//iterates along the map, and update every value that should come from client
        mute.lock();
        while (iter != value.end()) {

            if (iter->second.getDir() == dirRight) {

                prompt = "set " + iter->second.getSim() + " " + to_string(iter->second.getValue());
                cout<<prompt;
                cout<<"\n";
                is_sent = send(connection, prompt.c_str(), prompt.size(), 0);
                if (is_sent == -1) {
                    cout << "can't send";
                }
                iter++;
            }

        }

        mute.unlock();
    }
    close(connection);


}

