#include"logic.h"
#include"aux.h"

int jogada(Tabuleiro* tab, int ponta, int jogador, Direcao dir){
   // testa se jogada é possivel, e se sim, escreve no tabuleiro a respectiva jogada
   int i,j;

   if(!ponta){ // Ponta A(W,A,S,D)
      i = tab->iA;
      j = tab->jA;
   }else{ // Ponta B(I,J,K,L)
      i = tab->iB;
      j = tab->jB;
   }

   int k, l;
   k = i;
   l = j;
   move(&k, &l, dir);

   if(!checkPointIsClear(*tab, k, l)){//Checa se a direcao da jogada
      return 0;//esta desimpedida
   }

   //classifica e escreve a jogada
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
   return 1;
}

int jogoTerminado(Tabuleiro tab){//testa se existe alguma jogada possivel
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

int pontos(Tabuleiro tab){//retorna o contador de pontos(TODO: remover, é futil)
   return tab.nJogadas;
}
