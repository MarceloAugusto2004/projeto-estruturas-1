#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ordenacao.h"

// Função auxiliar para dividir a lista
void dividirLista(Personagem *origem, Personagem **frente, Personagem **tras) {
    Personagem *rapido = origem->prox;
    Personagem *lento = origem;

    while (rapido) {
        rapido = rapido->prox;
        if (rapido) {
            lento = lento->prox;
            rapido = rapido->prox;
        }
    }
    *frente = origem;
    *tras = lento->prox;
    lento->prox = NULL;
}

// Função para mesclar duas listas ordenadas
Personagem* mesclarListas(Personagem *a, Personagem *b) {
    if (!a) return b;
    if (!b) return a;
    Personagem *resultado;

    if (strcmp(a->nome, b->nome) <= 0) {
        resultado = a;
        resultado->prox = mesclarListas(a->prox, b);
    } else {
        resultado = b;
        resultado->prox = mesclarListas(a, b->prox);
    }
    return resultado;
}

// MergeSort principal
void mergeSortLista(Personagem **cabecaRef) {
    Personagem *cabeca = *cabecaRef;
    if (!cabeca || !cabeca->prox) return;

    Personagem *a, *b;
    dividirLista(cabeca, &a, &b);

    mergeSortLista(&a);
    mergeSortLista(&b);

    *cabecaRef = mesclarListas(a, b);
}

void mergeSort(Lista *lista) {
    mergeSortLista(&lista->inicio);
}

// Busca Binária (após converter lista para vetor)
void buscarPorNome(Lista *lista) {
    int tamanho = 0;
    Personagem *p = lista->inicio;
    while (p) { tamanho++; p = p->prox; }

    if (tamanho == 0) { printf("Lista vazia.\n"); return; }

    Personagem **vetor = malloc(tamanho * sizeof(Personagem*));
    p = lista->inicio;
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = p;
        p = p->prox;
    }

    char nomeBusca[MAX_NOME];
    printf("Nome do personagem: ");
    fgets(nomeBusca, MAX_NOME, stdin); nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int inicio = 0, fim = tamanho - 1, meio, encontrado = 0;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int cmp = strcmp(vetor[meio]->nome, nomeBusca);
        if (cmp == 0) {
            printf("Encontrado: %s (Classe: %s, Nível: %d, Jogador: %s)\n",
                   vetor[meio]->nome, vetor[meio]->classe, vetor[meio]->nivel, vetor[meio]->jogador);
            encontrado = 1; break;
        } else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    if (!encontrado) printf("Personagem não encontrado.\n");
    free(vetor);
}