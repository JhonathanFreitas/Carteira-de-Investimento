#include <iostream>
#include <cstring>
using namespace std;

struct Ativo {
    char ticket[7];
    int quantidade;
    double precoMedio;
};

//Registrar Compra
void registrarCompra(Ativo acoes[], int &numAcoes) {
    char ticket[7];
    int quantidade;
    double valor;

    cout << "Digite o ticket de empresa (ex: ITSA4): ";
    cin >> ticket;
    cout << "Digite a quantidade comprada: ";
    cin >> quantidade;
    cout << "Digite o valor do ativo no momento da compra: ";
    cin >> valor;

    int posicao = -1;
    for(int i = 0; i < numAcoes; i++) {
        if (strcmp(acoes[i].ticket, ticket) == 0) {
            posicao = i;
            break;
        }
    }

    if(posicao == -1) {
        posicao = numAcoes;
        strcpy(acoes[numAcoes].ticket, ticket);
        acoes[numAcoes]. quantidade = 0;
        acoes[numAcoes].precoMedio = 0.0;
        numAcoes++;
    }

    Ativo &acao = acoes[posicao];
    acao.precoMedio = ((acao.precoMedio * acao.quantidade) + (valor * quantidade)) / (acao.quantidade + quantidade);
    acao.quantidade += quantidade;
}

//Registrar Venda
void registrarVenda(Ativo acoes[], int numAcoes) {
    char ticket[7];
    int quantidade;
    double valor;

    cout << "Digite o ticket da empresa (ex: ITSA4): ";
    cin >> ticket;
    cout << "Digite a quantidade vendida: ";
    cin >> quantidade;

    int posicao = -1;
    for (int i = 0; i < numAcoes; i++) {
        if (strcmp(acoes[i].ticket, ticket) == 0) {
            posicao = i;
            break;
        }
    }

    if (posicao == -1) {
        cout << "Ativo não encontrado!" << endl;
        return;
    }

    Ativo &acao = acoes[posicao];
    if (acao.quantidade < quantidade) {
        cout << "Saldo insuficiente para venda!" << endl;
        return;
    }

    acao.quantidade -= quantidade;
}

//Buaca Binária
int buscaBinaria(Ativo acoes[], int inicio, int fim, const char *ticket) {
    if (inicio > fim) return -1;

    int meio = (inicio + fim) / 2;
    int comparacao = strcmp(acoes[meio].ticket, ticket);

    if (comparacao == 0) return meio;
    if (comparacao > 0) return buscaBinaria(acoes, inicio, meio - 1, ticket);
    return buscaBinaria(acoes, meio + 1, fim, ticket);
}

//Ver Saldo
void verSaldoAtivo(Ativo acoes[], int numAcoes) {
    char ticket[7];
    cout << "Digite o ticket da empresa (ex: ITSA4): ";
    cin >> ticket;

    int posicao = buscaBinaria(acoes, 0, numAcoes - 1, ticket);
    if (posicao == -1) {
        cout << "Ativo não encontrado!" << endl;
        return;
    }

    Ativo &acao = acoes[posicao];
    cout << "Ticket: " << acao.ticket << ", Quantidade: " << acao.quantidade << ", Preco Medio: " << acao.precoMedio << endl;
}

//Listar Patrimônio
void listarPatrimonio(Ativo acoes[], int numAcoes) {
    for (int i = 0; i < numAcoes; i++) {
        cout << "Ticket: " << acoes[i].ticket << ", Quantidade: " << acoes[i].quantidade << ", Preco Medio: " << acoes[i].precoMedio << endl;
    }
}

//Menu
int main() {
    const int maxAcoes = 100;
    Ativo acoes[maxAcoes];
    int numAcoes = 0;

    int opcao;
    do {
        cout <<"\nMenu:\n";
        cout <<"1- Registrar compra\n";
        cout <<"2- Registrar venda\n";
        cout <<"3- Ver Saldo(Busca por Ticket)\n";
        cout <<"4- Listar Patrimonio\n";
        cout <<"5- Sair\n";
        cout <<"Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCompra(acoes, numAcoes);
                break;
            case 2:
                registrarVenda(acoes, numAcoes);
                break;
            case 3:
                verSaldoAtivo(acoes, numAcoes);
                break;
            case 4:
                listarPatrimonio(acoes, numAcoes);
                break;
            case 5:
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
                break;
        }
    }while (opcao != 5);

    return 0;
}