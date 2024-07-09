# Sistema de Gerenciamento de Astronautas e Voos

Este programa em C++ permite gerenciar astronautas e voos em um sistema espacial simulado.

## Compilação

Para compilar o programa, siga os passos abaixo:

### Pré-requisitos

Certifique-se de ter um compilador C++ instalado. Recomenda-se o uso do g++.

### Compilação usando g++

Use o seguinte comando para compilar o programa:

```
g++ main.cpp components/system.cpp objects/astronaut.cpp objects/flight.cpp -o spacemanagement
```

Este comando compilará o arquivo `main.cpp` junto com os arquivos necessários `system.cpp`, `astronaut.cpp` e `flight.cpp`, gerando um executável chamado spacemanagement.

## Execução

Após compilar o programa, execute-o usando o seguinte comando:

```
./spacemanagement
```

## Funcionalidades

O programa oferece as seguintes funcionalidades através de um menu interativo:

1.  Cadastrar Astronauta: Permite cadastrar um novo astronauta com CPF único, nome e idade.
2.  Cadastrar Voo: Registra um novo voo com um código único.
3.  Adicionar Astronauta em Voo: Associa um astronauta a um voo existente.
4.  Remover Astronauta de Voo: Remove um astronauta de um voo existente.
5.  Lançar Voo: Inicia um voo planejado.
6.  Explodir Voo: Interrompe um voo em curso, causando a morte dos astronautas.
7.  Finalizar Voo: Completa um voo que foi lançado com sucesso.
8.  Listar Voos: Mostra a lista de voos planejados, em curso e finalizados.
9.  Listar Astronautas Mortos: Exibe a lista de astronautas mortos.
10. Listar Astronautas Vivos: Exibe a lista de astronautas vivos.
11. Sair: Encerra o programa.
