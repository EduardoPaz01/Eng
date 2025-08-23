// CODE BY EDUARDO PAZ //
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Individuo{
    unsigned int fitness;
    unsigned int tamanho_rota;
    unsigned int *rota;
    bool factibilidade;
};
struct No {
    struct No *direita;
    struct No *esquerda;
    struct Individuo individuo;
    int altura;
};
struct Populacao{
    struct No *raiz;
};

int maior(int a, int b) {return (a>b)?a:b;}

struct Individuo *buscar(struct No *raiz, int fitness){
    
    struct Individuo *retorno = (struct Individuo*)malloc(sizeof(struct Individuo));
    
    if(raiz == NULL) retorno = NULL;
    else if(fitness == raiz->individuo.fitness) retorno = &raiz->individuo;
    else if(fitness  < raiz->individuo.fitness) retorno = buscar(raiz->esquerda, fitness);
    else if(fitness  > raiz->individuo.fitness) retorno = buscar(raiz->direita, fitness);
    
    return retorno;
    
}

void imprimirIndividuo(struct Individuo individuo){
    
    printf("\nFo: %d\n",individuo.fitness);
    if(individuo.factibilidade) printf("Factivel\n");
    else printf("Infactivel\n");
    for(unsigned int i = 0; i<individuo.tamanho_rota; i++) printf("%d ", individuo.rota[i]);
    printf("\n");
    
}
void imprimirPopulacao(struct No *raiz){
    
    if(raiz!=NULL){
        imprimirPopulacao(raiz->esquerda);
        imprimirIndividuo(raiz->individuo);
        imprimirPopulacao(raiz->direita);
    }
    
}
void imprimirTabela(struct No *raiz, int nivel){
    
    int i;
    if(raiz){
        imprimirTabela(raiz->direita, nivel + 1);
        printf("\n\n");
        for(i=0; i<nivel; i++) printf("\t");
        printf("%d",raiz->individuo.fitness);
        imprimirTabela(raiz->esquerda, nivel + 1);
    }
    
}

int alturaDoNo(struct No* no){
    int retorno;
    
    if(no==NULL) retorno = -1;
    else retorno = no->altura;
    
    return retorno;
}
int fatorDeBalaceamento(struct No *no){
    
    int retorno;
    
    if(no!=NULL) retorno = (alturaDoNo(no->esquerda) - alturaDoNo(no->direita));
    else retorno = 0;
    
    return retorno;
} 
struct No *RL (struct No* r){
    
    struct No *y, *f;
    
    y = r->direita;
    f = y->esquerda;
    y->esquerda = r;
    r->direita = f;
    
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita))+1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita))+1;
    
    return y;
}
struct No *RR (struct No* r){
    
    struct No *y, *f;
    
    y = r->esquerda;
    f = y->direita;
    y->direita = r;
    r->esquerda = f;
    
    r->altura = maior(alturaDoNo(r->esquerda), alturaDoNo(r->direita))+1;
    y->altura = maior(alturaDoNo(y->esquerda), alturaDoNo(y->direita))+1;
    
    return y;
}
struct No *RRL(struct No* r){
    
    struct No *retorno;
    r->direita = RR(r->direita);
    retorno = RL(r);
    
    return retorno;
    
}
struct No *RLR(struct No* r){
    
    struct No *retorno;
    r->esquerda = RL(r->esquerda);
    retorno = RR(r);
    
    return retorno;
    
}

struct Individuo *preecher_novo_Individuo(void){
    
    struct Individuo *novo_Individuo = (struct Individuo*)malloc(sizeof(struct Individuo));
    
    int factibilidade;
    printf("Valor objetivo do Individuo: \n->");
    scanf("%d", &novo_Individuo->fitness);
    
    printf("\nO individuo é factivel ? (0)não - (1)sim:\n->");
    scanf("%d", &factibilidade);
    
    novo_Individuo->factibilidade = factibilidade;
    printf("\nDefina o tamanho da rota\n->");
    scanf("%d", &novo_Individuo->tamanho_rota);
    
