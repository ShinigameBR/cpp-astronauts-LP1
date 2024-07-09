#include "headers/system.h"

bool System::isValidCpf(const string &cpf)
{
    if (cpf.size() != 11)
    {
        return false;
    }
    return all_of(cpf.begin(), cpf.end(), ::isdigit);
}

void System::registerAstronaut(const string &cpf, const string &name, int age)
{
    if (!isValidCpf(cpf))
    {
        cerr << "Erro: CPF inválido. O CPF deve conter exatamente 11 dígitos positivos.\n";
        return;
    }
    auto it = find_if(astronauts.begin(), astronauts.end(), [&](const Astronaut &a)
                      { return a.getCpf() == cpf; });
    if (it != astronauts.end())
    {
        cerr << "Erro: Astronauta com CPF " << cpf << " já está cadastrado.\n";
    }
    if (age <= 0)
    {
        cerr << "Erro: Idade não pode ser negativa ou zero.\n";
        return;
    }
    else
    {
        astronauts.push_back(Astronaut(cpf, name, age));
    }
}

void System::registerFlight(int code)
{
    if (code < 0)
    {
        cerr << "Erro: Código do voo não pode ser negativo.\n";
        return;
    }
    auto it = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                      { return f.getCode() == code; });
    if (it != flights.end())
    {
        cerr << "Erro: Voo com código " << code << " já está cadastrado.\n";
    }
    else
    {
        flights.push_back(Flight(code));
    }
}

void System::addAstronautInFlight(const string &cpf, int flightCode)
{
    auto flightIt = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                            { return f.getCode() == flightCode; });
    if (flightIt == flights.end())
    {
        cerr << "Erro: Voo com código " << flightCode << " não encontrado.\n";
        return;
    }

    if (flightIt->isInProgress())
    {
        cerr << "Erro: Não é possível adicionar astronauta em voo já iniciado.\n";
        return;
    }

    auto astronautIt = find_if(astronauts.begin(), astronauts.end(), [&](const Astronaut &a)
                               { return a.getCpf() == cpf; });
    if (astronautIt == astronauts.end())
    {
        cerr << "Erro: Astronauta com CPF " << cpf << " não encontrado.\n";
        return;
    }

    auto passengerIt = find_if(flightIt->getPassengers().begin(), flightIt->getPassengers().end(), [&](const reference_wrapper<Astronaut> &ref)
                               { return ref.get().getCpf() == cpf; });
    if (passengerIt != flightIt->getPassengers().end())
    {
        cerr << "Erro: Astronauta " << astronautIt->getName() << " (CPF: " << astronautIt->getCpf() << ") já está no voo.\n";
        return;
    }

    if (astronautIt->isDead())
    {
        cerr << "Erro: Astronauta " << astronautIt->getName() << " (CPF: " << astronautIt->getCpf() << ") está morto.\n";
        return;
    }

    flightIt->addPassenger(*astronautIt);
}

void System::delAstronautInFlight(const string &cpf, int flightCode)
{
    auto flightIt = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                            { return f.getCode() == flightCode; });
    if (flightIt == flights.end())
    {
        cerr << "Erro: Voo com código " << flightCode << " não encontrado.\n";
        return;
    }

    if (flightIt->isInProgress())
    {
        cerr << "Erro: Não é possível remover astronauta de voo já iniciado.\n";
        return;
    }

    auto passengerIt = find_if(flightIt->getPassengers().begin(), flightIt->getPassengers().end(), [&](const reference_wrapper<Astronaut> &ref)
                               { return ref.get().getCpf() == cpf; });
    if (passengerIt == flightIt->getPassengers().end())
    {
        cerr << "Erro: Astronauta com CPF " << cpf << " não encontrado neste voo.\n";
        return;
    }

    flightIt->delPassenger(passengerIt->get());
}

