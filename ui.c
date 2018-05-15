#include<stdio.h>
#include<locale.h>
#include<wchar.h>

#include"ui.h"
#include"aux.h"

typedef struct _SFB{
	unsigned int height, width;
	wint_t* buffer;
}Framebuffer;

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

void initFramebuffer(Framebuffer* fb, unsigned h, unsigned w){
   //if(fb->buffer){
   //   free(fb->buffer);
   //}

   fb->buffer = malloc(sizeof(char)*h*w);

   fb->height = h;
   fb->width = w;
}

//void resizeFB(Framebuffer* fb, unsigned h, unsigned w){ // Redimensiona um framebuffer

//}

//Framebuffer horizConcat(Framebuffer* fbLeft, Framebuffer* fbRight){ // Concatena framebuffers de mesma altura

//}

void printFB(Framebuffer fb){ // Imprime framebuffer
   setlocale(LC_ALL, "");

   for(int i=0; i<fb.h; i++){
      for(int j=0; j<fb.w; j++){
         printf("%lc", fb.buffer[i*fb.w+j]);
      }
      printf("%lc", L'\n');
   }
}

Framebuffer printTab(Tabuleiro tab, int DHoriz, int DVert){ // Toma tab, e retorna sua representação grafica em um Framebuffer
   wint_t ponto = 0x262D;

   wint_t J1horiz = 0x2550;
   wint_t J1vert = 0x2551;

   wint_t J2horiz = 0x2501;
   wint_t J2vert = 0x2503;

   Framebuffer out;
   initFramebuffer(&out, 7+6*DVert, 7+6*DHoriz);

   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){
         out[i*(1+DVert)*out.w+j*(1+DHoriz)] = ponto;
      }
   }

   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){
         if(j!=6){
            Ponto p = tab.tab[i][j];

            wint_t traco;

            if(p.right == 0){
               traco = L' ';
            }else if(p.right == 1){
               traco = J1Horiz;
            }else if(p.right == 2){
               traco = J2Horiz;
            }

            for(int k=0; k<DHoriz; k++){
               out[i*(1+DVert)*out.w + j*(1+DHoriz) + k] = traco;
            }
         }
      }
      if(i!=6){
         for(int j=0; j<7; j++){
            Ponto p = tab.tab[i][j];

            wint_t traco;

            if(p.down == 0){
               traco = L' ';
            }else if(p.down == 1){
               traco = J1Vert;
            }else if(p.down == 2){
               traco = J2Vert;
            }

            for(int k=0; k<DVert; k++){
               out[i*(1+DVert+k)*out.w+j*(1+DHoriz)] = traco;
               if(j!=6){
                  for(int l=0; l<DHoriz; l++){
                     out[i*(1+DVert+k)*out.w+j*(1+DHoriz)+l]=L' ';
                  }
               }
            }
         }
      }
   }

   return out;
}

//Framebuffer printTabWithHints(Tabuleiro tab){
//   Framebuffer fb = printTab(tab);
//}
