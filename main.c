#include "dama.h"

int main(){
    
    int **matriz;
    int *entrada;
    int tam_entrada;
    tabuleiros *jogos;
    tipo_peca *pecas;
    entrada = malloc(sizeof(int)); 

    entrada = ler_arquivo(entrada, &tam_entrada);
    jogos = separaJogos(entrada,tam_entrada);
    
    struct timeval tv0,tv1;
    double tempo_final, tempo_inicial, time;
    gettimeofday(&tv0, NULL);
    
    for(;jogos->prox != NULL; jogos = jogos->prox){
        matriz = geraTabuleiro(jogos->linhas, jogos->colunas);
        pecas = prenche_tabuleiro(jogos->linhas, jogos->colunas, jogos->tam_estado,jogos->estado, matriz);
        melhor_jogada(matriz, jogos->linhas, jogos->colunas, pecas);
        //imprimi_jogo(matriz, jogos->linhas, jogos->colunas);
        gettimeofday(&tv1, NULL);
        tempo_final = (double)(tv1.tv_sec) + (double)(tv1.tv_usec)/ 1000000.00;
        tempo_inicial = (double)(tv0.tv_sec) + (double)(tv0.tv_usec)/ 1000000.00;
        time = (tempo_final - tempo_inicial);
        int minutos, segundos;
        minutos = time/60;
        segundos = (int) time%60; 
        printf("TEMPO : (%f)\n",time);
        printf("\n");
    }
    
    return 0;
}