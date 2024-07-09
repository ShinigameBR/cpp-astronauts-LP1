#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include "../../objects/headers/astronaut.h"
#include "../../objects/headers/flight.h"
using namespace std;

class System
{
private:
    vector<Astronaut> astronauts;
    vector<Flight> flights;
    bool isValidCpf(const string &cpf);

public:
    void registerAstronaut(const string &cpf, const string &name, int age);
    void registerFlight(int code);
    void addAstronautInFlight(const string &cpf, int flightCode);
    void delAstronautInFlight(const string &cpf, int flightCode);
    void launchFlight(int flightCode);
    void explodeFlight(int flightCode);
    void finishFlight(int flightCode);
    void listFlights() const;
    void listDeadAstronauts() const;
    void listAliveAstronauts() const;
};

#endif
