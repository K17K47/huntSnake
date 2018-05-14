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

void printTabBasic(Tabuleiro tab){
   setlocale(LC_ALL, "");

   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){
         printf("%lc", (wint_t) simboloPonto);
         if(j!=6){
            _printSeg(tab.tab[i][j], DIR_DIR);
         }
      }
      printf("\n");
      if(i!=6){
         for(int j=0; j<7; j++){
            _printSeg(tab.tab[i][j], DIR_BAIXO);
            if(j!=6){
               printf("  ");
            }
         }
         printf("\n");
      }
   }
}

	void VizinLivre( vetor, i, j);
		for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){
			int k,l;
			k = i;
			j = l;
			move(&k,&l,dir);
			vetor[dir] = checkPointIsClear(tab,k,l);
		}
	void letras(Tabuleiro){
		VizinLivre(int vetorLivre1[4], Tabuleiro.iA, Tabuleiro.jA);
		VizinLivre(int vetorLivre2[4], Tabuleiro.iB, Tabuleiro.jB);
		char vizinLetrado1[4],vizinLetrado2[4]
		for( int k = 0; k<4; k++){
			if(vetorLivre1[k]==1){
				char letras1[4]={'a','b','c','d'};
				vizinLetrado1[k]=letras1[k];
			}
			else{
				vizinLetrado1[k]= ' ';
			}
			if(vetorLivre2[k]==1){
				char letras2[4]={'e','f','g','h'};
				vizinLetrado2[k]=letras2[k];
			}
			else{
				vizinLetrado2[k]= ' ';
			}
		}
	}
void printTabLetras(Tabuleiro tab){
	sprintf(printTabBasic,
}

typedef struct _SFB{
	unsigned int height, widht;
	char* burffer;
}Framebuffer;

voi initFramebuffer(Framebuffer* fb, int h, int w)
