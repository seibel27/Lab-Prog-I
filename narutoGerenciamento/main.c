/*
Trabalho pr�tico da revis�o � v3

Voc� foi designado para confeccionar um sistema de gerenciamento de
ninjas e miss�es

As entidades do sistema mais importantes s�o: ninjas e miss�es

Cada ninja, possui um c�digo (5 d�gitos), nome e patente

Cada miss�o possui um c�digo (4 d�gitos), nome, rank (D, C, B, A, S) e
recompensa

Seu sistema deve ser capaz de armazenar uma lista de ninjas e a lista de
miss�es organizadas por per�odo (por exemplo 1200 da Era Shinobi)

Todas as estruturas devem ser alocadas dinamicamente

Devem ser permitidas as op��es de inser��o e remo��o em todas as
listas, atrav�s de um menu de op��es

Al�m disso, devem ser permitidas consultas dos ninjas inscritos em uma
determinada miss�o e das miss�es que determinados ninjas est�o
jogando, tamb�m em um determinado per�odo.

Finalmente, o sistema deve permitir o salvamento e a recupera��o dos
dados entre sess�es

Entregar arquivo (m�nimo de 3 ninjas, miss�es e aloca��es)
*/

#include <stdio.h>
#include <stdlib.h>

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
char *rankNomes[] = {"D", "C", "B", "A", "S"};
char *patenteNomes[] = {"Sem Patente", "Genin", "Chunin", "Jonin"};


typedef struct ninjaStruct{
    int codigo; //5 d�gitos
    char *nome;
    Patente patente;

} Ninja;

typedef struct missaoStruct{
    short int codigo; //4 d�gitos
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
