#ifndef USUARIO_H
#define USUARIO_H

#define MAX_EMAIL 80
#define MAX_NOME 50

typedef struct {
    char nome[MAX_NOME];
    char senha[MAX_NOME];
    char email[MAX_EMAIL];
} Usuario;

void limparBuffer();
void cadastrarUsuario();
int login(Usuario *user);

#endif