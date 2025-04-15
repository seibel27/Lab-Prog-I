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
#define BUFFER_MAX 255

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
typedef enum {Fogo, Vento, Raio, Terra, Agua} Natureza; //Fogo, Vento, Raio, Terra, �gua
char *rankNomes[] = {"D", "C", "B", "A", "S"};
char *patenteNomes[] = {"Sem Patente", "Genin", "Chunin", "Jonin"};
char *naturezaNomes[] = {"Katon", "Fuuton", "Raiton", "Doton", "Suiton"};

typedef struct {
    float ninjutsu, forca, taijutsu, velocidade, genjutsu, estamina, inteligencia, selos;
} Habilidades;

typedef struct {
    char *vila;
    char *cargoEspecial;
    char *kekkeiGenkai;
    char *cla;
    int naturezas[5];
    char *invocacao;
    Habilidades habilidades;
} DescricaoCompleta;

typedef struct ninjaStruct {
    int codigo; //5 digitos
    char *nome;
    Patente patente;
    DescricaoCompleta *descricao;
} Ninja;

typedef struct missaoStruct {
    short int codigo; //4 digitos
    char *nome;
    Rank rank;
    unsigned int recompensa;
    short unsigned int ano;
} Missao;

typedef struct ninjaNode {
    Ninja *ninja;
    struct ninjaNode *prox;
} NinjaNode;

typedef struct missaoNode {
    Missao *missao;
    struct missaoNode *prox;
    NinjaNode *participantes;
} MissaoNode;

typedef struct periodoNode {
    short unsigned int ano;
    MissaoNode *missoes;
    struct periodoNode *prox;
} PeriodoNode;

typedef struct sistema {
    NinjaNode *ninjas;
    PeriodoNode *periodos;
} Sistema;

///Declarando escopo das fun��es auxiliares
void mensagemInicial();
void printKonohaSymbol();
char *getTexto();
DescricaoCompleta *criarDescricaoPadrao();
DescricaoCompleta *criarDescricaoPersonalizada();
Ninja *criarNinja(Sistema *sistema);
void inserirNinja(Sistema *s, Ninja *n);
void exibirPerfilNinja(Sistema *sistema, int codigo);
void listarTodosNinjas(Sistema *s);
Missao *criarMissao(Sistema *sistema);
Ninja *buscarNinja(Sistema *sistema, int codigo);
MissaoNode *buscarMissao(Sistema *sistema, short int codigo, short unsigned int ano);
PeriodoNode *buscarOuCriarPeriodo(Sistema *sistema, short unsigned int ano);
void inserirMissao(Sistema *sistema, Missao *m);
void exibirPerfilMissao(Sistema *sistema, short int codigo, short unsigned int ano);
void removerMissao(Sistema *sistema, short int codigo, short unsigned int ano);
void removerNinja(Sistema *sistema, int codigo);
void consultarMissoesDoNinja(Sistema *sistema, int codigoNinja, short unsigned int ano);
void consultarNinjasDaMissao(Sistema *sistema, short int codigoMissao, short unsigned int ano);
void alocarNinjaEmMissao(Sistema *sistema, int codNinja, short int codMissao, short unsigned int ano);
void listarMissoesPorAno(Sistema *s, short unsigned int ano);
void listarTodasMissoes(Sistema *s);
void salvarSistema(Sistema *sistema, const char *nomeArquivo);
void carregarSistema(Sistema *sistema, const char *nomeArquivo);
void liberarSistema(Sistema *sistema);
void menu(Sistema *s);
// alguma coisa com missao
// validarCodigo
// busca
// inser��o
// remo��o

/* int main()
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
*/
int main() {
    setlocale(LC_ALL, "Portuguese");
    mensagemInicial();

    Sistema sistema;
    sistema.ninjas = NULL;
    sistema.periodos = NULL;

    carregarSistema(&sistema, "dados_konoha.bin");
    menu(&sistema);
    salvarSistema(&sistema, "dados_konoha.bin");

    return 0;
}


