#include<stdio.h>
#include<stdlib.h>

#include"menus.h"

void menuPrincipal(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
#                     #\n\
#   By Gromit e Sasha #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
  (1) Iniciar partida\n\
     (2) Créditos\n\
      (3)  Sair\n");
}

void menuPartida(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
#                     #\n\
#   By Gromit e Sasha #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
    Tipo de partida:\n\
\n\
(1)  Humano vs. Humano\n\
(2) Máquina vs. Humano\n\
(3)    Voltar\n");
}

void menuWIP(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
#                     #\n\
#   By Gromit e Sasha #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
 Item não implementado\n");
}

void creditos(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
#                     #\n\
#   By Gromit e Sasha #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
Jogo escrito por:\n\
\n\
 Gromit - Vinícius Santos Barbosa\n\
 Sasha  - Lucas Lopes Costa\n");
}

void msgStatus(int pontos, int jogador){
   printf("%d pontos, vez do jogador ", pontos);
   if(!jogador){
      printf("1\n");
   }else{
      printf("2\n");
   }
   printf("Tecle 'q' para retornar ao menu principal\n");
}

void msgPartida(int pontos, int jogador){
   printf("Cobra fez %d pontos\n", pontos);
   printf("Tecle 'c' para continuar\n");
}

void msgVitoria(int p1, int p2){
   system("clear");
   if(p1 == p2){
      printf("Empate! Espero que tenha uma revanche...\n");
   }else{
      int player;
      if(p1 > p2){
         player = 1;
      }else{
         player = 2;
      }

      printf("O Jogador %d é um ótimo caçador ou uma ótima cobra! (Wut?!)\n", player);
      printf("    Parabéns! A vitória é sua jogador %d\n", player);
   }
}

Framebuffer helpBox(int Dhoriz, int Dvert){
   Framebuffer out;
   int H, W;
   H = 6*Dvert+7;
   W = 80-(7+Dhoriz*6);

   initFramebuffer(&out, H, W);

   swprintf(&out.buffer[ 0  ], 40, L"   | As teclas W, A, S, D e I, J, K, L");
   swprintf(&out.buffer[ W  ], 40, L"   | controlam as pontas da cobra:");
   swprintf(&out.buffer[2*W ], 40, L"   | ");
   swprintf(&out.buffer[3*W ], 40, L"   |             W     I");
   swprintf(&out.buffer[4*W ], 40, L"   |             %lc     %lc", (wchar_t)0x25B2, (wchar_t)0x25B3);
   swprintf(&out.buffer[5*W ], 40, L"   |           A%lc%lc%lcD J%lc%lc%lcL", (wchar_t)0x25C0, (wchar_t)0x25CF, (wchar_t)0x25B6, (wchar_t)0x25C1, (wchar_t)0x25CB, (wchar_t)0x25B7);
   swprintf(&out.buffer[6*W ], 40, L"   |             %lc     %lc", (wchar_t)0x25BC, (wchar_t)0x25BD);
   swprintf(&out.buffer[7*W ], 40, L"   |             S     K");
   swprintf(&out.buffer[8*W ], 40, L"   | ");
   swprintf(&out.buffer[9*W ], 40, L"   | O objetivo é traçar a cobra mais");
   swprintf(&out.buffer[10*W], 40, L"   | longa. O turno termina quando não");
   swprintf(&out.buffer[11*W], 40, L"   | há jogadas possíveis. A pontuação");
   swprintf(&out.buffer[12*W], 40, L"   | é proporcional ao comprimento.");
   return out;
}
