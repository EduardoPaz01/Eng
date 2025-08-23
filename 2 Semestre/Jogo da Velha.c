// CODE BY EDUARDO PAZ //

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

//Variáveis globais
char tabuleiro[3][3];
int contador_de_jogadas;
int indice_menu;
int bot[2];

//Prototipação das funções
void menu();
void imprime ();
void joga (contador_de_jogadas);
int verifica ();
int maquina(int turno_atual, int alpha, int beta);

int main (){
    
    //Semente de aleatoriedade
    srand(time(NULL));
    system("clear");
    //Controle do looping
    int looping = 1;
    while(looping == 1){
        
        menu();
        contador_de_jogadas = 0;
        //Inicia o tabuleiro
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                tabuleiro[i][j] = ' ';
            }
        }
        
        //Jogo singleplayer
        if(indice_menu == 1){
            
            //int vez_da_maquina = 0;
            
            for (; contador_de_jogadas < 9; contador_de_jogadas++){
                
                imprime();
                
                //Vez da máquina
                if(contador_de_jogadas%2 ==0){
                    int jogada_feita =0;
                    if(contador_de_jogadas == 0){
                        tabuleiro[1][1] = 'X';
                        jogada_feita = 1;
                    }
                    //Repete o ciclo até a melhor jogada possivel ser factível
                    if(jogada_feita==0){
                        do{
                            //Encontra a melhor jogada possivel
                            maquina(contador_de_jogadas, -2, 2);
                            int melhor_Linha = bot[0];
                            int melhor_Coluna = bot[1];
                            
                            //Realiza a mlehor jogada possivel
                            if (tabuleiro[melhor_Linha][melhor_Coluna] == ' '){
                                tabuleiro[melhor_Linha][melhor_Coluna] = 'X';
                                jogada_feita = 1;
                        }
                    }   while(jogada_feita == 0);}
                }
                //Vez do jogador
                else{
                    joga (contador_de_jogadas);
                }
                
                //Empate
                if(contador_de_jogadas == 8){
                    imprime ();
                    printf("Empatou!");
                }
                //Vitória
                if (verifica () == 1){
                    imprime ();
                    char jogador_atual;
                    jogador_atual = (contador_de_jogadas % 2 == 0) ? 'X' : 'O';
                    printf("Jogador %c GANHOU!\n", jogador_atual);
                    contador_de_jogadas = 9;
                }
            }
        }
        
        //Jogo multiplayer
        if(indice_menu == 2){
            
            //Roda o jogo
            for (; contador_de_jogadas < 9; contador_de_jogadas++){
            
                //Imprime o tabuleiro
                imprime ();
                
                //realiza a jogada
                joga (contador_de_jogadas);
                
                //Empate
                if(contador_de_jogadas == 8){
                    imprime ();
                    printf("Empatou!");
                }
                //Vitória
                if (verifica () == 1){
                    imprime ();
                    char jogador_atual;
                    jogador_atual = (contador_de_jogadas % 2 == 0) ? 'X' : 'O';
                    printf("Jogador %c GANHOU!\n", jogador_atual);
                    contador_de_jogadas = 9;
                    
                }
            }
            
        }
        
        //Instruções
        if(indice_menu == 3){
            
            system("clear");
            
            printf("\n                INSTRUCOES              \n\n");
            printf("--------------------------------------------\n\n");
            printf("Jogador X sempre será o primeiro a jogar\n");
            printf("Jogador o sempre será o segundo a jogar\n\n");
            printf("Regras para vencer: \n\n");
            printf("1. Completar uma linha com mesmo jogador \n");
            printf("1. Completar uma coluna com mesmo jogador \n");
            printf("3. Completar uma diagonal com mesmo jogador \n\n");
            printf("Tenha um bom jogo!\n\n\n");
        }
        
        //Sair
        if(indice_menu == 4)
            looping = 0;
        
            
    }

}