void mensagemInicial(){
    for(int i=0;i<110;i++){
        printf("#");
    }
    printf("\n\n\t\t\tSEJA BEM-VINDO AO SISTEMA GERAL DE REGISTRO DE KONOHA\n\n");
    printf("\n\n\n\t   A PEDIDO DE KAKASHI E JIRAYA PARA SHIKAMARU, ESTE SISTEMA FOI CRIADO\t\n\tA FIM DE MELHOR CONTROLE DE SHINOBIS DA FOLHA, SHINOBIS ALIADOS E SHINOBIS INIMIGOS\t\n\n");
    printf("\n\n\n\n\nVers�o 1.0    ->Mente Criativa: Jiraiya    ->Mente Operacional: Shikamaru    ->Respons�vel pelos bugs: Obito\n");
    printf("Vers�o criada, gerida e distribu�da pela Vila Secreta da Aldeia da Folha.\nCopyright � 2025 Naruto.  Todos os direitos reservados.\n");

    for(int j=0;j<110;j++){
        printf("#");
    }
    printf("\n\n");
    return;
}

char *getTexto() {
    char buffer[BUFFER_MAX];
    scanf(" %[^\n]", buffer); // L� at� a quebra de linha (inclusive espa�os)
    char *texto = (char *)malloc(strlen(buffer) + 1); // Aloca mem�ria
    strcpy(texto, buffer); // Copia o conte�do do buffer para a mem�ria alocada
    return texto;
}

DescricaoCompleta *criarDescricaoPadrao() {
    DescricaoCompleta *d = (DescricaoCompleta *)malloc(sizeof(DescricaoCompleta));
    d->vila = strdup("Vila Secreta da Aldeia da Folha");
    d->cargoEspecial = strdup("Nenhum");
    d->kekkeiGenkai = strdup("Nenhuma");
    d->cla = strdup("Nenhum");
    d->invocacao = strdup("Nenhuma");
    for (int i = 0; i < 5; i++) d->naturezas[i] = 0;
    d->habilidades = (Habilidades){0};
    return d;
}

DescricaoCompleta *criarDescricaoPersonalizada() {
    DescricaoCompleta *d = (DescricaoCompleta *)malloc(sizeof(DescricaoCompleta));

    printf("Vila do ninja: ");
    d->vila = getTexto();

    printf("Cargo especial (se nenhum, digite 'Nenhum'): ");
    d->cargoEspecial = getTexto();

    printf("Kekkei Genkai (se nenhuma, digite 'Nenhuma'): ");
    d->kekkeiGenkai = getTexto();

    printf("Cl� (se nenhum, digite 'Nenhum'): ");
    d->cla = getTexto();

    printf("Invoca��o especial (se nenhuma, digite 'Nenhuma'): ");
    d->invocacao = getTexto();

    printf("Selecione as naturezas dominadas (0 ou 1 para cada):\n");
    for (int i = 0; i < 5; i++) {
        printf("Domina %s? (0 = n�o, 1 = sim): ", naturezaNomes[i]);
        scanf("%d", &d->naturezas[i]);
    }

    printf("Agora, defina as estat�sticas do ninja (0,0 a 5,0):\nUtilize v�rgula para a casa decimal.\n");
    printf("Ninjutsu: ");       scanf("%f", &d->habilidades.ninjutsu);
    printf("For�a: ");          scanf("%f", &d->habilidades.forca);
    printf("Taijutsu: ");       scanf("%f", &d->habilidades.taijutsu);
    printf("Velocidade: ");     scanf("%f", &d->habilidades.velocidade);
    printf("Genjutsu: ");       scanf("%f", &d->habilidades.genjutsu);
    printf("Estamina: ");       scanf("%f", &d->habilidades.estamina);
    printf("Intelig�ncia: ");   scanf("%f", &d->habilidades.inteligencia);
    printf("Selos: ");          scanf("%f", &d->habilidades.selos);
    getchar(); // limpa \n

    return d;
}

Ninja *criarNinja(Sistema *sistema) {
    Ninja *novo = (Ninja *)malloc(sizeof(Ninja));

    printf("\n--- Cadastro de novo ninja ---\n");

    // Valida��o de unicidade do c�digo
    do {
        printf("C�digo do ninja (5 d�gitos): ");
        scanf("%d", &novo->codigo);
        getchar();

        if (buscarNinja(sistema, novo->codigo) != NULL) {
            printf("[!] J� existe um ninja com esse c�digo. Escolha outro.\n");
        } else {
            break;
        }
    } while (1);

    printf("Nome do ninja: ");
    novo->nome = getTexto();

    printf("Patente (0: Sem Patente, 1: Genin, 2: Chunin, 3: Jonin): ");
    int pat;
    scanf("%d", &pat);
    novo->patente = (Patente)pat;
    getchar();

    printf("Deseja definir o perfil completo do ninja? (s/n): ");
    char opcao;
    scanf("%c", &opcao);
    getchar();

    if (opcao == 's' || opcao == 'S')
        novo->descricao = criarDescricaoPersonalizada();
    else
        novo->descricao = criarDescricaoPadrao();

    printf("\nNinja %s criado com sucesso!\n", novo->nome);
    return novo;
}


