#ifndef __DAMA_H
#define __DAMA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct Peca{
	int linha, coluna;
	int max;
	int tam;
}tipo_peca;

typedef struct tabuleiros *Apontador;
typedef struct tabuleiros{
	int linhas;
	int colunas;
	int estado[100];
	int tam_estado;
	Apontador prox;
}tabuleiros;

int **cria_tabuleiro(int linhas, int colunas);
int *ler_arquivo(int *entrada, int *tam_entrada);
tabuleiros* separaJogos(int* ent, int tamanho);
void imprimi_jogo(int **tab, int linhas, int colunas);
int** geraTabuleiro(int linhas, int coluna);
tipo_peca *prenche_tabuleiro(int linha, int coluna, int tam_estado, int *estado_atual, int **matriz);
int melhor_jogada(int **matriz, int linha, int coluna, tipo_peca *pecas);
int testa_caminhos(int **jogo, int linha, int coluna, int linha_atual,int coluna_atual,int jogadas_atuais,int* maximo);
void copia_matriz(int **copia, int **matriz, int linha, int coluna);
#endif /* __DAMA_H */