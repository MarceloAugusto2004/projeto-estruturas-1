#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#define MAX_CLASSE 30
#define MAX_JOGADOR 50
#include "usuario.h"

typedef struct personagem {
    int id;
    char nome[MAX_NOME];
    char classe[MAX_CLASSE];
    int nivel;
    char jogador[MAX_JOGADOR];
    struct personagem *prox;
} Personagem;

typedef struct {
    Personagem *inicio;
} Lista;

Lista *criarLista();
void liberarLista(Lista *lista);
void carregarPersonagens(Lista *lista);
void salvarPersonagens(Lista *lista);
void cadastrarPersonagem(Lista *lista);
void listarPersonagens(Lista *lista);
void editarPersonagem(Lista *lista);
void excluirPersonagem(Lista *lista);
void buscarPorClasse(Lista *lista);
void listarPorNivel(Lista *lista);
void contarPersonagens(Lista *lista);
void verPorJogador(Lista *lista);

#endif