void inserirNinja(Sistema *s, Ninja *n) {
    NinjaNode *no = (NinjaNode *)malloc(sizeof(NinjaNode));
    no->ninja = n;
    no->prox = s->ninjas;
    s->ninjas = no;
}

void exibirPerfilNinja(Sistema *sistema, int codigo) {
    Ninja *ninja = buscarNinja(sistema, codigo);

    if (ninja == NULL) {
        printf("Ninja com c�digo %05d n�o encontrado.\n", codigo);
        return;
    }

    printf("\n===== PERFIL COMPLETO DO NINJA =====\n");
    printf("Nome: %s\n", ninja->nome);
    printf("C�digo: %05d\n", ninja->codigo);
    printf("Patente: %s\n", patenteNomes[ninja->patente]);

    DescricaoCompleta *desc = ninja->descricao;
    printf("Vila: %s\n", desc->vila);
    printf("Cargo Especial: %s\n", desc->cargoEspecial);
    printf("Kekkei Genkai: %s\n", desc->kekkeiGenkai);
    printf("Cl�: %s\n", desc->cla);
    printf("Invoca��o Especial: %s\n", desc->invocacao);

    printf("Naturezas dominadas: ");
    int temNatureza = 0;
    for (int i = 0; i < 5; i++) {
        if (desc->naturezas[i]) {
            printf("%s ", naturezaNomes[i]);
            temNatureza = 1;
        }
    }
    if (!temNatureza) printf("Nenhuma");
    printf("\n");
    float totalHabilidades = desc->habilidades.ninjutsu + desc->habilidades.forca + desc->habilidades.taijutsu + desc->habilidades.velocidade + desc->habilidades.genjutsu + desc->habilidades.estamina + desc->habilidades.inteligencia + desc->habilidades.selos;
    printf("\n>>> Habilidades (%.1f)\n", totalHabilidades);
    printf("Ninjutsu: %.1f\n", desc->habilidades.ninjutsu);
    printf("For�a: %.1f\n", desc->habilidades.forca);
    printf("Taijutsu: %.1f\n", desc->habilidades.taijutsu);
    printf("Velocidade: %.1f\n", desc->habilidades.velocidade);
    printf("Genjutsu: %.1f\n", desc->habilidades.genjutsu);
    printf("Estamina: %.1f\n", desc->habilidades.estamina);
    printf("Intelig�ncia: %.1f\n", desc->habilidades.inteligencia);
    printf("Selos: %.1f\n", desc->habilidades.selos);

    int encontrouMissao = 0;
    printf("\n>>> Miss�es realizadas:\n");
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        MissaoNode *m = p->missoes;
        while (m != NULL) {
            NinjaNode *n = m->participantes;
            while (n != NULL) {
                if (n->ninja->codigo == codigo) {
                    printf("- [%hu] %s (Rank: %s, Recompensa: %u)\n",
                        m->missao->ano,
                        m->missao->nome,
                        rankNomes[m->missao->rank],
                        m->missao->recompensa);
                    encontrouMissao = 1;
                    break;
                }
                n = n->prox;
            }
            m = m->prox;
        }
        p = p->prox;
    }

    if (!encontrouMissao) {
        printf("Nenhuma miss�o registrada.\n");
    }
    printf("====================================\n");
}

void listarTodosNinjas(Sistema *s) {
    if (s->ninjas == NULL) {
        printf("Nenhum ninja cadastrado no sistema.\n");
        return;
    }

    printf("\n===== LISTA DE TODOS OS NINJAS =====\n");
    NinjaNode *n = s->ninjas;
    while (n != NULL) {
        printf("- %s (C�digo: %05d, Patente: %s)\n",
               n->ninja->nome,
               n->ninja->codigo,
               patenteNomes[n->ninja->patente]);
        n = n->prox;
    }
    printf("===================================\n");
}

