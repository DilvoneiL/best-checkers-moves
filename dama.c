#include "dama.h"

int **cria_tabuleiro(int linhas, int colunas){
    /*variavel aponta pra uma variavel de memoria que guarda outro ponteiro (vetor de vetores)*/
    int **mat;
    
    /*aloca o numero total de linhas, com o tamanho de um ponteiro para inteiro.*/
    mat = malloc(linhas * sizeof(int*));    

    // /*aloca o numero total de colunas percorrendo o vetor 
    // de ponteiros e para cada posição aloca outro vetor com o tamanho 3.
    // com o tamanho de numero inteiros.*/
    for(int  i = 0 ; i < linhas ; i++){
        mat[i] = malloc(colunas * sizeof(int));
    }
    return mat;
}
//leitura do arquivo criando um variavel contendo todos os caracteres 
int *ler_arquivo(int *entrada, int *tam_entrada){
    FILE * arquivo;
    arquivo= fopen("tp1.txt","r");
    entrada = malloc(800* sizeof(int) );
    int i = 0;
	while(fscanf(arquivo, "%d", &entrada[i])!= EOF){
        i++;
	}
    *tam_entrada = i;
    return entrada;
}
//separa os caracteres em jogos separando as linhas e colunas e o estado em um unico grupo fazendo uma lista
tabuleiros* separaJogos(int* ent, int tamanho){
    tabuleiros *tab = (Apontador)malloc(sizeof(tabuleiros));
    tabuleiros *aux = tab;
    tab->prox = NULL;
    int i, cont = 0, j = 0;
    //for que checa todas as linhas 
    for (i = 0 ; i <= tamanho; i++){  
        tab->prox =(Apontador) malloc(sizeof(tabuleiros));
        tab->prox->prox = NULL;
        if(ent[i] >= 3 ){
            if(cont  < 1 ){
                tab->linhas = ent[i];
                tab->colunas = ent[i+1];
                i++;
                cont = 1;
            }else{
                cont = 0;
                j = 0;
                i--;
                for(;tab->prox != NULL ;tab = tab->prox);  
            }
        }else{
            tab->estado[j] = ent[i];
            tab->tam_estado = j+1;
            j++;
        }
    }
    return aux;
}
//funcao de impressao do tabuleiro
void imprimi_jogo(int **tab, int linhas, int colunas){
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf( "[%d]", tab[i][j]); 
        }
        printf("\n");
    }

}
//cria um tabuleiro vazio
int** geraTabuleiro(int linha, int coluna){
    int acessivel = 0, n_acessivel = -1;
    int primeira = acessivel;
    int alterna = n_acessivel;
    int i,j,n,m;
    n = linha;
    m = coluna;
    int ** tabuleiro;
    tabuleiro = cria_tabuleiro(n,m);
    //vai de casa em casa revezando uma sim e outra nao colocando -1 nas indisponiveis
    for(i = 0; i < n; i++){
        if(primeira == n_acessivel){
            primeira = acessivel;
            alterna = n_acessivel;
        }else{
            primeira = n_acessivel;
            alterna = acessivel;
        }
        for (j = 0; j < m; j++) {
            if(alterna == acessivel){
                tabuleiro[i][j] = alterna;
                alterna = n_acessivel;
            }else{
                tabuleiro[i][j] = alterna;
                alterna = acessivel;
            }
        }
    }
    return tabuleiro;
}

