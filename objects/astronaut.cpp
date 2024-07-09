#include "headers/astronaut.h"

Astronaut::Astronaut(string cpf, string name, int age) : cpf(cpf), name(name), age(age), available(true), dead(false) {}

string Astronaut::getCpf() const
{
    return cpf;
}

string Astronaut::getName() const
{
    return name;
}

int Astronaut::getAge() const
{
    return age;
}

bool Astronaut::isAvailable() const
{
    return available;
}

bool Astronaut::isDead() const
{
    return dead;
}

void Astronaut::setAvailable(bool available)
{
    this->available = available;
}

void Astronaut::setDead(bool dead)
{
    this->dead = dead;
}
