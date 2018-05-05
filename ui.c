#include<stdio.h>
#include<locale.h>
#include<wchar.h>

#include"ui.h"
#include"aux.h"

int simboloPonto = 0x262D;

/*
*  Ponto : U+262D
*  Jogador 1 : Horizontal - U+2550
*              Vertical   - U+2551
*  Jogador 2 : Horizontal - U+2501
*              Vertical   - U+2503
*/

void _printSeg(Ponto p, Direcao dir){
   if(dir == DIR_DIR){
      if(p.right == 0){
         printf("  ");
      }else if(p.right == 1){
         printf("%lc%lc", (wint_t)0x2550, (wint_t)0x2550);
      }else if(p.right == 2){
         printf("%lc%lc", (wint_t)0x2501, (wint_t)0x2501);
      }
   }else if(dir == DIR_BAIXO){
      if(p.down == 0){
         printf(" ");
      }else if(p.down == 1){
         printf("%lc", (wint_t)0x2551);
      }else if(p.down == 2){
         printf("%lc", (wint_t)0x2503);
      }
   }
}

void printTabBasic(Ponto tab[7][7]){
   setlocale(LC_ALL, "");

   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){
         printf("%lc", (wint_t) simboloPonto);
         if(j!=6){
            _printSeg(tab[i][j], DIR_DIR);
         }
      }
      printf("\n");
      if(i!=6){
         for(int j=0; j<7; j++){
            _printSeg(tab[i][j], DIR_BAIXO);
            if(j!=6){
               printf("  ");
            }
         }
         printf("\n");
      }
   }
}
