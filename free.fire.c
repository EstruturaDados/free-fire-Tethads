#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10
#define MAX_COMPONENTES 20
#define MAX_NOME 50
#define MAX_TIPO 20

// ----------------------- Estruturas -----------------------
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int prioridade;
} Componente;

// ----------------------- Protótipos de funções -----------------------
// Vetor
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nomeBusca[]);
void ordenarVetor(Item mochila[], int qtd);

// Lista encadeada
void inserirItemLista(No** inicio);
void removerItemLista(No** inicio);
void listarItensLista(No* inicio);
int buscarSequencialLista(No* inicio, char nomeBusca[]);

// Ordenação de componentes
void bubbleSortNome(Componente comp[], int qtd, int* comparacoes);
void insertionSortTipo(Componente comp[], int qtd, int* comparacoes);
void selectionSortPrioridade(Componente comp[], int qtd, int* comparacoes);
int buscaBinariaNome(Componente comp[], int qtd, char nomeBusca[], int* comparacoes);

// Função utilitária
void mostrarComponentes(Componente comp[], int qtd);

// ----------------------- Implementação -----------------------

// --------- Vetor ---------
void inserirItemVetor(Item mochila[], int *qtd){
    if(*qtd >= MAX_ITENS){
        printf("Mochila cheia!\n");
        return;
    }
    printf("Nome do item: ");
    scanf(" %29[^\n]", mochila[*qtd].nome);
    printf("Tipo do item: ");
    scanf(" %19s", mochila[*qtd].tipo);
    printf("Quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    (*qtd)++;
}
void removerItemVetor(Item mochila[], int *qtd){
    char nomeBusca[MAX_NOME];
    printf("Informe o nome do item a remover: ");
    scanf(" %29[^\n]", nomeBusca);
    int encontrado = 0;
    for(int i=0;i<*qtd;i++){
        if(strcmp(mochila[i].nome, nomeBusca)==0){
            encontrado = 1;
            for(int j=i;j<*qtd-1;j++){
                mochila[j]=mochila[j+1];
            }
            (*qtd)--;
            printf("Item removido.\n");
            break;
        }
    }
    if(!encontrado) printf("Item nao encontrado.\n");
}

void listarItensVetor(Item mochila[], int qtd){
    printf("---- Itens na mochila (Vetor) ----\n");
    for(int i=0;i<qtd;i++){
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
                i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nomeBusca[]){
    int comparacoes = 0;
    for(int i=0;i<qtd;i++){
        comparacoes++;
        if(strcmp(mochila[i].nome,nomeBusca)==0){
            printf("Item encontrado apos %d comparacoes: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   comparacoes, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return i;
        }
    }
    printf("Item nao encontrado apos %d comparacoes.\n", comparacoes);
    return -1;
}

void ordenarVetor(Item mochila[], int qtd){
    // Bubble sort por nome
    int comparacoes=0;
    for(int i=0;i<qtd-1;i++){
        for(int j=0;j<qtd-i-1;j++){
            comparacoes++;
            if(strcmp(mochila[j].nome, mochila[j+1].nome)>0){
                Item temp=mochila[j];
                mochila[j]=mochila[j+1];
                mochila[j+1]=temp;
            }
        }
    }
    printf("Itens ordenados por nome. Comparacoes: %d\n", comparacoes);
}

// --------- Lista Encadeada ---------
void inserirItemLista(No** inicio){
    No* novo = (No*) malloc(sizeof(No));
    if(!novo){ printf("Erro de alocacao.\n"); return; }
    printf("Nome do item: ");
    scanf(" %29[^\n]", novo->dados.nome);
    printf("Tipo do item: ");
    scanf(" %19s", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    novo->proximo = *inicio;
    *inicio=novo;
}

void removerItemLista(No** inicio){
    char nomeBusca[MAX_NOME];
    printf("Informe o nome do item a remover: ");
    scanf(" %29[^\n]", nomeBusca);
    No* atual = *inicio;
    No* anterior = NULL;
    while(atual){
        if(strcmp(atual->dados.nome, nomeBusca)==0){
            if(anterior) anterior->proximo=atual->proximo;
            else *inicio=atual->proximo;
            free(atual);
            printf("Item removido.\n");
            return;
        }
        anterior=atual;
        atual=atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

void listarItensLista(No* inicio){
    printf("---- Itens na mochila (Lista Encadeada) ----\n");
    No* atual = inicio;
    int i=1;
    while(atual){
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual=atual->proximo;
        i++;
    }
}
    No* buscarSequencialLista(No* inicio, char nomeBusca[]){ // Tipo de retorno ajustado
    int comparacoes=0;
    No* atual=inicio;
    while(atual){
        comparacoes++;
        if(strcmp(atual->dados.nome,nomeBusca)==0){
            printf("Item encontrado apos %d comparacoes: Nome: %s | Tipo: %s | Quantidade: %d\n",
                   comparacoes, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            return atual; // Retorna o ponteiro para o nó
        }
        atual=atual->proximo;
    }
    printf("Item nao encontrado apos %d comparacoes.\n", comparacoes);
    return NULL; // Retorna NULL se não encontrar
}
// --------- Ordenação de Componentes da Torre ---------
void bubbleSortNome(Componente comp[], int qtd, int* comparacoes){
    for(int i=0;i<qtd-1;i++){
        for(int j=0;j<qtd-i-1;j++){
            (*comparacoes)++;
            if(strcmp(comp[j].nome, comp[j+1].nome)>0){
                Componente temp = comp[j];
                comp[j]=comp[j+1];
                comp[j+1]=temp;
            }
        }
    }
}

void insertionSortTipo(Componente comp[], int qtd, int* comparacoes){
    for(int i=1;i<qtd;i++){
        Componente chave = comp[i];
        int j=i-1;
        while(j>=0 && (strcmp(comp[j].tipo,chave.tipo)>0)){
            (*comparacoes)++;
            comp[j+1]=comp[j];
            j--;
        }
        comp[j+1]=chave;
    }
}

void selectionSortPrioridade(Componente comp[], int qtd, int* comparacoes){
    for(int i=0;i<qtd-1;i++){
        int min=i;
        for(int j=i+1;j<qtd;j++){
            (*comparacoes)++;
            if(comp[j].prioridade < comp[min].prioridade) min=j;
        }
        if(min!=i){
            Componente temp=comp[i];
            comp[i]=comp[min];
            comp[min]=temp;
        }
    }
}

int buscaBinariaNome(Componente comp[], int qtd, char nomeBusca[], int* comparacoes){
    int esq=0, dir=qtd-1;
    while(esq<=dir){
        (*comparacoes)++;
        int meio=(esq+dir)/2;
        int cmp=strcmp(comp[meio].nome,nomeBusca);
        if(cmp==0) return meio;
        else if(cmp<0) esq=meio+1;
        else dir=meio-1;
    }
    return -1;
}

void mostrarComponentes(Componente comp[], int qtd){
    printf("---- Componentes da Torre ----\n");
    for(int i=0;i<qtd;i++){
        printf("%d. Nome: %s | Tipo: %s | Prioridade: %d\n",
               i+1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// ----------------------- Função Principal -----------------------
// ...
int main(){
    srand(time(NULL));
    int escolha;
    Item mochilaVetor[MAX_ITENS];
    int qtdVetor=0;
    No* mochilaLista=NULL;

    do{
        printf("\n--- MENU ---\n");
        printf("1. Inserir item (Vetor)\n"item (Vetor)\n");
        printf("2. Remover item (Vetor)\n"item (Vetor)\n");
        printf("3. Listar itens (Vetor)\n"itens (Vetor)\n");
        printf("4. Buscar item (Vetor)\n"item (Vetor)\n");
        printf("5. Ordenar itens (Vetor)\n"itens (Vetor)\n");
        printf("6. Inserir item (Lista)\n"item (Lista)\n");
        printf("7. Remover item (Lista)\n"item (Lista)\n");
        printf("8. Listar itens (Lista)\n"itens (Lista)\n");
        printf("9. Buscar item (Lista)\n"item (Lista)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1: inserirItemVetor(mochilaVetor, &qtdVetor); break;
            case 2: removerItemVetor(mochilaVetor, &qtdVetor); break;
            case 3: listarItensVetor(mochilaVetor, qtdVetor); break;
            case 4: {
                char nomeBusca[MAX_NOME];
                printf("Nome do item a buscar: ");
                scanf(" %29[^\n]", nomeBusca);
                int indice = buscarSequencialVetor(mochilaVetor, qtdVetor, nomeBusca);
                if(indice != -1){
                    printf("Item encontrado: %s\n", mochilaVetor[indice].nome);
                }
                break;
            }
            case 5: ordenarVetor(mochilaVetor, qtdVetor); break;
            case 6: inserirItemLista(&mochilaLista); break;
            case 7: removerItemLista(&mochilaLista); break;
            case 8: listarItensLista(mochilaLista); break;
            case 9: {
                char nomeBusca[MAX_NOME];
                printf("Nome do item a buscar: ");
                scanf(" %29[^\n]", nomeBusca);
                No* item = buscarSequencialLista(mochilaLista, nomeBusca);
                if(item != NULL){
                    printf("Item encontrado: %s\n", item->dados.nome);
                }
                break;
            }
            case 0: break;
            default: printf("Opcao invalida!\n"); break;
        }
    } while(escolha!=0);

    // Liberar memória da lista encadeada
    No* atual = mochilaLista;
    while(atual){
        No* temp = atual;
        atual=atual->proximo;
        free(temp);
    }

    printf("Programa encerrado.\n");
    return 0;
}