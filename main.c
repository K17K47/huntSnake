#include<stdio.h>
#include<stdlib.h>

#include"ui.h"
#include"logic.h"
#include"aux.h"

int menu(){
   int out;

   system("clear");

   printf("Cobra e Caçador\n");
   printf("---------------\n");
   printf("1 - Jogar\n");
   printf("2 - Sair\n");

   scanf("%d", &out);

   return out;
}

int main(){
   Tabuleiro tab;
   clearTab(&tab);

   while(menu()!=2){
      int jogador = 0;
      clearTab(&tab);

      do{
         system("clear");
         printTabBasic(tab);

         Direcao dir;

         scanf("%d", &dir);

         jogada(&tab, 0, jogador*1+(!jogador)*2, dir);

         jogador = !jogador;
      }while(!jogoTerminado(tab));
   }

   return 0;
}
