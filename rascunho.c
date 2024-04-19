#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//CRIAR NÓ COM: ESTADO, CAPITAL E PERCENTUAL
typedef struct no_simples no_simples;
struct no_simples{
    char estado[30];
    char capital[30];
    float percentual;
    no_simples *prox;
};

//CRIAR LISTA
typedef struct lista lista;
struct lista{
    int tamanho;
    no_simples *primeiro;
    no_simples *ultimo;
};
//LER ARQUIVO "perc_cat.csv"

//ARMAZENAR AS INFORMAÇÕES NA LISTA (INSERTION_SORT)

//---------------------
//ESCOLHER ORDEM:
void switchOrdem(lista *lst, int opcao) {
    switch (opcao) {
        case 1:
            // Ordena por ordem alfabética dos estados
            insertionSortPorCodigoEstado(lst);
            break;
        case 2:
            // Ordena por ordem alfabética das capitais
            insertionSortPorCapital(lst);
            break;
        case 3:
            // Ordena por porcentagem de católicos
            insertionSortPorPorcentagemCat(lst);
            break;
        default:
            printf("Opção inválida.\n");
            break;
    }
}
//1-ALFABÉTICA POR CÓDIGO
//2-ALFABÉTICA NOME DA CAPIAL
//3-CRESCENTE DO PERCENTUAL DE CATÓLICOS


//----------------------
//USUÁRIO PODE SER CAPAZ DE:
//1- IMPRIMIR CONTEÚDO DA LISTA
//2 - LER O PERCENTUAL
//3 - MODIFIQUE O PERCENTUAL DE CATÓLICOS
int main(){
  //Fiquei um pouco perdido no código que tu mandou se tu puder colocar tudo sobre cada detalhe acho que vou entender melhor
}
