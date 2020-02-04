# Flight Simulator - Part 1\2
Hello and welcome to Tzach Cohen and Zohar Rafter's FlightGear project - 1st Milestone

In this project you'll find everything you need in order to operate the Simulator.
Notice - this simulator program operates the plane automatically, without human intervention.
In order to get started, follow these simple steps:

1.Download and install the Flightgear Simulator from : https://www.flightgear.org/download/

1.1 Linux users can enter the terminal (Ctrl+Alt+T) and type : sudo add-apt-repository ppa:saiarcot895/flightgear

2.launch Flightgear, go to settings and add the following commands under "additional settings":

--telnet=socket,in,10,127.0.0.1,5400,tcp

--generic=socket,out,10,127.0.0.1,5402,tcp,generic_small

(The order of the lines does not matter!)

3.Add the "generic_small.xml" file to Flightgear/Protocol

3.1 Linux users - open the terminal and type : sudo nautilus /usr/share/games/flightgear/Protocol

4.Launch the program with the fly.txt file

5.Launch Flightgear and press the fly option.


Fly.txt and generic_small.xml are provided in this repository

