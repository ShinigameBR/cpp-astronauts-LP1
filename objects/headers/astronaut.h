#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include <string>
using namespace std;

class Astronaut
{
private:
    string cpf;
    string name;
    int age;
    bool available;
    bool dead;

public:
    Astronaut(string cpf, string name, int age);

    string getCpf() const;
    string getName() const;
    int getAge() const;
    bool isAvailable() const;
    bool isDead() const;

    void setAvailable(bool available);
    void setDead(bool dead);
};

#endif