Missao *criarMissao(Sistema *sistema) {
    Missao *m = (Missao *)malloc(sizeof(Missao));

    printf("\n--- Cadastro de nova miss�o ---\n");

    do {
        printf("C�digo da miss�o (4 d�gitos): ");
        scanf("%hd", &m->codigo);

        printf("Ano/per�odo da miss�o (ex: 1200): ");
        scanf("%hu", &m->ano);

        if (buscarMissao(sistema, m->codigo, m->ano) != NULL) {
            printf("[!] J� existe uma miss�o com esse c�digo no ano %hu. Digite um c�digo diferente.\n", m->ano);
        } else {
            break;
        }
    } while (1);

    getchar(); // limpar buffer

    printf("Nome da miss�o: ");
    m->nome = getTexto();

    printf("Rank da miss�o (0: D, 1: C, 2: B, 3: A, 4: S): ");
    int r;
    scanf("%d", &r);
    m->rank = (Rank)r;

    printf("Recompensa: ");
    scanf("%u", &m->recompensa);

    return m;
}

Ninja *buscarNinja(Sistema *sistema, int codigo) {
    NinjaNode *atual = sistema->ninjas;
    while (atual != NULL) {
        if (atual->ninja->codigo == codigo)
            return atual->ninja;
        atual = atual->prox;
    }
    return NULL;
}

MissaoNode *buscarMissao(Sistema *sistema, short int codigo, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        if (p->ano == ano) {
            MissaoNode *m = p->missoes;
            while (m != NULL) {
                if (m->missao->codigo == codigo)
                    return m;
                m = m->prox;
            }
        }
        p = p->prox;
    }
    return NULL;
}

PeriodoNode *buscarOuCriarPeriodo(Sistema *sistema, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;

    while (p != NULL) {
        if (p->ano == ano) return p;
        p = p->prox;
    }

    // Criar novo
    p = (PeriodoNode *)malloc(sizeof(PeriodoNode));
    p->ano = ano;
    p->missoes = NULL;
    p->prox = sistema->periodos;
    sistema->periodos = p;

    return p;
}

void inserirMissao(Sistema *sistema, Missao *m) {
    PeriodoNode *periodo = buscarOuCriarPeriodo(sistema, m->ano);
    MissaoNode *nova = (MissaoNode *)malloc(sizeof(MissaoNode));
    nova->missao = m;
    nova->prox = periodo->missoes;
    nova->participantes = NULL;
    periodo->missoes = nova;
}

void alocarNinjaEmMissao(Sistema *sistema, int codNinja, short int codMissao, short unsigned int ano) {
    Ninja *ninja = buscarNinja(sistema, codNinja);
    if (ninja == NULL) {
        printf("Ninja com c�digo %05d n�o encontrado.\n", codNinja);
        return;
    }

    MissaoNode *missao = buscarMissao(sistema, codMissao, ano);
    if (missao == NULL) {
        printf("Miss�o com c�digo %04d no ano %hu n�o encontrada.\n", codMissao, ano);
        return;
    }

    // Verifica se j� est� alocado
    NinjaNode *p = missao->participantes;
    while (p != NULL) {
        if (p->ninja->codigo == codNinja) {
            printf("Ninja j� est� alocado nessa miss�o.\n");
            return;
        }
        p = p->prox;
    }

    // Aloca
    NinjaNode *novo = (NinjaNode *)malloc(sizeof(NinjaNode));
    novo->ninja = ninja;
    novo->prox = missao->participantes;
    missao->participantes = novo;

    printf("Ninja %s alocado com sucesso � miss�o %s.\n", ninja->nome, missao->missao->nome);
}

void removerNinja(Sistema *sistema, int codigo) {
    NinjaNode *atual = sistema->ninjas;
    NinjaNode *anterior = NULL;

    while (atual != NULL && atual->ninja->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Ninja com c�digo %d n�o encontrado.\n", codigo);
        return;
    }

    // Remover de poss�veis miss�es
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        MissaoNode *m = p->missoes;
        while (m != NULL) {
            NinjaNode *n = m->participantes;
            NinjaNode *n_ant = NULL;
            while (n != NULL) {
                if (n->ninja->codigo == codigo) {
                    if (n_ant == NULL)
                        m->participantes = n->prox;
                    else
                        n_ant->prox = n->prox;
                    free(n); // remove ninja da miss�o
                    break;
                }
                n_ant = n;
                n = n->prox;
            }
            m = m->prox;
        }
        p = p->prox;
    }

    // Remove da lista principal
    if (anterior == NULL)
        sistema->ninjas = atual->prox;
    else
        anterior->prox = atual->prox;

    free(atual->ninja->nome);
    free(atual->ninja);
    free(atual);
    printf("Ninja removido com sucesso!\n");
}

