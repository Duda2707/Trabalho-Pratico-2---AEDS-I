#ifndef PILHA_H
#define PILHA_H

#define MAXTAM 10
#define MAX_ENTREGA 7

typedef struct Pedido {
    int codigo;
    int produtos[MAXTAM];
    int tamanhoProdutos;
    float valor_pedido;
    float distancia;
} Pedido;

typedef struct PilhaPedidos {
    Pedido pedido[MAX_ENTREGA];
    int topo;
} PilhaPedidos;

void FazPilhaVazia(PilhaPedidos *pilhaPedidos);
bool VerificaPilhaVazia(PilhaPedidos *pilhaPedidos);
bool VerificaPilhaCheia(PilhaPedidos *pilhaPedidos);
void EmpilhaPedidos(PilhaPedidos *pilhaPedidos, Pedido pedido);
void DesempilhaPedidos(PilhaPedidos *pilhaPedidos, Pedido *pedido);
void ExibePilha(PilhaPedidos *pilhaPedidos);
int Tamanho(PilhaPedidos *pilhaPedidos);

#endif