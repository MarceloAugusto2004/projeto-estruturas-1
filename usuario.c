#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usuario.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validarEmail(char email[]) {
    return strchr(email, '@') && strlen(email) < MAX_EMAIL;
}

int emailExiste(char email[]) {
    FILE *f = fopen("usuarios.txt", "r");
    if (!f) return 0;
    Usuario temp;
    while (fscanf(f, "%[^|]|%[^|]|%[^\n]\n", temp.nome, temp.senha, temp.email) != EOF) {
        if (strcmp(temp.email, email) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void cadastrarUsuario() {
    Usuario novo;
    printf("=== Cadastro de Usuário ===\n");
    printf("Nome de usuário: ");
    fgets(novo.nome, MAX_NOME, stdin); novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Senha: ");
    fgets(novo.senha, MAX_NOME, stdin); novo.senha[strcspn(novo.senha, "\n")] = 0;

    while (1) {
        printf("Email: ");
        fgets(novo.email, MAX_EMAIL, stdin); novo.email[strcspn(novo.email, "\n")] = 0;

        if (!validarEmail(novo.email)) {
            printf("Email inválido.\n");
        } else if (emailExiste(novo.email)) {
            printf("Email já cadastrado.\n");
        } else break;
    }

    FILE *f = fopen("usuarios.txt", "a");
    fprintf(f, "%s|%s|%s\n", novo.nome, novo.senha, novo.email);
    fclose(f);
}

int login(Usuario *user) {
    char nome[MAX_NOME], senha[MAX_NOME];
    printf("=== Login ===\n");
    while (1) {
        printf("Usuário: ");
        fgets(nome, MAX_NOME, stdin); nome[strcspn(nome, "\n")] = 0;
        printf("Senha: ");
        fgets(senha, MAX_NOME, stdin); senha[strcspn(senha, "\n")] = 0;

        FILE *f = fopen("usuarios.txt", "r");
        if (!f) return 0;
        Usuario temp;
        while (fscanf(f, "%[^|]|%[^|]|%[^\n]\n", temp.nome, temp.senha, temp.email) != EOF) {
            if (strcmp(nome, temp.nome) == 0 && strcmp(senha, temp.senha) == 0) {
                *user = temp;
                fclose(f);
                return 1;
            }
        }
        fclose(f);
        printf("Login inválido. Tente novamente.\n");
    }
}