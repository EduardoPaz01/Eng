// CODE BY EDUARDO PAZ //

#include <stdio.h>

int main(){
	int x1[4]={0,0,1,1};//entradas possiveis de x1
	int x2[4]={0,1,0,1};//entradas possiveis de x2

	int  y[4]={0,0,0,1};//resposta absoluta AND

	float w1 = 5.6, w2 = 2.1;//pesos das entradas escolhidos aleatoriamente
	float bias = -0.5;//precipita o treinamento de acordo com o tamanho do erro
	
	
    float tx = 0.06; //coeficiente de inteligencia
    
    float threshold = 0;//valor para executar a funcao de ativacao
    
    float v;//funcao hipotese para a regressao linear; Campo induzido
    
    int a;//resposta encontrada pelo perceptron para comparar com y[i]
    
    float erro;//usado para reajustar os pesos W
    
    int iteracao = 0;//conta a quantidade de vezes que foi feito o loop de treinamento
    int i = 0;//indice do vetor
    int certo;//certo varia de 0 a 4, acertando 4 em uma unica repeticao, terminao treinamento
    
  
    do{
        if(i % 4 == 0){
            i = 0;
            certo = 0;
        }
        v = x1[i] * w1 + x2[i] * w2 + bias;//Juncao aditiva, calculo do campo induzido
        
        //Funcao de ativacao, por degrau bipolar
        if(v > threshold)
            a = 1;
        else
            a = 0;
            
        erro = tx * (y[i] - a);
        
        w1 = w1 + erro * x1[i];
        w2 = w2 + erro * x2[i];
        bias = bias + erro;
        
        printf("bias = %.2f w1 = %.2f w2 = %.2f\n", bias, w1,w2);
        
        if(a == y[i]){
            printf("Acertou y[%d]\n", i);
            certo++;
        }
        else printf("Errou y[%d]\n", i);
            
        i++;
        iteracao++;
    }while(certo < 4);
    
    printf("Algoritmo treinado com %d iteracoes\n", iteracao);
    
    //acima treinamento finalizado
    ///////////////////////////////////////////////////////////////////////////
    //abaixo o algoritmo treinado para teste
    int e1, e2;//entradas do usuário
    printf("PORTA AND\n");
    printf("Digite a entrada 1: ");
    scanf("%d", &e1);
    printf("Digite a entrada 2: ");
    scanf("%d", &e2);
    
    
    int h = e1 * w1 + e2 * w2 + bias;//Juncao aditiva
    //Funcao de ativacao
    if(h > threshold)
        a = 1;
    else
        a = 0;
    printf("Saida AND: %d\n", a);
}


