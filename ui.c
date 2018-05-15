#include<stdlib.h>

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

//Aloca memoria para framebuffer, e inicializa suas propriedades
void initFramebuffer(Framebuffer* fb, unsigned h, unsigned w){
   //if(fb->buffer){
   //   free(fb->buffer);
   //}

   fb->buffer = malloc(sizeof(wchar_t)*h*w);

   for(int i=0; i<h*w; i++){
      fb->buffer[i] = L' ';
   }

   fb->height = h;
   fb->width = w;
}

//void resizeFB(Framebuffer* fb, unsigned h, unsigned w){ // Redimensiona um framebuffer

//}

//Framebuffer horizConcat(Framebuffer* fbLeft, Framebuffer* fbRight){ // Concatena framebuffers de mesma altura

//}

void printFB(Framebuffer fb){ // Imprime framebuffer
   setlocale(LC_ALL, "");

   for(int i=0; i<fb.height; i++){
      for(int j=0; j<fb.width; j++){
         printf("%lc", fb.buffer[i*fb.width+j]);
      }
      printf("%lc", L'\n');
   }
}

//Gera tabuleiro com dica de comandos para a jogada
Framebuffer printTabWithHints(Tabuleiro tab, int DHoriz, int DVert){
	Framebuffer fb = printTab(tab, DHoriz, DVert);//Gera um tabuleiro basico, para poupar trabalho

	wint_t letras1[] = {L'W',L'D',L'S',L'A'};//Teclas para ponta A
	wint_t letras2[] = {L'I',L'L',L'K',L'J'};//Teclas para ponta B
	for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){//Procura casas livres ao redor da ponta A
		int i = tab.iA ; int j = tab.jA;
		int k,l;
		k = i;
		l = j;
		move(&k,&l,dir);
		if(checkPointIsClear(tab,k,l)){//e substitui pela letra da tecla correspondente para a jogada
			fb.buffer[k*(1+DVert)*fb.width+l*(1+DHoriz)]=letras1[dir];
		}
	}
	for(Direcao dir=DIR_CIMA; dir<=DIR_ESQ; dir++){//loop similar ao acima, para a ponta B
		int i = tab.iB ; int j = tab.jB;
		int k,l;
		k = i;
		l = j;
		move(&k,&l,dir);
		if(checkPointIsClear(tab,k,l)){
			fb.buffer[k*(1+DVert)*fb.width+l*(1+DHoriz)]=letras2[dir];
		}
	}
	return(fb);
}

//Gera um tabuleiro basico
Framebuffer printTab(Tabuleiro tab, int DHoriz, int DVert){ // Toma tab, e retorna sua representação grafica em um Framebuffer
   //Definicao dos caracteres usados no tabuleiro
   //Atencao: Sao todos caracteres longos, Unicode
   wint_t ponto = 0x262D;//Pontos do tabuleiro

   //Caracteres do jogador 1
   wint_t J1horiz = 0x2550;//traco horizontal
   wint_t J1vert = 0x2551;//traco vertical

   //Caracteres do jogador 2
   wint_t J2horiz = 0x2501;//traco horizontal
   wint_t J2vert = 0x2503;//traco vertical

   Framebuffer out;
   initFramebuffer(&out, 7+6*DVert, 7+6*DHoriz);//Aloca um framebuffer
   //para armazenar o tabuleiro

   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){//preenche com os pontos
         out.buffer[i*(1+DVert)*out.width+j*(1+DHoriz)] = ponto;
      }
   }

   //preenche com os tracos ou espacos vazios
   for(int i=0; i<7; i++){
      for(int j=0; j<7; j++){
         if(j!=6){
            Ponto p = tab.tab[i][j];

            wchar_t traco;

            if(p.right == 0){
               traco = L' ';
            }else if(p.right == 1){
               traco = J1horiz;
            }else if(p.right == 2){
               traco = J2horiz;
            }

            for(int k=1; k<DHoriz+1; k++){//tracos horizontais
               out.buffer[i*(1+DVert)*out.width + j*(1+DHoriz) + k] = traco;
            }
         }
      }
      if(i!=6){
         for(int j=0; j<7; j++){
            Ponto p = tab.tab[i][j];

            wchar_t traco;

            if(p.down == 0){
               traco = L' ';
            }else if(p.down == 1){
               traco = J1vert;
            }else if(p.down == 2){
               traco = J2vert;
            }

            for(int k=1; k<DVert+1; k++){//tracos verticais
               out.buffer[(i*(1+DVert)+k)*out.width+j*(1+DHoriz)] = traco;
               if(j!=6){
                  for(int l=1; l<DHoriz+1; l++){//e espacos para alinhamento
                     out.buffer[(i*(1+DVert)+k)*out.width+j*(1+DHoriz)+l]=L' ';
                  }
               }
            }
         }
      }
   }

   return out;//retorna o framebuffer resultante
}
