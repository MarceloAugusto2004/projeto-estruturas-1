#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "personagem.h"

Lista *criarLista() {
    Lista *lista = malloc(sizeof(Lista));
    if (lista) lista->inicio = NULL;
    return lista;
}

void liberarLista(Lista *lista) {
    Personagem *p = lista->inicio;
    while (p) {
        Personagem *prox = p->prox;
        free(p);
        p = prox;
    }
    free(lista);
}

void carregarPersonagens(Lista *lista) {
    FILE *arquivo = fopen("personagens.dat", "rb");
    if (!arquivo) return;

    Personagem temp;
    while (fread(&temp, sizeof(Personagem), 1, arquivo)) {
        Personagem *novo = malloc(sizeof(Personagem));
        *novo = temp;
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }

    fclose(arquivo);
}

void salvarPersonagens(Lista *lista) {
    FILE *arquivo = fopen("personagens.dat", "wb");
    if (!arquivo) return;

    Personagem *p = lista->inicio;
    while (p) {
        fwrite(p, sizeof(Personagem), 1, arquivo);
        p = p->prox;
    }

    fclose(arquivo);
}

void cadastrarPersonagem(Lista *lista) {
    Personagem *novo = malloc(sizeof(Personagem));
    if (!novo) return;

    printf("Nome: ");
    fgets(novo->nome, MAX_NOME, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Classe: ");
    fgets(novo->classe, MAX_CLASSE, stdin);
    novo->classe[strcspn(novo->classe, "\n")] = '\0';

    printf("Nível: ");
    scanf("%d", &novo->nivel); getchar();

    printf("Nome do jogador: ");
    fgets(novo->jogador, MAX_JOGADOR, stdin);
    novo->jogador[strcspn(novo->jogador, "\n")] = '\0';

    // Atribuir um ID (incremental simples)
    static int id_atual = 1;
    novo->id = id_atual++;

    novo->prox = lista->inicio;
    lista->inicio = novo;

    printf("Personagem cadastrado com sucesso!\n");
}

void listarPersonagens(Lista *lista) {
    Personagem *p = lista->inicio;
    if (!p) {
        printf("Nenhum personagem cadastrado.\n");
        return;
    }

    while (p) {
        printf("\nID: %d\nNome: %s\nClasse: %s\nNível: %d\nJogador: %s\n",
               p->id, p->nome, p->classe, p->nivel, p->jogador);
        p = p->prox;
    }
}

void editarPersonagem(Lista *lista) {
    int id;
    printf("ID do personagem a editar: ");
    scanf("%d", &id); getchar();

    Personagem *p = lista->inicio;
    while (p) {
        if (p->id == id) {
            printf("Novo nome: ");
            fgets(p->nome, MAX_NOME, stdin);
            p->nome[strcspn(p->nome, "\n")] = '\0';

            printf("Nova classe: ");
            fgets(p->classe, MAX_CLASSE, stdin);
            p->classe[strcspn(p->classe, "\n")] = '\0';

            printf("Novo nível: ");
            scanf("%d", &p->nivel); getchar();

            printf("Novo jogador: ");
            fgets(p->jogador, MAX_JOGADOR, stdin);
            p->jogador[strcspn(p->jogador, "\n")] = '\0';

            printf("Personagem atualizado!\n");
            return;
        }
        p = p->prox;
    }

    printf("Personagem não encontrado.\n");
}

void excluirPersonagem(Lista *lista) {
    int id;
    printf("ID do personagem a excluir: ");
    scanf("%d", &id); getchar();

    Personagem *p = lista->inicio;
    Personagem *anterior = NULL;

    while (p) {
        if (p->id == id) {
            if (anterior) anterior->prox = p->prox;
            else lista->inicio = p->prox;
            free(p);
            printf("Personagem excluído.\n");
            return;
        }
        anterior = p;
        p = p->prox;
    }

    printf("Personagem não encontrado.\n");
}

void buscarPorClasse(Lista *lista) {
    char classeBusca[MAX_CLASSE];
    printf("Classe a buscar: ");
    fgets(classeBusca, MAX_CLASSE, stdin);
    classeBusca[strcspn(classeBusca, "\n")] = '\0';

    int encontrados = 0;
    Personagem *p = lista->inicio;
    while (p) {
        if (strcmp(p->classe, classeBusca) == 0) {
            printf("Nome: %s, Nível: %d, Jogador: %s\n", p->nome, p->nivel, p->jogador);
            encontrados++;
        }
        p = p->prox;
    }

    if (!encontrados)
        printf("Nenhum personagem encontrado com essa classe.\n");
}

void listarPorNivel(Lista *lista) {
    int nivel;
    printf("Digite o nível: ");
    scanf("%d", &nivel); getchar();

    int encontrados = 0;
    Personagem *p = lista->inicio;
    while (p) {
        if (p->nivel == nivel) {
            printf("Nome: %s, Classe: %s, Jogador: %s\n", p->nome, p->classe, p->jogador);
            encontrados++;
        }
        p = p->prox;
    }

    if (!encontrados)
        printf("Nenhum personagem encontrado com esse nível.\n");
}

void contarPersonagens(Lista *lista) {
    int count = 0;
    Personagem *p = lista->inicio;
    while (p) {
        count++;
        p = p->prox;
    }

    printf("Total de personagens: %d\n", count);
}

void verPorJogador(Lista *lista) {
    char jogadorBusca[MAX_JOGADOR];
    printf("Nome do jogador: ");
    fgets(jogadorBusca, MAX_JOGADOR, stdin);
    jogadorBusca[strcspn(jogadorBusca, "\n")] = '\0';

    int encontrados = 0;
    Personagem *p = lista->inicio;
    while (p) {
        if (strcmp(p->jogador, jogadorBusca) == 0) {
            printf("Nome: %s, Classe: %s, Nível: %d\n", p->nome, p->classe, p->nivel);
            encontrados++;
        }
        p = p->prox;
    }

    if (!encontrados)
        printf("Nenhum personagem encontrado para esse jogador.\n");
}
