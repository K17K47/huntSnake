#include<stdlib.h>

#include"ai.h"

void computadorInicializa(Tabuleiro* tab){
	// Decisão da primeira jogada do computador, como cobra
	tab->iA = rand()%7;
	tab->iB = tab->iA;

	tab->jA = rand()%7;
	tab->jB = tab->jA;
}

void turnoComputador(Tabuleiro tab, int cacador, char* input){
	// Decisão da próxima jogada do computador

	char keys[] = {'w','d','s','a','i','l','k','j'};

	*input = keys[rand()%8];
}