    novo_Individuo->rota = (unsigned int *)malloc(novo_Individuo->tamanho_rota*sizeof(unsigned int));
    for(unsigned int i = 0; i<novo_Individuo->tamanho_rota; i++ ){
        printf("Defina a posicao[%d]: ",i+1);
        scanf("%d", &novo_Individuo->rota[i]);
    }
    
    return novo_Individuo;
}
struct No *NovoNo(struct Individuo novo_Individuo){
    
    struct No *novo = (struct No*)malloc(sizeof(struct No));
    
    if(novo){
        novo->individuo = novo_Individuo;
        novo->direita = NULL;
        novo->esquerda = NULL;
        novo->altura = 0;
    }
    else printf("\nErro ao alocar nó em novoNO\n");
    
    return novo;
    
}
struct No *balancear(struct No *raiz){
    
    int fb = fatorDeBalaceamento(raiz);
    int fbDir = fatorDeBalaceamento(raiz->direita);
    int fbEsq = fatorDeBalaceamento(raiz->esquerda);
    
    if(fb<-1 && fbDir<=0) raiz = RL(raiz);
    else if(fb>1 && fbEsq>=0) raiz = RR(raiz);
    else if(fb>1 && fbEsq<0) raiz = RLR(raiz);
    else if(fb<1 && fbDir>0) raiz = RRL(raiz);
    
    return raiz;
    
}
struct No *inserir(struct No *raiz, struct Individuo novo_Individuo){
    
    struct No *retorno = (struct No*)malloc(sizeof(struct No));
    
    if(raiz==NULL) retorno = NovoNo(novo_Individuo);
    else {
        if(novo_Individuo.fitness < raiz->individuo.fitness) raiz->esquerda = inserir(raiz->esquerda, novo_Individuo);
        else if(novo_Individuo.fitness > raiz->individuo.fitness) raiz->direita = inserir(raiz->direita, novo_Individuo);
        else printf("Insercao nao realizada, elemento existe !");
        
        raiz->altura = maior(alturaDoNo(raiz->esquerda), alturaDoNo(raiz->direita)) + 1;
        raiz = balancear(raiz);
        retorno = raiz;
    }
    
    return retorno;
}

void continuar(void){
    
    int vazio;
    printf("\n\nPrecione qualquer tecla para continuar:");
    scanf("%d",&vazio);
    
}

int main(){
    
    int opcao;
    struct Populacao populacao;
    populacao.raiz = NULL;
    
    do{
        system("clear");
        printf("MENU\n----\n");
        printf("(1) Inserir Individuo\n(2) Consultar Individuo\n(3) Mostrar Populacao\n(4) Tabela\n(5) Sobre\n(6) Sair\n\n->");
        scanf("%d", &opcao);
        system("clear");
        
        switch(opcao){
            case 1:
                printf("INSERIR\n-------\n");
                struct Individuo novo_Individuo = *preecher_novo_Individuo();
                populacao.raiz = inserir(populacao.raiz, novo_Individuo);
                break;
            case 2:
                printf("BUSCAR\n------\nDigite o fitness\n->");
                unsigned int fitness;
                scanf("%d", &fitness);
                struct Individuo *individuo_buscado = buscar(populacao.raiz, fitness);
                if(individuo_buscado != NULL) imprimirIndividuo(*individuo_buscado);
                else printf("\nValor não encontrado\n\n");
                continuar();
                break;
            case 3:
                printf("ARVORE\n------\n");
                imprimirPopulacao(populacao.raiz);
                continuar();
                break;
            case 4:
                printf("ARVORE\n------\n");
                imprimirTabela(populacao.raiz, 1);
                continuar();
                break;
            case 5:
                printf("SOBRE\n-----\n");
                printf("O código é um exemplo de uma populacao de um algoritmo\n");
                printf("genético aplicado em algum problema de roteamento,  em\n");
                printf("que  não  há individuos  com  mesmo  fitness. Pode ser\n");
                printf("aplicado  na  materia  de  IA Engenharia de Controle e\n");
                printf("Automação.");
                continuar();
                break;
            case 6:
                printf("Saindo..");
                break;
            default:
                printf("\nPor favor insira um valor válido !");
                continuar();
                break;
        }
        
    }while(opcao != 6);
    
}