/*
Trabalho prático da revisão – v3

Você foi designado para confeccionar um sistema de gerenciamento de
ninjas e missões

As entidades do sistema mais importantes são: ninjas e missões

Cada ninja, possui um código (5 dígitos), nome e patente

Cada missão possui um código (4 dígitos), nome, rank (D, C, B, A, S) e
recompensa

Seu sistema deve ser capaz de armazenar uma lista de ninjas e a lista de
missões organizadas por período (por exemplo 1200 da Era Shinobi)

Todas as estruturas devem ser alocadas dinamicamente

Devem ser permitidas as opções de inserção e remoção em todas as
listas, através de um menu de opções

Além disso, devem ser permitidas consultas dos ninjas inscritos em uma
determinada missão e das missões que determinados ninjas estão
jogando, também em um determinado período.

Finalmente, o sistema deve permitir o salvamento e a recuperação dos
dados entre sessões

Entregar arquivo (mínimo de 3 ninjas, missões e alocações)
*/

#include <stdio.h>
#include <stdlib.h>

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
char *rankNomes[] = {"D", "C", "B", "A", "S"};
char *patenteNomes[] = {"Sem Patente", "Genin", "Chunin", "Jonin"};


typedef struct ninjaStruct{
    int codigo; //5 dígitos
    char *nome;
    Patente patente;

} Ninja;

typedef struct missaoStruct{
    short int codigo; //4 dígitos
    char *nome;
    Rank rank;
    unsigned int recompensa;
    short unsigned int ano;
    ///Lista de ninjas envolvidos

} Missao;

int main()
{
    ///Testando
    Rank rank = A;
    Patente patente = 3;
    printf("Rank do ninja: %s\nPatente do ninja: %s", rankNomes[rank], patenteNomes[patente]);
    return 0;
}