void liberarSistema(Sistema *sistema) {
    //Liberando os ninjas
    NinjaNode *n = sistema->ninjas;
    while (n) {
        NinjaNode *tmp = n;
        n = n->prox;
        free(tmp->ninja->descricao->vila);
        free(tmp->ninja->descricao->cargoEspecial);
        free(tmp->ninja->descricao->kekkeiGenkai);
        free(tmp->ninja->descricao->cla);
        free(tmp->ninja->descricao->invocacao);
        free(tmp->ninja->descricao);
        free(tmp->ninja->nome);
        free(tmp->ninja);
        free(tmp);
    }

    // Libera a lista de per�odos
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        PeriodoNode *auxPeriodo = p;
        p = p->prox;

        // Libera as miss�es dentro do per�odo
        MissaoNode *m = auxPeriodo->missoes;
        while (m != NULL) {
            MissaoNode *auxMissao = m;
            m = m->prox;

            // Libera participantes da miss�o
            NinjaNode *np = auxMissao->participantes;
            while (np != NULL) {
                NinjaNode *auxNp = np;
                np = np->prox;
                free(auxNp);
            }

            free(auxMissao->missao->nome);
            free(auxMissao->missao);
            free(auxMissao);
        }

        free(auxPeriodo);
    }

    sistema->ninjas = NULL;
    sistema->periodos = NULL;
}

void exibirPerfilMissao(Sistema *sistema, short int codigo, short unsigned int ano) {
    MissaoNode *m = buscarMissao(sistema, codigo, ano);

    if (m == NULL) {
        printf("Miss�o com c�digo %04d no ano %hu n�o encontrada.\n", codigo, ano);
        return;
    }

    printf("\n===== PERFIL DA MISS�O =====\n");
    printf("Nome: %s\n", m->missao->nome);
    printf("C�digo: %04d\n", m->missao->codigo);
    printf("Ano: %hu\n", m->missao->ano);
    printf("Rank: %s\n", rankNomes[m->missao->rank]);
    printf("Recompensa: %u\n", m->missao->recompensa);
    printf("Participantes:\n");

    if (m->participantes == NULL) {
        printf("- Nenhum ninja alocado.\n");
    } else {
        NinjaNode *n = m->participantes;
        while (n != NULL) {
            printf("- %s (C�digo: %05d, Patente: %s)\n",
                   n->ninja->nome,
                   n->ninja->codigo,
                   patenteNomes[n->ninja->patente]);
            n = n->prox;
        }
    }

    printf("============================\n");
}

void removerMissao(Sistema *sistema, short int codigo, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        if (p->ano == ano) {
            MissaoNode *m = p->missoes;
            MissaoNode *m_ant = NULL;

            while (m != NULL) {
                if (m->missao->codigo == codigo) {
                    // Remove todos os participantes da miss�o
                    NinjaNode *n = m->participantes;
                    while (n != NULL) {
                        NinjaNode *aux = n;
                        n = n->prox;
                        free(aux); // N�o libera o ninja, s� o n� da miss�o
                    }

                    if (m_ant == NULL)
                        p->missoes = m->prox;
                    else
                        m_ant->prox = m->prox;

                    free(m->missao->nome);
                    free(m->missao);
                    free(m);
                    printf("Miss�o removida com sucesso!\n");
                    return;
                }

                m_ant = m;
                m = m->prox;
            }

        }
        p = p->prox;
    }
    printf("Miss�o com c�digo %d no ano %d n�o encontrada.\n", codigo, ano);
}

void consultarMissoesDoNinja(Sistema *sistema, int codigoNinja, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;

    while (p != NULL) {
        if (p->ano == ano) {
            MissaoNode *m = p->missoes;
            int encontrou = 0;

            while (m != NULL) {
                NinjaNode *n = m->participantes;
                while (n != NULL) {
                    if (n->ninja->codigo == codigoNinja) {
                        printf("Miss�o: %s (C�digo: %04d, Rank: %s, Recompensa: %u)\n",
                               m->missao->nome, m->missao->codigo, rankNomes[m->missao->rank], m->missao->recompensa);
                        encontrou = 1;
                        break;
                    }
                    n = n->prox;
                }
                m = m->prox;
            }

            if (!encontrou)
                printf("Este ninja n�o participou de nenhuma miss�o no ano %hu.\n", ano);
            return;
        }
        p = p->prox;
    }

    printf("N�o h� miss�es registradas no ano %hu.\n", ano);
}

