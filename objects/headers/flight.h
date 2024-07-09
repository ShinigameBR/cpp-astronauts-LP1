#ifndef FLIGHT_H
#define FLIGHT_H

#include <vector>
#include "astronaut.h"
using namespace std;

class Flight
{
private:
    int code;
    vector<reference_wrapper<Astronaut>> passengers;
    bool inProgress;
    bool finished;

public:
    Flight(int code);

    int getCode() const;
    const vector<reference_wrapper<Astronaut>> &getPassengers() const;
    bool isInProgress() const;
    bool isFinished() const;

    void addPassenger(Astronaut &astronaut);
    void delPassenger(Astronaut &astronaut);
    void launch();
    void explode();
    void finish();
};

#endif
