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
#define BUFFER_MAX 255

//Criando as estruturas no escopo global
typedef enum {D,C,B,A,S} Rank;
typedef enum {SemPatente, Genin, Chunin, Jonin} Patente;
typedef enum {Fogo, Vento, Raio, Terra, Agua} Natureza; //Fogo, Vento, Raio, Terra, Água
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

///Declarando escopo das funções auxiliares
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
// inserção
// remoção

/* int main()
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
    printf("\n\n\n\n\nVersão 1.0    ->Mente Criativa: Jiraiya    ->Mente Operacional: Shikamaru    ->Responsável pelos bugs: Obito\n");
    printf("Versão criada, gerida e distribuída pela Vila Secreta da Aldeia da Folha.\nCopyright © 2025 Naruto.  Todos os direitos reservados.\n");

    for(int j=0;j<110;j++){
        printf("#");
    }
    printf("\n\n");
    return;
}

char *getTexto() {
    char buffer[BUFFER_MAX];
    scanf(" %[^\n]", buffer); // Lê até a quebra de linha (inclusive espaços)
    char *texto = (char *)malloc(strlen(buffer) + 1); // Aloca memória
    strcpy(texto, buffer); // Copia o conteúdo do buffer para a memória alocada
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

    printf("Clã (se nenhum, digite 'Nenhum'): ");
    d->cla = getTexto();

    printf("Invocação especial (se nenhuma, digite 'Nenhuma'): ");
    d->invocacao = getTexto();

    printf("Selecione as naturezas dominadas (0 ou 1 para cada):\n");
    for (int i = 0; i < 5; i++) {
        printf("Domina %s? (0 = não, 1 = sim): ", naturezaNomes[i]);
        scanf("%d", &d->naturezas[i]);
    }

    printf("Agora, defina as estatísticas do ninja (0,0 a 5,0):\nUtilize vírgula para a casa decimal.\n");
    printf("Ninjutsu: ");       scanf("%f", &d->habilidades.ninjutsu);
    printf("Força: ");          scanf("%f", &d->habilidades.forca);
    printf("Taijutsu: ");       scanf("%f", &d->habilidades.taijutsu);
    printf("Velocidade: ");     scanf("%f", &d->habilidades.velocidade);
    printf("Genjutsu: ");       scanf("%f", &d->habilidades.genjutsu);
    printf("Estamina: ");       scanf("%f", &d->habilidades.estamina);
    printf("Inteligência: ");   scanf("%f", &d->habilidades.inteligencia);
    printf("Selos: ");          scanf("%f", &d->habilidades.selos);
    getchar(); // limpa \n

    return d;
}

Ninja *criarNinja(Sistema *sistema) {
    Ninja *novo = (Ninja *)malloc(sizeof(Ninja));

    printf("\n--- Cadastro de novo ninja ---\n");

    // Validação de unicidade do código
    do {
        printf("Código do ninja (5 dígitos): ");
        scanf("%d", &novo->codigo);
        getchar();

        if (buscarNinja(sistema, novo->codigo) != NULL) {
            printf("[!] Já existe um ninja com esse código. Escolha outro.\n");
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
        printf("Ninja com código %05d não encontrado.\n", codigo);
        return;
    }

    printf("\n===== PERFIL COMPLETO DO NINJA =====\n");
    printf("Nome: %s\n", ninja->nome);
    printf("Código: %05d\n", ninja->codigo);
    printf("Patente: %s\n", patenteNomes[ninja->patente]);

    DescricaoCompleta *desc = ninja->descricao;
    printf("Vila: %s\n", desc->vila);
    printf("Cargo Especial: %s\n", desc->cargoEspecial);
    printf("Kekkei Genkai: %s\n", desc->kekkeiGenkai);
    printf("Clã: %s\n", desc->cla);
    printf("Invocação Especial: %s\n", desc->invocacao);

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
    printf("Força: %.1f\n", desc->habilidades.forca);
    printf("Taijutsu: %.1f\n", desc->habilidades.taijutsu);
    printf("Velocidade: %.1f\n", desc->habilidades.velocidade);
    printf("Genjutsu: %.1f\n", desc->habilidades.genjutsu);
    printf("Estamina: %.1f\n", desc->habilidades.estamina);
    printf("Inteligência: %.1f\n", desc->habilidades.inteligencia);
    printf("Selos: %.1f\n", desc->habilidades.selos);

    int encontrouMissao = 0;
    printf("\n>>> Missões realizadas:\n");
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
        printf("Nenhuma missão registrada.\n");
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
        printf("- %s (Código: %05d, Patente: %s)\n",
               n->ninja->nome,
               n->ninja->codigo,
               patenteNomes[n->ninja->patente]);
        n = n->prox;
    }
    printf("===================================\n");
}

Missao *criarMissao(Sistema *sistema) {
    Missao *m = (Missao *)malloc(sizeof(Missao));

    printf("\n--- Cadastro de nova missão ---\n");

    do {
        printf("Código da missão (4 dígitos): ");
        scanf("%hd", &m->codigo);

        printf("Ano/período da missão (ex: 1200): ");
        scanf("%hu", &m->ano);

        if (buscarMissao(sistema, m->codigo, m->ano) != NULL) {
            printf("[!] Já existe uma missão com esse código no ano %hu. Digite um código diferente.\n", m->ano);
        } else {
            break;
        }
    } while (1);

    getchar(); // limpar buffer

    printf("Nome da missão: ");
    m->nome = getTexto();

    printf("Rank da missão (0: D, 1: C, 2: B, 3: A, 4: S): ");
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
        printf("Ninja com código %05d não encontrado.\n", codNinja);
        return;
    }

    MissaoNode *missao = buscarMissao(sistema, codMissao, ano);
    if (missao == NULL) {
        printf("Missão com código %04d no ano %hu não encontrada.\n", codMissao, ano);
        return;
    }

    // Verifica se já está alocado
    NinjaNode *p = missao->participantes;
    while (p != NULL) {
        if (p->ninja->codigo == codNinja) {
            printf("Ninja já está alocado nessa missão.\n");
            return;
        }
        p = p->prox;
    }

    // Aloca
    NinjaNode *novo = (NinjaNode *)malloc(sizeof(NinjaNode));
    novo->ninja = ninja;
    novo->prox = missao->participantes;
    missao->participantes = novo;

    printf("Ninja %s alocado com sucesso à missão %s.\n", ninja->nome, missao->missao->nome);
}

void removerNinja(Sistema *sistema, int codigo) {
    NinjaNode *atual = sistema->ninjas;
    NinjaNode *anterior = NULL;

    while (atual != NULL && atual->ninja->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Ninja com código %d não encontrado.\n", codigo);
        return;
    }

    // Remover de possíveis missões
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
                    free(n); // remove ninja da missão
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

    // Libera a lista de períodos
    PeriodoNode *p = sistema->periodos;
    while (p != NULL) {
        PeriodoNode *auxPeriodo = p;
        p = p->prox;

        // Libera as missões dentro do período
        MissaoNode *m = auxPeriodo->missoes;
        while (m != NULL) {
            MissaoNode *auxMissao = m;
            m = m->prox;

            // Libera participantes da missão
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
        printf("Missão com código %04d no ano %hu não encontrada.\n", codigo, ano);
        return;
    }

    printf("\n===== PERFIL DA MISSÃO =====\n");
    printf("Nome: %s\n", m->missao->nome);
    printf("Código: %04d\n", m->missao->codigo);
    printf("Ano: %hu\n", m->missao->ano);
    printf("Rank: %s\n", rankNomes[m->missao->rank]);
    printf("Recompensa: %u\n", m->missao->recompensa);
    printf("Participantes:\n");

    if (m->participantes == NULL) {
        printf("- Nenhum ninja alocado.\n");
    } else {
        NinjaNode *n = m->participantes;
        while (n != NULL) {
            printf("- %s (Código: %05d, Patente: %s)\n",
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
                    // Remove todos os participantes da missão
                    NinjaNode *n = m->participantes;
                    while (n != NULL) {
                        NinjaNode *aux = n;
                        n = n->prox;
                        free(aux); // Não libera o ninja, só o nó da missão
                    }

                    if (m_ant == NULL)
                        p->missoes = m->prox;
                    else
                        m_ant->prox = m->prox;

                    free(m->missao->nome);
                    free(m->missao);
                    free(m);
                    printf("Missão removida com sucesso!\n");
                    return;
                }

                m_ant = m;
                m = m->prox;
            }

        }
        p = p->prox;
    }
    printf("Missão com código %d no ano %d não encontrada.\n", codigo, ano);
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
                        printf("Missão: %s (Código: %04d, Rank: %s, Recompensa: %u)\n",
                               m->missao->nome, m->missao->codigo, rankNomes[m->missao->rank], m->missao->recompensa);
                        encontrou = 1;
                        break;
                    }
                    n = n->prox;
                }
                m = m->prox;
            }

            if (!encontrou)
                printf("Este ninja não participou de nenhuma missão no ano %hu.\n", ano);
            return;
        }
        p = p->prox;
    }

    printf("Não há missões registradas no ano %hu.\n", ano);
}

void consultarNinjasDaMissao(Sistema *sistema, short int codigoMissao, short unsigned int ano) {
    PeriodoNode *p = sistema->periodos;

    while (p != NULL) {
        if (p->ano == ano) {
            MissaoNode *m = p->missoes;

            while (m != NULL) {
                if (m->missao->codigo == codigoMissao) {
                    if (m->participantes == NULL) {
                        printf("Nenhum ninja registrado nesta missão.\n");
                        return;
                    }

                    printf("Ninjas na missão %s (código %04d):\n", m->missao->nome, codigoMissao);
                    NinjaNode *n = m->participantes;
                    while (n != NULL) {
                        printf("- %s (código: %05d, patente: %s)\n",
                               n->ninja->nome, n->ninja->codigo, patenteNomes[n->ninja->patente]);
                        n = n->prox;
                    }
                    return;
                }
                m = m->prox;
            }

            printf("Missão com código %d não encontrada no ano %hu.\n", codigoMissao, ano);
            return;
        }
        p = p->prox;
    }

    printf("Não há missões registradas no ano %hu.\n", ano);
}

void listarTodasMissoes(Sistema *s) {
    if (s->periodos == NULL) {
        printf("Nenhuma missão cadastrada no sistema.\n");
        return;
    }

    printf("\n===== LISTA DE TODAS AS MISSÕES =====\n");
    PeriodoNode *p = s->periodos;
    while (p != NULL) {
        printf("\n--- Período: %hu ---\n", p->ano);
        MissaoNode *m = p->missoes;
        if (!m) printf("(Nenhuma missão neste período)\n");
        while (m != NULL) {
            Missao *ms = m->missao;
            printf("- Código: %04d | Nome: %s | Rank: %s | Recompensa: %u\n",
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
            printf("\n===== MISSÕES DO ANO %hu =====\n", ano);
            MissaoNode *m = p->missoes;
            if (!m) {
                printf("Nenhuma missão cadastrada neste ano.\n");
            } else {
                while (m != NULL) {
                    Missao *ms = m->missao;
                    printf("- Código: %04d | Nome: %s | Rank: %s | Recompensa: %u\n",
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
    printf("Nenhum período encontrado com o ano %hu.\n", ano);
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

    // salvar períodos e missões
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
        printf("3. Cadastrar nova missão\n");
        printf("4. Remover missão\n");
        printf("5. Consultar missões de um ninja em um período\n");
        printf("6. Consultar ninjas de uma missão em um período\n");
        printf("7. Alocar ninja a uma missão\n");
        printf("8. Exibir perfil de um ninja\n");
        printf("9. Exibir perfil de uma missão\n");
        printf("10. Listar todos os ninjas cadastrados\n");
        printf("11. Listar todas as missões cadastradas\n");
        printf("12. Listar missões de um ano específico\n");
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
                printf("Código do ninja a ser removido: ");
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
                printf("Código da missão: ");
                scanf("%hd", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                removerMissao(s, cod, ano);
                break;
            }
            case 5: {
                int cod;
                short unsigned int ano;
                printf("Código do ninja: ");
                scanf("%d", &cod);
                printf("Ano: ");
                scanf("%hu", &ano);
                consultarMissoesDoNinja(s, cod, ano);
                break;
            }
            case 6: {
                short int cod;
                short unsigned int ano;
                printf("Código da missão: ");
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
                printf("Código do ninja: ");
                scanf("%d", &codNinja);
                printf("Código da missão: ");
                scanf("%hd", &codMissao);
                printf("Ano: ");
                scanf("%hu", &ano);
                alocarNinjaEmMissao(s, codNinja, codMissao, ano);
                break;
            }
            case 8: {
                int cod;
                printf("Código do ninja: ");
                scanf("%d", &cod);
                exibirPerfilNinja(s, cod);
                break;
            }
            case 9: {
                short int cod;
                short unsigned int ano;
                printf("Código da missão: ");
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
                printf("Opção inválida!\n");
        }

    } while(op != 0);
}