void consultarNinjasDaMissao(Sistema *sistema, short int codigoMissao, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;

    while (p != NULL) {
        if (p->ano == ano) {
            MissaoNode *m = p->missoes;

            while (m != NULL) {
                if (m->missao->codigo == codigoMissao) {
                    if (m->participantes == NULL) {
                        printf("Nenhum ninja registrado nesta miss�o.\n");
                        return;
                    }

                    printf("Ninjas na miss�o %s (c�digo %04d):\n", m->missao->nome, codigoMissao);
                    NinjaNode *n = m->participantes;
                    while (n != NULL) {
                        printf("- %s (c�digo: %05d, patente: %s)\n",
                               n->ninja->nome, n->ninja->codigo, patenteNomes[n->ninja->patente]);
                        n = n->prox;
                    }
                    return;
                }
                m = m->prox;
            }

            printf("Miss�o com c�digo %d n�o encontrada no ano %hu.\n", codigoMissao, ano);
            return;
        }
        p = p->prox;
    }

    printf("N�o h� miss�es registradas no ano %hu.\n", ano);
}

void listarTodasMissoes(Sistema *s) {
    if (s->periodos == NULL) {
        printf("Nenhuma miss�o cadastrada no sistema.\n");
        return;
    }

    printf("\n===== LISTA DE TODAS AS MISS�ES =====\n");
    PeriodoNode *p = s->periodos;
    while (p != NULL) {
        printf("\n--- Per�odo: %hu ---\n", p->ano);
        MissaoNode *m = p->missoes;
        if (!m) printf("(Nenhuma miss�o neste per�odo)\n");
        while (m != NULL) {
            Missao *ms = m->missao;
            printf("- C�digo: %04d | Nome: %s | Rank: %s | Recompensa: %u\n",
                   ms->codigo,
                   ms->nome,
                   rankNomes[ms->rank],
                   ms->recompensa);
            m = m->prox;
        }
        p = p->prox;
    }
    printf("=======================================\n");
}

void listarMissoesPorAno(Sistema *s, short unsigned int ano) {
    PeriodoNode *p = s->periodos;
    while (p != NULL) {
        if (p->ano == ano) {
            printf("\n===== MISS�ES DO ANO %hu =====\n", ano);
            MissaoNode *m = p->missoes;
            if (!m) {
                printf("Nenhuma miss�o cadastrada neste ano.\n");
            } else {
                while (m != NULL) {
                    Missao *ms = m->missao;
                    printf("- C�digo: %04d | Nome: %s | Rank: %s | Recompensa: %u\n",
                           ms->codigo,
                           ms->nome,
                           rankNomes[ms->rank],
                           ms->recompensa);
                    m = m->prox;
                }
            }
            printf("=======================================\n");
            return;
        }
        p = p->prox;
    }
    printf("Nenhum per�odo encontrado com o ano %hu.\n", ano);
}

