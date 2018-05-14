#include"logic.h"
#include"aux.h"

void jogada(Tabuleiro* tab, int ponta, int jogador, Direcao dir){
   int i,j;

   if(!ponta){ // Ponta A
      i = tab->iA;
      j = tab->jA;
   }else{ // Ponta B
      i = tab->iB;
      j = tab->jB;
   }

   if((dir == DIR_BAIXO)||(dir == DIR_DIR)){
      if(dir == DIR_DIR)
         tab->tab[i][j].right = jogador;
      if(dir == DIR_BAIXO)
         tab->tab[i][j].down = jogador;
         move(&i, &j, dir);
   }else{
      move(&i, &j, dir);
      if(dir == DIR_CIMA){
         tab->tab[i][j].down = jogador;
      }else{
         tab->tab[i][j].right = jogador;
      }
   }

   if(!ponta){ // Ponta A
      tab->iA = i;
      tab->jA = j;
   }else{ // Ponta B
      tab->iB = i;
      tab->jB = j;
   }
}

int jogoTerminado(Tabuleiro tab){
   int i, j;

   for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){
      i = tab.iA;
      j = tab.jA;

      move(&i, &j, dir);
      if(checkPointIsClear(tab, i, j)){
         return 0;
      }
   }

   for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){
      i = tab.iB;
      j = tab.jB;

      move(&i, &j, dir);
      if(checkPointIsClear(tab, i, j)){
         return 0;
      }
   }

   return 1;
}

int pontos(Tabuleiro tab){
   return tab.nJogadas;
}
