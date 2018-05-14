#ifndef _LOGIC_H
#define _LOGIC_H

#include"aux.h"


// Realiza uma jogada no tabuleiro
// int ponta - 0 ou 1
// int jogador - 1 ou 2
void jogada(Tabuleiro *tab, int ponta, int jogador, Direcao dir);
int jogoTerminado(Tabuleiro tab); // Checa se existe alguma jogada possivel
int pontos(Tabuleiro tab); // Determina quantos pontos foram feitos

#endif