void System::launchFlight(int flightCode)
{
    auto flightIt = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                            { return f.getCode() == flightCode; });
    if (flightIt == flights.end())
    {
        cerr << "Erro: Voo com código " << flightCode << " não encontrado.\n";
        return;
    }

    if (flightIt->isInProgress())
    {
        cerr << "Erro: Voo com código " << flightCode << " já está em curso.\n";
        return;
    }

    if (flightIt->getPassengers().empty())
    {
        cerr << "Erro: Voo com código " << flightCode << " não pode ser lançado sem astronautas.\n";
        return;
    }

    for (auto &passengerRef : flightIt->getPassengers())
    {
        Astronaut &passenger = passengerRef.get();

        if (passenger.isDead())
        {
            cerr << "Erro: Astronauta " << passenger.getName() << " (CPF: " << passenger.getCpf() << ") está morto.\n";
            return;
        }

        if (!passenger.isAvailable())
        {
            cerr << "Erro: Astronauta " << passenger.getName() << " (CPF: " << passenger.getCpf() << ") não está disponível.\n";
            return;
        }

        auto it = find_if(astronauts.begin(), astronauts.end(), [&](Astronaut &a)
                          { return a.getCpf() == passenger.getCpf(); });
        if (it != astronauts.end())
        {
            it->setAvailable(false);
        }
    }

    flightIt->launch();
}

void System::explodeFlight(int flightCode)
{
    auto flightIt = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                            { return f.getCode() == flightCode; });
    if (flightIt == flights.end())
    {
        cerr << "Erro: Voo com código " << flightCode << " não encontrado.\n";
        return;
    }

    if (!flightIt->isInProgress())
    {
        cerr << "Erro: Voo com código " << flightCode << " não está em curso.\n";
        return;
    }

    flightIt->explode();
}

void System::finishFlight(int flightCode)
{
    auto flightIt = find_if(flights.begin(), flights.end(), [&](const Flight &f)
                            { return f.getCode() == flightCode; });
    if (flightIt == flights.end())
    {
        cerr << "Erro: Voo com código " << flightCode << " não encontrado.\n";
        return;
    }

    if (!flightIt->isInProgress())
    {
        cerr << "Erro: Voo com código " << flightCode << " não está em curso.\n";
        return;
    }

    flightIt->finish();
}

void System::listFlights() const
{
    cout << "--- Voos Planejados: ---\n";
    for (const auto &flight : flights)
    {
        if (!flight.isInProgress() && !flight.isFinished())
        {
            cout << "Voo " << flight.getCode() << ":\n";
            cout << "Passageiros:\n";
            for (const auto &passengerRef : flight.getPassengers())
            {
                cout << passengerRef.get().getName() << " (CPF: " << passengerRef.get().getCpf() << ")\n";
            }
            cout << "Status: Planejado\n";
            cout << "------------------------\n";
        }
    }

    cout << "---  Voos em Curso:  ---\n";
    for (const auto &flight : flights)
    {
        if (flight.isInProgress())
        {
            cout << "Voo " << flight.getCode() << ":\n";
            cout << "Passageiros:\n";
            for (const auto &passengerRef : flight.getPassengers())
            {
                cout << passengerRef.get().getName() << " (CPF: " << passengerRef.get().getCpf() << ")\n";
            }
            cout << "Status: Em curso\n";
            cout << "------------------------\n";
        }
    }

    cout << "--- Voos Finalizados ---\n";
    for (const auto &flight : flights)
    {
        if (!flight.isInProgress() && flight.isFinished())
        {
            cout << "Voo " << flight.getCode() << ":\n";
            cout << "Passageiros:\n";
            for (const auto &passengerRef : flight.getPassengers())
            {
                cout << passengerRef.get().getName() << " (CPF: " << passengerRef.get().getCpf() << ")\n";
            }
            cout << "Status: Finalizado\n";
            cout << "------------------------\n";
        }
    }
}

void System::listDeadAstronauts() const
{
    cout << "Astronautas Mortos:\n";
    for (const auto &astronaut : astronauts)
    {
        if (astronaut.isDead())
        {
            cout << "   CPF: " << astronaut.getCpf() << ", Nome: " << astronaut.getName() << "\n";
        }
    }
}

void System::listAliveAstronauts() const
{
    cout << "Astronautas Vivos:\n";
    for (const auto &astronaut : astronauts)
    {
        if (!astronaut.isDead())
        {

            cout << "   CPF: " << astronaut.getCpf() << ", Nome: " << astronaut.getName()
                 << ", Disponibilidade: " << (astronaut.isAvailable() ? "Disponível" : "Indisponível") << "\n";
        }
    }
}