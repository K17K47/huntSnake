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

typedef struct _SFB{
	unsigned int height, width;
	char* buffer;
}Framebuffer;

void initFramebuffer(Framebuffer* fb, unsigned h, unsigned w){
   if(fb->buffer){
      free(fb->buffer);
   }

   fb->buffer = malloc(sizeof(char)*h*w);

   fb->height = h;
   fb->width = w;
}

void resizeFB(Framebuffer* fb, unsigned h, unsigned w){ // Redimensiona um framebuffer

}

Framebuffer horizConcat(Framebuffer* fbLeft, Framebuffer* fbRight){ // Concatena framebuffers de mesma altura

}

void printFB(Framebuffer fb){ // Imprime framebuffer

}

Framebuffer printTab(Tabuleiro tab){ // Toma tab, e retorna sua representação grafica em um Framebuffer

}

Framebuffer printTabWithHints(Tabuleiro tab){
	Framebuffer fb = printTab(tab);
	letras1 = {'w','d','s','a'};
	letras2 = {'i','l','k','j'};
	for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){
		int i = tab.iA ; int j = tab.jA;
		int k,l;
		k = i;
		l = j;
		move(&k,&l,dir);
		if(checkPointIsClear(tab,k,l)){
			fb[k,l]=letras1[dir];
		}
	}
	for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){
		int i = tab.iB ; int j = tab.jB;
		int k,l;
		k = i;
		l = j;
		move(&k,&l,dir);
		if(checkPointIsClear(tab,k,l)){
			fb[k,l]=letras2[dir];
		}
	}
	return(fb);
}
