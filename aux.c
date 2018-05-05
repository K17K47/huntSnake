#include"aux.h"

void move(int *i, int *j, Direcao dir){ // Calcula ponto após movimento em uma direção
   switch(dir){
      case DIR_CIMA:  // Para cima
         (*i)--;
         break;
      case DIR_DIR:  // Para direita
         (*j)++;
         break;
      case DIR_BAIXO:  // Para baixo
         (*i)++;
         break;
      case DIR_ESQ:  // Para esquerda
         (*j)--;
         break;
   }
}

int checkBorder(int i, int j){   // Checa se coordenada está dentro do tabuleiro
   return (0 <= i && i < 7) && (0 <= j && j < 7);
}

int checkPointIsClear(Ponto tab[7][7], int i, int j){ // Checa se a direção não tem obstrução
   int di, dj;

   if(tab[i][j].right){
      di = i;
      dj = j;
      move(&di, &dj, DIR_DIR);
      if(checkBorder(di, dj)){
         return 0;
      }
   }
   if(tab[i][j].down){
      di = i;
      dj = j;
      move(&di, &dj, DIR_BAIXO);
      if(checkBorder(di, dj)){
         return 0;
      }
   }

   di = i;
   dj = j;
   move(&di, &dj, DIR_CIMA);
   if(checkBorder(di,dj)){
      if(tab[di][dj].down){
         return 0;
      }
   }

   di = i;
   dj = j;
   move(&di, &dj, DIR_ESQ);
   if(checkBorder(di,dj)){
      if(tab[di][dj].right){
         return 0;
      }
   }

   return 1;
}
