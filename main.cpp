#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include "components/headers/system.h"
using namespace std;

void clearScreen()
{
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

int getIntInput()
{
    int input;
    while (true)
    {
        cin >> input;
        if (!cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida! Por favor tente novamente.\n";
            continue;
        }
        else
            break;
    }
    return input;
}

void showMenu()
{
    cout << "1.  Cadastrar Astronauta\n";
    cout << "2.  Cadastrar Voo\n";
    cout << "3.  Adicionar Astronauta em Voo\n";
    cout << "4.  Remover Astronauta de Voo\n";
    cout << "5.  Lançar Voo\n";
    cout << "6.  Explodir Voo\n";
    cout << "7.  Finalizar Voo\n";
    cout << "8.  Listar Voos\n";
    cout << "9.  Listar Astronautas Mortos\n";
    cout << "10. Listar Astronautas Vivos\n";
    cout << "0.  Sair\n";
    cout << "Escolha uma opção: ";
}

int main()
{
    System system;
    int option;

    do
    {
        clearScreen();
        showMenu();
        cin >> option;
        cin.ignore();

        string cpf, name;
        int age, flightCode;
        bool success;

        switch (option)
        {
        case 1:
            clearScreen();
            cout << "Digite o CPF do astronauta sem pontuação: (Ex.: 75870020140) \n";
            getline(cin, cpf);
            cout << "Digite o nome do astronauta: \n";
            getline(cin, name);
            cout << "Digite a idade do astronauta: \n";
            age = getIntInput();
            system.registerAstronaut(cpf, name, age);
            break;

        case 2:
            clearScreen();
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.registerFlight(flightCode);
            break;

        case 3:
            clearScreen();
            cout << "Digite o CPF do astronauta sem pontuação: (Ex.: 75870020140) \n";
            getline(cin, cpf);
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.addAstronautInFlight(cpf, flightCode);
            break;

        case 4:
            clearScreen();
            cout << "Digite o CPF do astronauta sem pontuação: (Ex.: 75870020140) \n";
            getline(cin, cpf);
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.delAstronautInFlight(cpf, flightCode);
            break;

        case 5:
            clearScreen();
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.launchFlight(flightCode);
            break;

        case 6:
            clearScreen();
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.explodeFlight(flightCode);
            break;

        case 7:
            clearScreen();
            cout << "Digite o código do voo: \n";
            flightCode = getIntInput();
            system.finishFlight(flightCode);
            break;

        case 8:
            clearScreen();
            system.listFlights();
            break;

        case 9:
            clearScreen();
            system.listDeadAstronauts();
            break;

        case 10:
            clearScreen();
            system.listAliveAstronauts();
            break;

        case 0:
            cout << "Saindo...\n";
            break;

        default:
            cerr << "Opção inválida! Tente novamente.\n";
            break;
        }
        if (option != 0)
        {
            cout << "Pressione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (option != 0);

    return 0;
}
