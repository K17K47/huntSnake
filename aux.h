#ifndef _AUX_H
#define _AUX_H

typedef enum _EDir{
   DIR_CIMA,
   DIR_DIR,
   DIR_BAIXO,
   DIR_ESQ
}Direcao;

typedef struct _SPonto{ // Armazena Informações sobre um ponto no tabuleiro
   int right;           // 0 - Não há jogada nessa direção,  1 - Jogada do jogador 1
   int down;            // 2 - Jogada do jogador 2, >= 3 - Impossível
}Ponto;

typedef struct _STabuleiro{
   Ponto tab[7][7]; // Tabuleiro
   int iA, jA; //Extremidades da cobra
   int iB, jB;
   int nJogadas; // Conta o numero de jogadas executadas
} Tabuleiro;

void clearTab(Tabuleiro *tab); // Limpa o tabuleiro

void move(int *i, int *j, Direcao dir); // Calcula ponto após movimento em uma direção
int checkBorder(int i, int j); // Checa se coordenada está dentro do tabuleiro
int checkPointIsClear(Tabuleiro tab, int i, int j); // Checa se o ponto não tem obstrução/já foi navegado

void decodificaJogada(char input, Direcao* dir, int* ponta); // Decodifica a tecla entrada em na ponta desejada, e na direcao desejada
// w,a,s,d -> Ponta 0, i,j,k,l -> Ponta 1
// w,i -> Cima, a,j -> Esquerda, s,k -> Baixo, d,l -> Direita

#endif
