#include <iostream>
#include "Pilha.hpp"
#include "Pilha.cpp"

#include <fstream>

using namespace std;

// Imprime o menu principal
void menu()
{
    cout << "1 - Inclusao de um novo pedido\n";
    cout << "2 - Lista Pedidos\n";
    cout << "3 - Ver Cardapio\n";
    cout << "4 - Consultar Pedido\n";
    cout << "5 - Imprimir Lista de Entrega\n";
    cout << "6 - Lancar entrega\n";
    cout << "7 - Sair e Salvar\n";
}

// Imprime o cardapio
void cardapio()
{
    cout << "---------------------------\n";
    cout << "|         Cardapio        |\n";
    cout << "---------------------------\n";
    cout << "| 1 - Pastel de Carne     |\n";
    cout << "| 2 - Coxinha             |\n";
    cout << "| 3 - Batata Frita        |\n";
    cout << "| 4 - Quibe               |\n";

    cout << "| 5 - Sanduiche de Queijo |\n";
    cout << "| 6 - Sanduiche Vegano    |\n";
    cout << "| 7 - Hot-Dog             |\n";

    cout << "| 8 - Suco Natural        |\n";
    cout << "| 9 - Suco de Polpa       |\n";
    cout << "| 10 - Refrigerante       |\n";

    cout << "| 11 - Trufas Recheiadas  |\n";
    cout << "| 12 - Pedaco de Bolo     |\n";
    cout << "| 13 - Pudin              |\n";
    cout << "| 14 - Torta de Limao     |\n";

    cout << "| 0 - Sair                |\n";
    cout << "---------------------------\n";
}

// Retorna o preco do produto
float tabelaPrecos(int opcaoCardapio)
{
    switch (opcaoCardapio)
    {
    case 1:
        return 5;
        break;

    case 2:
        return 3.5;
        break;

    case 3:
        return 9;
        break;

    case 4:
        return 4.5;
        break;

    case 5:
        return 5.5;
        break;

    case 6:
        return 7;
        break;

    case 7:
        return 6;
        break;

    case 8:
        return 2;
        break;

    case 9:
        return 2.5;
        break;

    case 10:
        return 3;
        break;

    case 11:
        return 2.5;
        break;

    case 12:
        return 5;
        break;

    case 13:
        return 3.5;
        break;

    case 14:
        return 4.5;
        break;
    }
    return 0;
}

int main()
{
    PilhaPedidos mochila; // Pilha principal
    FazPilhaVazia(&mochila);

    Pedido pedido; // Utilizado para guardar informacoes de pedidos

    int codigoPedido = 0; // Controle automatico de IDs
    int codigo; // Codigo para consultas
    int opcao; // Usado no Switch-Case
    int tamanhoLista; // Recebe o tamanho das pilhas
    int opcaoCardapio; // Usado para guardar as escolhas no cardapio

    float maiorDistancia; // Usado para guardar a maior distancia encontrada no case 5

    // Recupera a pilha do arquivo
    FILE* file = fopen("lanchonete.bin", "r");
    if(file != NULL) {

        while(fread(&pedido, sizeof(Pedido), 1, file)) {

            // Atualiza o id disponivel para o maior encontrado no arquivo
            if(pedido.codigo > codigoPedido) {
                codigoPedido = pedido.codigo;
            }
            // Guarda o pedido na pilha
            EmpilhaPedidos(&mochila, pedido);
        }
    }
    codigoPedido++; // Muda o id disponivel para 1 acima do maior encontrado no arquivo

    do
    {
        menu();
        cout << "Escolha uma opcao: ";
        cin >> opcao;
        system("cls");

        switch (opcao)
        {
        // Registrar pedido
        case 1:
            pedido.codigo = codigoPedido;

            pedido.tamanhoProdutos = 0;
            pedido.valor_pedido = 0;

            do
            {
                cardapio();
                cout << "Escolha um produto: ";
                cin >> opcaoCardapio;

                // Guarda o id dos produtos e atualiza o valor total do pedido
                if (opcaoCardapio != 0) 
                {
                    pedido.produtos[pedido.tamanhoProdutos] = opcaoCardapio;
                    pedido.valor_pedido += tabelaPrecos(opcaoCardapio);
                    pedido.tamanhoProdutos++;
                }
                if (opcaoCardapio > 14)
                {
                    cout << "Produto Inexistente!\n";
                }

                system("cls");
            } while (opcaoCardapio != 0 && pedido.tamanhoProdutos < MAXTAM);

            cout << "Distancia da lanchonete em kilometros: ";
            cin >> pedido.distancia;

            EmpilhaPedidos(&mochila, pedido); // Empilha o pedido na pilha
            codigoPedido++; // Atualiza o id disponivel
            system("cls");
            break;

        // Exibe a pilha
        case 2:
            if(VerificaPilhaVazia(&mochila))
            {
                cout << "Lista de Pedidos vazia!\n";
            }
            else
            {   
                ExibePilha(&mochila);
                system("pause");
                system("cls");
            }
            break;

        // Exibe o cardapio
        case 3:
            cardapio();
            system("pause");
            system("cls");
            break;

        // Exibe as informações do pedido de acordo com o id
        case 4:
            cout << "Digite o codigo do pedido: ";
            cin >> codigo;
            consultarPedido(&mochila, codigo);
            system("pause");
            system("cls");
            break;

        // Organiza a pilha de acordo com a distancia da lanchone em ordem crescente
        case 5:
            if (VerificaPilhaVazia(&mochila))
            {
                cout << "Lista de Pedidos vazia!\n";
            }
            else
            {
                PilhaPedidos aux;
                FazPilhaVazia(&aux);
                tamanhoLista = mochila.topo;
                for(int i = 0; i < tamanhoLista; i++) {
                    DesempilhaPedidos(&mochila, &pedido);
                    EmpilhaPedidos(&aux, pedido);
                }
                tamanhoLista = aux.topo;
                for (int j = 0; j < tamanhoLista; j++)
                {
                    maiorDistancia = 0;
                    for (int i = 0; i < aux.topo; i++)
                    {
                        if (maiorDistancia < aux.pedido[i].distancia)
                        {
                            maiorDistancia = aux.pedido[i].distancia;
                            codigo = aux.pedido[i].codigo;
                        }
                    }
                    EmpilhaPedidos(&mochila, removePedidoPorCodigo(&aux, codigo));
                }
                cout << "Pilha Organizada!\n\n";
                ExibePilha(&mochila);
            }
            system("pause");
            system("cls");
            break;

        // Remove o primeiro pedido para entrega
        case 6:
            if (VerificaPilhaVazia(&mochila))
            {
                cout << "Molchila Vazia!\n";
            }
            else
            {
                DesempilhaPedidos(&mochila, &pedido);
                cout << "Pedido com codigo " << pedido.codigo << " foi entregue!\n";
            }
            system("pause");
            system("cls");
            break;
        }

    } while (opcao != 7);

    // Salva a pilha no arquivo
    file = fopen("lanchonete.bin", "w");
    tamanhoLista = mochila.topo;
    for(int i = 0; i < tamanhoLista; i++) {
        DesempilhaPedidos(&mochila, &pedido);
        fwrite(&pedido, sizeof(Pedido), 1, file);
    }

    return 0;
}