//coloca os dados do estado no tabuleiro vazio criado
tipo_peca *prenche_tabuleiro(int linha, int coluna, int tam_estado, int *estado, int **matriz){
    int i;
    int j;
    int t= 0;
    int m = 0;
    tipo_peca *pecas = malloc( tam_estado* sizeof(tipo_peca));
    for(i = 0; i < linha; i++){
        for (j = 0; j < coluna; j++) {    
            if( t == tam_estado+1 ){
                break;                
            }         
            if(matriz[i][j] == 0){
                matriz[i][j] = estado[t];
                if(matriz[i][j] == 1){
                    pecas[m].linha = i ;
                    pecas[m].coluna = j;
                    m++;
                    pecas->tam = m;
                }
                t++;
            }
       
        }
    }
    return pecas;
}
//verifica entre as pecas a que possui a melhor jogada
int melhor_jogada(int **matriz, int linha, int coluna, tipo_peca *pecas){
    int maior = 0;
    int *maximo = calloc(1,sizeof(int));
    FILE* arquivo = fopen("saida.txt", "r+");
    if(arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.txt.\n");
    }
    for(int i = 0; i < pecas->tam; i++){
        testa_caminhos(matriz, linha, coluna, pecas[i].linha,pecas[i].coluna,0,maximo);
        if(*maximo > maior){ 
            maior = *maximo;
            printf(" %d ",maior);
        }
        fprintf(arquivo, "%d\n", maior);
    }
    fclose(arquivo);
    return 1;
}
int testa_caminhos(int **jogo, int linha, int coluna, int linha_atual,int coluna_atual,int jogadas_atuais, int* maximo){

    int **matriz;
    matriz = cria_tabuleiro(linha,coluna);
    copia_matriz(matriz, jogo, linha, coluna);
    //checa as direcoes que sao possiveis mover as pecas e ao achar um movimento chamar a propria funcao

        //direita baixo 
        if(linha_atual+2 <= linha && coluna_atual+2 >= 0 && coluna_atual+2 <= coluna){
            if(matriz[linha_atual+1][coluna_atual+1] == 2){
                if(matriz[linha_atual+2][coluna_atual+2] == 0){       
                        matriz[linha_atual][linha_atual] = 0;
                        matriz[linha_atual+1][coluna_atual+1] = 0;
                        matriz[linha_atual+2][coluna_atual+2] = 1;
                         testa_caminhos(matriz,linha,coluna,linha_atual+2,coluna_atual+2,jogadas_atuais+1,maximo);
 
                }
            }
        }
        //esquerda baixo
        if(linha_atual+2 >= 0 && linha_atual+2 <= linha && coluna_atual-2 >= 0){
            if(matriz[linha_atual+1][coluna_atual-1] == 2){
                if(matriz[linha_atual+2][coluna_atual-2] == 0){
                        matriz[linha_atual][linha_atual] = 0;
                        matriz[linha_atual+1][coluna_atual-1] = 0;
                        matriz[linha_atual+2][coluna_atual-2] = 1;  
                        testa_caminhos(matriz,linha,coluna,linha_atual+2,coluna_atual-2,jogadas_atuais+1,maximo);
    
                }
            }
        }
        //cima direita
        if(linha_atual-2 >= 0 && coluna_atual+2 <= coluna){
            if(matriz[linha_atual-1][coluna_atual+1] == 2){
                if(matriz[linha_atual-2][coluna_atual+2] == 0){

                        matriz[linha_atual][linha_atual] = 0;
                        matriz[linha_atual-1][coluna_atual+1] = 0;
                        matriz[linha_atual-2][coluna_atual+2] = 1; 
                        testa_caminhos(matriz,linha,coluna,linha_atual-2,coluna_atual+2,jogadas_atuais+1,maximo);

                }
            }
        }
        //cima esquerda
        if(linha_atual-2 >= 0 && coluna_atual-2 >= 0){
            if(matriz[linha_atual-1][coluna_atual-1] == 2){
                if(matriz[linha_atual-2][coluna_atual-2] == 0){

                        matriz[linha_atual][linha_atual] = 0;
                        matriz[linha_atual-1][coluna_atual-1] = 0;
                        matriz[linha_atual-2][coluna_atual-2] = 1;                     
                        testa_caminhos(matriz,linha,coluna,linha_atual-2,coluna_atual-2,jogadas_atuais+1,maximo);
 
                }
            }
        }
            if(*maximo <= jogadas_atuais){ 
               *maximo = jogadas_atuais;
               }
            return jogadas_atuais; 

    
}
//cria uma copias da matriz de uma etapa atras da recursao para que possa ser usada
void copia_matriz(int **copia, int **matriz, int linha, int coluna){
    for(int i =0 ; i < linha; i++){
        for(int j =0 ; j < coluna; j++){
            copia[i][j] = matriz[i][j];
        }
    }
}



