#ifndef _UI_H
#define _UI_H

#include<stdio.h>
#include<locale.h>
#include<wchar.h>

#include"aux.h"

typedef struct _SFB{
   unsigned height, width;
   wint_t* buffer;
}Framebuffer;

void printTabBasic(Tabuleiro tab); // Imprime tabuleiro
void initFramebuffer(Framebuffer *fb, unsigned h, unsigned w);
//void resizeFB(Framebuffer* fb, unsigned h, unsigned w);
void printFB(Framebuffer fb);
//Framebuffer horizConcat(Framebuffer* fbLeft, Framebuffer* fbRight);
Framebuffer printTab(Tabuleiro tab, int DHoriz, int DVert);
//Framebuffer printTabWithHints(Tabuleiro tab);

#endif
