#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

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
   struct termios velhaConf, novaConf;

   tcgetattr(0, &novaConf);

   velhaConf = novaConf;
   novaConf.c_lflag &= ~( ICANON | ECHO );
   novaConf.c_cc[VMIN] = 0;
   novaConf.c_cc[VTIME] = 0;

   Tabuleiro tab;
   clearTab(&tab);

   while(menu()!=2){
      char input;
      int jogador = 0;
      clearTab(&tab);

      tcsetattr(0, TCSANOW, &novaConf);

      do{
         Direcao dir;

         do{
            system("clear");
            printTabBasic(tab);
            usleep(600000); // 600ms de aguardo

            system("clear");
            printTabBasic(tab);
            usleep(200000); // 200ms de aguardo

            input = getchar();

            if(input == 'a' || input == 's' || input == 'd' ||
               input == 'w' || input == 'j' || input == 'k' ||
               input == 'l' || input == 'i' || input == 'q'){
               break;
            }
         }while(1);

         if(input != 'q'){
            int ponta;
            if(input == 'a' || input == 's' || input == 'd' ||
            input == 'w'){
               ponta = 0;
               switch(input){
                  case 'a':
                     dir = DIR_ESQ;
                     break;
                  case 's':
                     dir = DIR_BAIXO;
                     break;
                  case 'd':
                     dir = DIR_DIR;
                     break;
                  case 'w':
                     dir = DIR_CIMA;
                     break;
               }
            }

            if(input == 'j' || input == 'k' || input == 'l' ||
            input == 'i'){
               ponta = 1;
               switch(input){
                  case 'j':
                     dir = DIR_ESQ;
                     break;
                  case 'k':
                     dir = DIR_BAIXO;
                     break;
                  case 'l':
                     dir = DIR_DIR;
                     break;
                  case 'i':
                     dir = DIR_CIMA;
                     break;
               }
            }

            if(jogada(&tab, ponta, jogador*1+(!jogador)*2, dir)){
               tab.nJogadas++;
               jogador = !jogador;
            }
         }

      }while(!jogoTerminado(tab) && (input != 'q'));
      tcsetattr(0, TCSANOW, &velhaConf);
   }

   return 0;
}