void salvarSistema(Sistema *sistema, const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "wb");
    if (!arq) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    int qtdNinjas = 0;
    NinjaNode *n = sistema->ninjas;
    while (n != NULL) {
        qtdNinjas++;
        n = n->prox;
    }
    fwrite(&qtdNinjas, sizeof(int), 1, arq);

    n = sistema->ninjas;
    while (n != NULL) {
        Ninja *nj = n->ninja;
        int tamNome = strlen(nj->nome) + 1;
        fwrite(&nj->codigo, sizeof(int), 1, arq);
        fwrite(&tamNome, sizeof(int), 1, arq);
        fwrite(nj->nome, sizeof(char), tamNome, arq);
        fwrite(&nj->patente, sizeof(Patente), 1, arq);

        int tamVila = strlen(nj->descricao->vila) + 1;
        int tamCargo = strlen(nj->descricao->cargoEspecial) + 1;
        int tamKekkei = strlen(nj->descricao->kekkeiGenkai) + 1;
        int tamCla = strlen(nj->descricao->cla) + 1;
        int tamInvoc = strlen(nj->descricao->invocacao) + 1;

        fwrite(&tamVila, sizeof(int), 1, arq);
        fwrite(nj->descricao->vila, sizeof(char), tamVila, arq);
        fwrite(&tamCargo, sizeof(int), 1, arq);
        fwrite(nj->descricao->cargoEspecial, sizeof(char), tamCargo, arq);
        fwrite(&tamKekkei, sizeof(int), 1, arq);
        fwrite(nj->descricao->kekkeiGenkai, sizeof(char), tamKekkei, arq);
        fwrite(&tamCla, sizeof(int), 1, arq);
        fwrite(nj->descricao->cla, sizeof(char), tamCla, arq);
        fwrite(&tamInvoc, sizeof(int), 1, arq);
        fwrite(nj->descricao->invocacao, sizeof(char), tamInvoc, arq);

        fwrite(nj->descricao->naturezas, sizeof(int), 5, arq);
        fwrite(&nj->descricao->habilidades, sizeof(Habilidades), 1, arq);

        n = n->prox;
    }

    // salvar per�odos e miss�es
    int qtdPeriodos = 0;
    PeriodoNode *p = sistema->periodos;
    while (p) {
        qtdPeriodos++;
        p = p->prox;
    }
    fwrite(&qtdPeriodos, sizeof(int), 1, arq);

    p = sistema->periodos;
    while (p) {
        fwrite(&p->ano, sizeof(short unsigned int), 1, arq);

        int qtdMissoes = 0;
        MissaoNode *m = p->missoes;
        while (m) {
            qtdMissoes++;
            m = m->prox;
        }
        fwrite(&qtdMissoes, sizeof(int), 1, arq);

        m = p->missoes;
        while (m) {
            Missao *ms = m->missao;
            int tamNome = strlen(ms->nome) + 1;
            fwrite(&ms->codigo, sizeof(short int), 1, arq);
            fwrite(&tamNome, sizeof(int), 1, arq);
            fwrite(ms->nome, sizeof(char), tamNome, arq);
            fwrite(&ms->rank, sizeof(Rank), 1, arq);
            fwrite(&ms->recompensa, sizeof(unsigned int), 1, arq);
            fwrite(&ms->ano, sizeof(short unsigned int), 1, arq);

            int qtdParticipantes = 0;
            NinjaNode *np = m->participantes;
            while (np) {
                qtdParticipantes++;
                np = np->prox;
            }
            fwrite(&qtdParticipantes, sizeof(int), 1, arq);

            np = m->participantes;
            while (np) {
                fwrite(&np->ninja->codigo, sizeof(int), 1, arq);
                np = np->prox;
            }
            m = m->prox;
        }
        p = p->prox;
    }

    fclose(arq);
    printf("Sistema salvo com sucesso!\n");
}

