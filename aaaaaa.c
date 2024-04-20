#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct no_simples no_simples;
struct no_simples{
    char estado[30];
    char capital[30];
    float percentual;
    no_simples *prox;
};

// lista
typedef struct lista lista;
struct lista{
    int tamanho;
    no_simples *primeiro;
    no_simples *ultimo;
};

void adiciona_elemento(float percentual, char estado[30], char capital[30], lista *p){
    no_simples *novo = (no_simples *) malloc(sizeof(no_simples));

    if (novo == NULL){
        return;
    }

    novo->percentual = percentual;
    strcpy(novo->estado, estado);
    strcpy(novo->capital, capital);
    novo->prox = NULL;
    if (p->tamanho == 0){
        p->primeiro = novo;
        p->ultimo = novo;
    }
    else{
        p->ultimo->prox = novo;
        p->ultimo = novo;
    }
    p->tamanho++;
}

// nesta função serão impressas apenas as idades por simplicidade.
// alberto
void imprime_lista(lista *p){    
    printf("Estado\t\tCapital\t\tPercentual\n");
    printf("----------------------------------------\n");
    for(no_simples *x = p->primeiro; x != NULL; x = x->prox){
        printf("%s\t\t%s\t\t%.2f\n", x->estado, x->capital, x->percentual);
    }
    printf("----------------------------------------\n");
}
// alberto
void perc_cat_por_codigo_estado(char estado[30], lista *p){
    int encontrou = 0;
    for(no_simples *atual=p->primeiro; atual != NULL; atual = atual->prox){
        if (strcmp(atual->estado, estado) == 0){
            encontrou = 1;
            printf("O percentual de católicos do estado %s é : %d", atual->estado, atual->percentual);
        }
        if(encontrou == 0){
            printf("O código digitado não corresponde a nenhum estado.\n");
        }
    }
}




void modifica_percentual(float novo_percentual, char estado[30], lista *p){
    // preciso ir percorrendo a lista até encontra o estado
    int encontrou = 0;
    for(no_simples *x=p->primeiro; x != NULL; x = x->prox){
        if (strcmp(x->estado, estado) == 0){
            encontrou = 1;
            x->percentual = novo_percentual;
        }
    }
    if (encontrou == 0){
        printf("não foi encontrado o estado\n");
    }
}
// a lista q é a lista ordenada
void insertion_sort(int opcao, lista *p, lista *q){
    // opcao = 0 -> ordena por estado
    // opcao = 1 -> ordena por capital
    // opcao = 2 -> ordena por
    // x itera sobre todos os elementos da lista p
    for(no_simples *x=p->primeiro; x != NULL; x = x->prox){
        printf("%i\n", q->tamanho);
    // para cada nó, cria um novo nó com as mesmas informações.
        no_simples *novo = (no_simples *) malloc(sizeof(no_simples));

        if (novo == NULL){
            printf("retornou");
            return;
        }
        novo->percentual = x->percentual;
        strcpy(novo->estado, x->estado);
        strcpy(novo->capital, x->capital);
        printf("%s", x->estado);
        novo->prox = NULL;
        bool condicao1;
        if (q->tamanho == 0){
            q->primeiro = novo;
            q->ultimo = novo;
            q->tamanho = 1;
            continue;
        }
        switch (opcao)
        {
        case 0:
            condicao1 = strcmp(x->estado, q->primeiro->estado) < 0;
            break;
        case 1:
            condicao1 = strcmp(x->capital, q->primeiro->capital) < 0;
            break;
        case 2: 
            condicao1 = x->percentual < q->primeiro->percentual;
            break;
        default:
            break;
        }
        // se a lista 'q' estiver vazia, insere o novo elemento.
        //cas não esteja vazia, testa se deve inserir na primeira posição
        
        if(condicao1){ // // inverter?
            novo->prox = q->primeiro;
            q->primeiro = novo;
        }
        // se não está vazia e não vai inserir na primeira posição, 
        // encontra a posição para inserir: 
        else{
            // y vai iterar sobre os elementos da lista 'q'
            no_simples *y=q->primeiro;
            // enquanto y tiver um próximo elemento, e o próximo for menor que a idade do novo nó,
            // continua iterando.
            
            bool condicao2 = y->prox!=NULL;
            while(y->prox!=NULL){
                switch (opcao){
                    case 0:
                        condicao2 = strcmp(y->prox->estado, novo->estado) < 0;
                        break;
                    case 1:
                        condicao2 = strcmp(y->prox->capital, novo->capital) < 0;
                        break;
                    case 2: 
                        condicao2 = y->prox->percentual < novo->percentual;
                        break;
                    default:
                        break;
                
                }
                if (condicao2){
                    y = y->prox;
                }else{
                    break;
                }
            }
            
            // while(condicao2){ // inverter?
            //     y = y->prox;
            // }
            // depois que terminar de iterar, insere no novo nó atualizando os ponteiros
            novo->prox = y->prox;   
            y->prox = novo;         
        }
        // se novo nó é o último, atualiza o ponteiro:
        if (novo->prox == NULL){
            q->ultimo = novo;
        }
        q->tamanho++;
        
        
    }

}


int main(){
    lista lst = {0, NULL, NULL}; // lista com os nossos dados
    lista lst_ordenada = {0, NULL, NULL};
    FILE *arq;

    // tenta abrir e avisa caso não conseguir
    arq = fopen("perc_cat.csv", "r");
    if(arq == NULL) {
        printf("nao consegui abrir\n");
        return 0;
    }

    // le primeira linha
    char lixo[100];
    fscanf(arq, "%[^\n]\n", lixo);
    printf("descartando: %s\n", lixo);
  
    // le próximas linhas
    char estado[30], capital[30];
    double perc;
    while (fscanf(arq, "%[^ ;] ;%[^;];%lf\n", estado, capital, &perc) > 0){
        adiciona_elemento(perc, estado, capital, &lst);
    }
    //printf("%i", lst.tamanho);
    //imprime_lista(&lst);
    insertion_sort(1, &lst, &lst_ordenada);
    // fecha o arquivo
    printf("%i", lst_ordenada.tamanho);
    imprime_lista(&lst_ordenada);
    fclose(arq);


    return 1;
}