#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

    // para cada nó, cria um novo nó com as mesmas informações.
        no_simples *novo = (no_simples *) malloc(sizeof(no_simples));

        if (novo == NULL){
            return;
        }
        novo->percentual = x->percentual;
        strcpy(novo->estado, x->estado);
        strcpy(novo->capital, x->capital);
        novo->prox = NULL;
        if (opcao == 0 || opcao == 1){
            char antes[30]; // são variaveis auxiliares para guardar a string e ver se a string antes está antes da string depois considerando a ordem alfabetica
            char depois[30];
            if (opcao == 0){
                strcpy(antes, x->estado);
                strcpy(depois, q->primeiro->estado);
            }else{
                strcpy(antes, x->capital);
                strcpy(depois, q->primeiro->capital);
            }
            // se a lista 'q' estiver vazia, insere o novo elemento.
            if (q->tamanho == 0){
                q->primeiro = novo;
                q->ultimo = novo;
            }
            //cas não esteja vazia, testa se deve inserir na primeira posição

            
            else if(strcmp(antes, depois) < 0){ // // inverter?
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
                if (opcao == 0){
                    strcpy(antes, y->prox->capital);
                    strcpy(depois, novo->capital);
                }else{
                    strcpy(antes, y->prox->capital);
                    strcpy(depois, novo->capital);
                }
                while(y->prox!=NULL && (strcmp(antes, depois) < 0)){ // inverter?
                    y = y->prox;
                }
                // depois que terminar de iterar, insere no novo nó atualizando os ponteiros
                novo->prox = y->prox;   
                y->prox = novo;         
            }
            // se novo nó é o último, atualiza o ponteiro:
            if (novo->prox == NULL){
                q->ultimo = novo;
            }
            q->tamanho++;
        }else{
            // nesse caso a opcao é 2 então é pra ordenador por percentual
            // alberto
        }
        
    }

}


int main(){
    lista lst = {0, NULL, NULL}; // lista com os nossos dados
    FILE *arquivo;
    arquivo = fopen("perc_cat.csv", "r");
    
    char campo[30];
    // cada pokemon tem 17 coisas
    int contador_campo = 0; // controla em qual campo a gente está, 0 = estado, 1 = capital, 2 = percentual
    while (fscanf(arquivo, "%[^,\n]%*c", campo)!=EOF){
        no_simples ls = {"", "", 0, NULL};
        if (contador_campo == 0){
            strcpy(ls.estado, campo);
        } else if (contador_campo == 1){
            strcpy(ls.capital, campo);
        } else{
            ls.percentual = atof(campo);
        }
        contador_campo++;
        contador_campo = contador_campo % 3; // ele fica rodando, quando for 3 ele volta para o 0
        adiciona_elemento(ls.percentual, ls.estado, ls.capital, &lst);
        
    }
    fclose(arquivo);


    return 1;
}
