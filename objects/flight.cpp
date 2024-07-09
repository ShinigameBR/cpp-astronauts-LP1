#include "headers/flight.h"

Flight::Flight(int code) : code(code), inProgress(false), finished(false) {}

int Flight::getCode() const
{
    return code;
}

const vector<reference_wrapper<Astronaut>> &Flight::getPassengers() const
{
    return passengers;
}

bool Flight::isInProgress() const
{
    return inProgress;
}

bool Flight::isFinished() const
{
    return finished;
}

void Flight::addPassenger(Astronaut &astronaut)
{
    passengers.push_back(ref(astronaut));
}

void Flight::delPassenger(Astronaut &astronaut)
{
    for (auto it = passengers.begin(); it != passengers.end(); ++it)
    {
        if (&it->get() == &astronaut)
        {
            passengers.erase(it);
            break;
        }
    }
}

void Flight::launch()
{
    if (!passengers.empty())
    {
        inProgress = true;
        for (auto &astronaut : passengers)
        {
            astronaut.get().setAvailable(false);
        }
    }
}

void Flight::explode()
{
    for (auto &astronaut : passengers)
    {
        astronaut.get().setAvailable(false);
        astronaut.get().setDead(true);
    }
    inProgress = false;
    finished = true;
}

void Flight::finish()
{
    inProgress = false;
    finished = true;

    for (auto &astronaut : passengers)
    {
        astronaut.get().setAvailable(true);
    }
}
