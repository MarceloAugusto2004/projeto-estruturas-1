#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "personagem.h"
#include "ordenacao.h"

void menu() {
    printf("\n=== Sistema da Guilda de Aventureiros ===\n");
    printf("1 - Cadastrar personagem\n");
    printf("2 - Listar personagens\n");
    printf("3 - Editar personagem\n");
    printf("4 - Excluir personagem\n");
    printf("5 - Buscar por classe\n");
    printf("6 - Listar por nível\n");
    printf("7 - Contar personagens\n");
    printf("8 - Ver por jogador\n");
    printf("9 - Ordenar por nome\n");
    printf("10 - Buscar personagem por nome\n");
    printf("11 - Sair\n");
    printf("Escolha: ");
}

int main() {
    Usuario user;
    char resp;
    printf("Deseja se cadastrar? (s/n): ");
    scanf(" %c", &resp); limparBuffer();
    if (resp == 's' || resp == 'S') cadastrarUsuario();
    if (!login(&user)) return 0;

    printf("\nBem-vindo, %s! Prepare seus dados, herói.\n", user.nome);

    Lista *lista = criarLista();
    carregarPersonagens(lista);

    int opcao;
    do {
        menu();
        scanf("%d", &opcao); limparBuffer();
        switch (opcao) {
            case 1: 
                cadastrarPersonagem(lista); 
            break;
            case 2: listarPersonagens(lista); break;
            case 3: editarPersonagem(lista); break;
            case 4: excluirPersonagem(lista); break;
            case 5: buscarPorClasse(lista); break;
            case 6: listarPorNivel(lista); break;
            case 7: contarPersonagens(lista); break;
            case 8: verPorJogador(lista); break;
            case 9: mergeSort(lista); salvarPersonagens(lista); printf("Ordenado!\n"); break;
            case 10: buscarPorNome(lista); break;
            case 11: salvarPersonagens(lista); printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 11);

    liberarLista(lista);
    return 0;
}