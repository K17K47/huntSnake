#define _AUX_H
#ifndef _AUX_H

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

void clearTab(Ponto tab[7][7]); // Limpa o tabuleiro
void move(int *i, int *j, Direcao dir); // Calcula ponto após movimento em uma direção
int checkBorder(int i, int j); // Checa se coordenada está dentro do tabuleiro
int checkPointIsClear(Ponto tab[7][7], int i, int j); // Checa se o ponto não tem obstrução/já foi navegado

#endif