void menu(){
    
    
    printf("\n                  MENU              \n\n");
    printf("--------------------------------------------\n\n");
    printf(" 1. singleplayer  \n 2. multiplayer  \n");
    printf(" 3. instruções    \n 4. sair         \n\n");
    printf("->");
    
    scanf("%d", &indice_menu);
}

void imprime (){
    
    //Para limpar foi necessC!rio o clear em vez do cls
    system ("clear");
    for (int i = 0; i < 3; i++){
        printf ("+---+---+---+\n");
        for (int j = 0; j < 3; j++){
            printf ("| %c ", tabuleiro[i][j]);
        }
        printf ("|\n");
    }
    printf ("+---+---+---+\n");
}

void joga (int turno_atual){

    //Variaveis
    int linha;
    int coluna;
    char jogador_atual = ' ';
    
    //Determina quem é o jogador da vez
    jogador_atual = (turno_atual % 2 == 0) ? 'X' : 'O';
    
    //Realiza a jogada
    int jogada_feita = 0;
    do
    {
        printf ("Jogador %c: \n", jogador_atual);
        printf ("linha: ");
        scanf ("%d", &linha);
        printf ("coluna: ");
        scanf ("%d", &coluna);
        
        //Verifica se hC! essa posiC'C#o feita
        if (tabuleiro[linha][coluna] == ' '){
            tabuleiro[linha][coluna] = jogador_atual;
            jogada_feita = 1;
        }
    }while (jogada_feita == 0);

}

int verifica (){
    char jogador1 = 'X';
    char jogador2 = 'O';
    
    //Verifica se X ganhou horizontalmente
    for (int i = 0; i < 3; i++){
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2] && tabuleiro[i][2] == jogador1)
            return 1;
    }
    //Verifica se X ganhou verticalmente
    for (int i = 0; i < 3; i++){
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i] && tabuleiro[2][i] == jogador1)
            return 1;
    }
    //Verifica se X ganhou diagonalmente
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[2][2] == jogador1)
        return 1;
    if (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[2][0] == tabuleiro[0][2] && tabuleiro[0][2] == jogador1)
        return 1;

    //Verifica se O ganhou horizontalmente
    for (int i = 0; i < 3; i++){
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][0] == tabuleiro[i][2] && tabuleiro[i][2] == jogador2)
            return 1;
    }
    //Verifica se O ganhou verticalmente
    for (int i = 0; i < 3; i++){
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[0][i] == tabuleiro[2][i] && tabuleiro[2][i] == jogador2)
            return 1;
    }
    //Verifica se O ganhou diagonalmente
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[0][0] == tabuleiro[2][2] && tabuleiro[2][2] == jogador2)
        return 1;
    if (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[2][0] == tabuleiro[0][2] && tabuleiro[0][2] == jogador2)
        return 1;

    //Segue o jogo
    return 0;
}

int maquina(int turno_atual, int alpha, int beta) {
    if (turno_atual == 0) {
        // A máquina joga no centro do tabuleiro na primeira jogada
        
        return 0;
    }

    int melhorValor = -2; // Inicializa com valor baixo para maximizar
    int melhorLinha = -1;
    int melhorColuna = -1;

    // Loop através do tabuleiro para encontrar a melhor jogada
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Se a célula estiver vazia
            if (tabuleiro[i][j] == ' ') {
                tabuleiro[i][j] = 'X'; // A máquina faz uma jogada simulada
                int valorDaJogada = -maquina(turno_atual - 1, -beta, -alpha); // Chamada recursiva para o próximo nível
                tabuleiro[i][j] = ' '; // Desfaz a jogada simulada

                // Atualiza o valor da melhor jogada
                if (valorDaJogada > melhorValor) {
                    melhorValor = valorDaJogada;
                    melhorLinha = i;
                    melhorColuna = j;
                }

                // Realiza a poda Alpha-Beta
                alpha = (melhorValor > alpha) ? melhorValor : alpha;
                if (alpha >= beta) {
                    break;
                }
            }
        }
    }
    bot[0] = melhorLinha;
    bot[1] = melhorColuna;

    return melhorValor;
}