void carregarSistema(Sistema *sistema, const char *nomeArquivo) {
    FILE *arq = fopen(nomeArquivo, "ab+");
    if (!arq) {
        printf("Erro ao tentar abrir o arquivo.\n");
        return;
    }
    rewind(arq);

    int qtdNinjas;
    if (fread(&qtdNinjas, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        printf("Arquivo vazio ou mal formatado.\n");
        return;
    }

    for (int i = 0; i < qtdNinjas; i++) {
        Ninja *n = (Ninja *)malloc(sizeof(Ninja));
        int tamNome;
        fread(&n->codigo, sizeof(int), 1, arq);
        fread(&tamNome, sizeof(int), 1, arq);
        n->nome = (char *)malloc(tamNome);
        fread(n->nome, sizeof(char), tamNome, arq);
        fread(&n->patente, sizeof(Patente), 1, arq);

        DescricaoCompleta *d = (DescricaoCompleta *)malloc(sizeof(DescricaoCompleta));
        int tamVila, tamCargo, tamKekkei, tamCla, tamInvoc;

        fread(&tamVila, sizeof(int), 1, arq);
        d->vila = (char *)malloc(tamVila);
        fread(d->vila, sizeof(char), tamVila, arq);

        fread(&tamCargo, sizeof(int), 1, arq);
        d->cargoEspecial = (char *)malloc(tamCargo);
        fread(d->cargoEspecial, sizeof(char), tamCargo, arq);

        fread(&tamKekkei, sizeof(int), 1, arq);
        d->kekkeiGenkai = (char *)malloc(tamKekkei);
        fread(d->kekkeiGenkai, sizeof(char), tamKekkei, arq);

        fread(&tamCla, sizeof(int), 1, arq);
        d->cla = (char *)malloc(tamCla);
        fread(d->cla, sizeof(char), tamCla, arq);

        fread(&tamInvoc, sizeof(int), 1, arq);
        d->invocacao = (char *)malloc(tamInvoc);
        fread(d->invocacao, sizeof(char), tamInvoc, arq);

        fread(d->naturezas, sizeof(int), 5, arq);
        fread(&d->habilidades, sizeof(Habilidades), 1, arq);

        n->descricao = d;
        inserirNinja(sistema, n);
    }

    int qtdPeriodos;
    if (fread(&qtdPeriodos, sizeof(int), 1, arq) != 1) {
        fclose(arq);
        return;
    }

    for (int i = 0; i < qtdPeriodos; i++) {
        short unsigned int ano;
        fread(&ano, sizeof(short unsigned int), 1, arq);

        int qtdMissoes;
        fread(&qtdMissoes, sizeof(int), 1, arq);

        for (int j = 0; j < qtdMissoes; j++) {
            Missao *m = (Missao *)malloc(sizeof(Missao));
            int tamNome;
            fread(&m->codigo, sizeof(short int), 1, arq);
            fread(&tamNome, sizeof(int), 1, arq);
            m->nome = (char *)malloc(tamNome);
            fread(m->nome, sizeof(char), tamNome, arq);
            fread(&m->rank, sizeof(Rank), 1, arq);
            fread(&m->recompensa, sizeof(unsigned int), 1, arq);
            fread(&m->ano, sizeof(short unsigned int), 1, arq);

            inserirMissao(sistema, m);
            MissaoNode *mNode = buscarMissao(sistema, m->codigo, m->ano);

            int qtdParticipantes;
            fread(&qtdParticipantes, sizeof(int), 1, arq);

            for (int k = 0; k < qtdParticipantes; k++) {
                int codNinja;
                fread(&codNinja, sizeof(int), 1, arq);
                Ninja *ninja = buscarNinja(sistema, codNinja);
                if (ninja && mNode) {
                    NinjaNode *novo = (NinjaNode *)malloc(sizeof(NinjaNode));
                    novo->ninja = ninja;
                    novo->prox = mNode->participantes;
                    mNode->participantes = novo;
                }
            }
        }
    }

    fclose(arq);
    printf("Sistema carregado com sucesso!\n");
}


void menu(Sistema *s) {
    int op;
    do {
        printf("\n--- MENU NINJA ---\n");
        printf("1. Cadastrar novo ninja\n");
        printf("2. Remover ninja\n");
        printf("3. Cadastrar nova miss�o\n");
        printf("4. Remover miss�o\n");
        printf("5. Consultar miss�es de um ninja em um per�odo\n");
        printf("6. Consultar ninjas de uma miss�o em um per�odo\n");
        printf("7. Alocar ninja a uma miss�o\n");
        printf("8. Exibir perfil de um ninja\n");
        printf("9. Exibir perfil de uma miss�o\n");
        printf("10. Listar todos os ninjas cadastrados\n");
        printf("11. Listar todas as miss�es cadastradas\n");
        printf("12. Listar miss�es de um ano espec�fico\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch(op) {
            case 1: {
                Ninja *n = criarNinja(s);
                inserirNinja(s, n);
                break;
            }
            case 2: {
                int codigo;
                printf("C�digo do ninja a ser removido: ");
                scanf("%d", &codigo);
                removerNinja(s, codigo);
                break;
            }
            case 3: {
                Missao *m = criarMissao(s);
                inserirMissao(s, m);
                break;
            }
            case 4: {
                short int cod;
                short unsigned int ano;
                printf("C�digo da miss�o: ");
                scanf("%hd", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                removerMissao(s, cod, ano);
                break;
            }
            case 5: {
                int cod;
                short unsigned int ano;
                printf("C�digo do ninja: ");
                scanf("%d", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                consultarMissoesDoNinja(s, cod, ano);
                break;
            }
            case 6: {
                short int cod;
                short unsigned int ano;
                printf("C�digo da miss�o: ");
                scanf("%hd", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                consultarNinjasDaMissao(s, cod, ano);
                break;
            }
            case 7: {
                int codNinja;
                short int codMissao;
                short unsigned int ano;
                printf("C�digo do ninja: ");
                scanf("%d", &codNinja);
                printf("C�digo da miss�o: ");
                scanf("%hd", &codMissao);
                printf("Ano: ");
                scanf("%hu", &ano);
                alocarNinjaEmMissao(s, codNinja, codMissao, ano);
                break;
            }
            case 8: {
                int cod;
                printf("C�digo do ninja: ");
                scanf("%d", &cod);
                exibirPerfilNinja(s, cod);
                break;
            }
            case 9: {
                short int cod;
                short unsigned int ano;
                printf("C�digo da miss�o: ");
                scanf("%hd", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                exibirPerfilMissao(s, cod, ano);
                break;
            }
            case 10:
                listarTodosNinjas(s);
                break;
            case 11:
                listarTodasMissoes(s);
                break;
            case 12: {
                short unsigned int ano;
                printf("Digite o ano desejado: ");
                scanf("%hu", &ano);
                listarMissoesPorAno(s, ano);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Op��o inv�lida!\n");
        }

    } while(op != 0);
}
