#include <iostream>
#include "Pilha.hpp"

using namespace std;

void FazPilhaVazia(PilhaPedidos *pilhaPedidos) {
   pilhaPedidos->topo = 0;
}

bool VerificaPilhaVazia(PilhaPedidos *pilhaPedidos) {
    if (pilhaPedidos->topo == 0)
        return true;
    return false;
}

bool VerificaPilhaCheia(PilhaPedidos *pilhaPedidos) {
    if (pilhaPedidos->topo == MAXTAM)
        return true;
    return false;
}

void EmpilhaPedidos(PilhaPedidos *pilhaPedidos, Pedido pedido) {
    if (VerificaPilhaCheia(pilhaPedidos)) {
        cout << "\nPilha cheia\n";
        return;
    } 
    
    pilhaPedidos->pedido[pilhaPedidos->topo] = pedido;
    pilhaPedidos->topo++;
    //cout << "\nItem empilhado com sucesso!\n";
}

void ExibePilha(PilhaPedidos *pilhaPedidos) { 
    for (int i=pilhaPedidos->topo-1; i>=0; i--) {
        cout << "Codigo: " << pilhaPedidos->pedido[i].codigo << "\n";
            cout << "Distancia: " << pilhaPedidos->pedido[i].distancia << "\n";
            cout << "Valor Total: " << pilhaPedidos->pedido[i].valor_pedido << "\n";
            cout << "Codigos Produtos: ";
            for(int j = 0; j < pilhaPedidos->pedido[i].tamanhoProdutos; j++) {
                cout << pilhaPedidos->pedido[i].produtos[j] << " ";
            }
            cout << "\n--------------------------------\n";
    }
}



void consultarPedido(PilhaPedidos *pilhaPedidos, int codigo) {
    for(int i = 0; i < pilhaPedidos->topo; i++) {
        if(pilhaPedidos->pedido[i].codigo == codigo) {
            cout << "Codigo: " << pilhaPedidos->pedido[i].codigo << "\n";
            cout << "Distancia: " << pilhaPedidos->pedido[i].distancia << "\n";
            cout << "Valor Total: " << pilhaPedidos->pedido[i].valor_pedido << "\n";
            cout << "Codigos Produtos: ";
            for(int j = 0; j < pilhaPedidos->pedido[i].tamanhoProdutos; j++) {
                cout << pilhaPedidos->pedido[i].produtos[j] << " ";
            }
            cout << "\n";
            return;
        }
    }
}

Pedido removePedidoPorCodigo(PilhaPedidos *pilhaPedidos, int codigo) {
    for(int i = 0; i < pilhaPedidos->topo; i++) {
        if(pilhaPedidos->pedido[i].codigo == codigo) {
            Pedido retirado = pilhaPedidos->pedido[i];
            for(int j = i; j < pilhaPedidos->topo; j++) {
                pilhaPedidos->pedido[j] = pilhaPedidos->pedido[j+1];
            }
            pilhaPedidos->topo--;
            return retirado;
        }
    }
}

void DesempilhaPedidos(PilhaPedidos *pilhaPedidos, Pedido *pedido) {
    if (VerificaPilhaVazia(pilhaPedidos)) {
        cout << "\nPilha vazia.\n";
        return;
    }

    pilhaPedidos->topo--;
    *pedido = pilhaPedidos->pedido[pilhaPedidos->topo];
}

int Tamanho(PilhaPedidos *pilhaPedidos) {
    return pilhaPedidos->topo;
}