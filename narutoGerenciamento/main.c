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
#include <locale.h>

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
typedef enum {Fogo, Vento, Raio, Terra, Agua} Natureza; //Fogo, Vento, Raio, Terra, �gua
char *rankNomes[] = {"D", "C", "B", "A", "S"};
char *patenteNomes[] = {"Sem Patente", "Genin", "Chunin", "Jonin"};
char *naturezaNomes[] = {"Katon", "Fuuton", "Raiton", "Doton", "Suiton"};


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

void mensagemInicial();
void printKonohaSymbol();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    mensagemInicial();
    //printKonohaSymbol();

    ///Verificar se h� um arquivo?
    ///Criar ou abrir arquivo (trataremos tudo em bin�rio)

    ///Ler arquivo
    ///Puxar informa��es
    ///Fechar arquivo

    ///Rodar o sistema
        ///Apresenta��o do menu()
            ///Op��es do menu()
            ///Printar todos os ninjas cadastrados
            ///Printar todas as miss�es cadastradas
            ///Adicionar ou remover um ninja
            ///Adicionar ou remover uma miss�o
            ///Editar um ninja......?
            ///Editar uma miss�o....?
            ///Printar um ninja - perfil completo

    ///No caso de salvamento
        ///Abrir o arquivo
        ///Realizar altera��o
        ///Fechar arquivo

    ///No caso de finalizar sess�o no sistema
        ///Liberar as mem�rias alocadas


    Rank rank = A;
    Patente patente = 3;
    printf("Rank do ninja: %s\nPatente do ninja: %s", rankNomes[rank], patenteNomes[patente]);
    return 0;
}



void mensagemInicial(){
    for(int i=0;i<110;i++){
        printf("#");
    }

    printf("\n\n\t\t\tSEJA BEM-VINDO AO SISTEMA GERAL DE REGISTRO DE KONOHA\n\n");
    printf("\n\n\n\t   A PEDIDO DE KAKASHI E JIRAYA PARA SHIKAMARU, ESTE SISTEMA FOI CRIADO\t\n\tA FIM DE MELHOR CONTROLE DE SHINOBIS DA FOLHA, SHINOBIS ALIADOS E SHINOBIS INIMIGOS\t\n\n");
    printf("\n\n\n\n\nVers�o 1.0    ->Mente Criativa: Jiraya    ->Mente Operacional: Shikamaru    ->Respons�vel pelos bugs: Obito\n");
    printf("Vers�o criada, gerida e distribu�da pela Vila Secreta da Aldeia da Folha.\nCopyright � 2025 Naruto.  Todos os direitos reservados.\n");

    for(int j=0;j<110;j++){
        printf("#");
    }
    printf("\n\n");
    return;
}


void printKonohaSymbol() {
    printf("                              \n");
    printf("                              \n");
    printf("                              \n");
    printf("             ########       ##\n");
    printf("           ####    ####   ### \n");
    printf("         ###          ######  \n");
    printf("        ##              ##    \n");
    printf("       ##                     \n");
    printf("      ##     ######           \n");
    printf("      #    ####  ####         \n");
    printf("     ##   ##        ##        \n");
    printf("     ##   #          ##       \n");
    printf("     #   ##    ###    ##      \n");
    printf("    ##   ##      ##    #      \n");
    printf("    ##    #       ##   ##     \n");
    printf("    ##    ##      ##   ##     \n");
    printf("   ####    ##    ##    ##     \n");
    printf("   # ##     ######     ##     \n");
    printf("  ##  ##               ##     \n");
    printf("  #   ##              ##      \n");
    printf(" ##    ###           ##       \n");
    printf("############      ####        \n");
    printf("####################          \n");
    printf("                              \n");
    printf("                              \n");
    printf("                              \n");
    printf("                              \n");
    return;
}


