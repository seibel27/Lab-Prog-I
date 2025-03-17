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
#include <locale.h>

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
typedef enum {Fogo, Vento, Raio, Terra, Agua} Natureza; //Fogo, Vento, Raio, Terra, Água
char *rankNomes[] = {"D", "C", "B", "A", "S"};
char *patenteNomes[] = {"Sem Patente", "Genin", "Chunin", "Jonin"};
char *naturezaNomes[] = {"Katon", "Fuuton", "Raiton", "Doton", "Suiton"};


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

void mensagemInicial();
void printKonohaSymbol();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    mensagemInicial();
    //printKonohaSymbol();

    ///Verificar se há um arquivo?
    ///Criar ou abrir arquivo (trataremos tudo em binário)

    ///Ler arquivo
    ///Puxar informações
    ///Fechar arquivo

    ///Rodar o sistema
        ///Apresentação do menu()
            ///Opções do menu()
            ///Printar todos os ninjas cadastrados
            ///Printar todas as missões cadastradas
            ///Adicionar ou remover um ninja
            ///Adicionar ou remover uma missão
            ///Editar um ninja......?
            ///Editar uma missão....?
            ///Printar um ninja - perfil completo

    ///No caso de salvamento
        ///Abrir o arquivo
        ///Realizar alteração
        ///Fechar arquivo

    ///No caso de finalizar sessão no sistema
        ///Liberar as memórias alocadas


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
    printf("\n\n\n\n\nVersão 1.0    ->Mente Criativa: Jiraya    ->Mente Operacional: Shikamaru    ->Responsável pelos bugs: Obito\n");
    printf("Versão criada, gerida e distribuída pela Vila Secreta da Aldeia da Folha.\nCopyright © 2025 Naruto.  Todos os direitos reservados.\n");

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


