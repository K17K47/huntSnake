#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

#include"ui.h"
#include"menus.h"

#include"logic.h"
#include"ai.h"
#include"aux.h"

int loopPartida(Tabuleiro tab, int jogador){ // Loop principal do jogo
   // Toma um tabuleiro com a coordenada inicial inicializada, e o primeiro jogador da rodada
   char input;

   do{
      Direcao dir;
      Framebuffer tabBasico, tabLetras, box, tmp;

      box = helpBox(2, 1);

      tmp = printTab(tab, 2, 1); //Gera o framebuffer com o tabuleiro simples
      tabBasico = horizConcat(tmp, box);
      free(tmp.buffer);

      tmp = printTabWithHints(tab, 2, 1); //Gera o framebuffer com a dica de teclas de jogada
      tabLetras = horizConcat(tmp, box);
      free(tmp.buffer);

      do{
         system("clear");
         printFB(tabLetras);  //Imprime o tabuleiro com dicas
         msgStatus(tab.nJogadas, jogador); //e a mensagem de status
         usleep(600000); // 600ms de aguardo

         system("clear");
         printFB(tabBasico);  //Imprime o tabuleiro simples
         msgStatus(tab.nJogadas, jogador);
         usleep(200000); // 200ms de aguardo

         input = getchar(); //Captura a entrada

         if(input == 'a' || input == 's' || input == 'd' ||
            input == 'w' || input == 'j' || input == 'k' ||
            input == 'l' || input == 'i' || input == 'q'){
            break; // Se for comando valido, responde. Senao, ignora e continua o loop
         }
      }while(1);

      free(tabBasico.buffer); //Dealoca a memoria usada para
      free(tabLetras.buffer); //desenhar os tabuleiros

      if(input != 'q'){ //Caso nao seja a opção de sair
         int ponta; // interpreta a direção da jogada
         decodificaJogada(input, &dir, &ponta);

         // se a jogada é possivel, grava ela no tabuleiro
         if(jogada(&tab, ponta, jogador*1+(!jogador)*2, dir)){
            tab.nJogadas++;// e atualiza o contador
            jogador = !jogador; // e o jogador da proxima jogada
         }
      }

   }while(!jogoTerminado(tab) && (input != 'q'));

   if(input == 'q'){
      return 0;
   }

   if(jogoTerminado(tab)){ //Se o jogo terminou pela cobra ser morta
      system("clear");
      Framebuffer tabBasico;
      tabBasico = printTab(tab, 2, 1);//Imprime uma visao do tabuleiro
      printFB(tabBasico);
      free(tabBasico.buffer);

      msgPartida(tab.nJogadas, jogador);// e exibe uma mensagem de fim de rodada
      do{
         input = getchar();
      }while(input!='c');
   }

   return tab.nJogadas;
}

void inicializaTabuleiro(Tabuleiro* tab, int jogador){
   char input = 0;

   clearTab(tab);

   system("clear");
   printf("Jogador %d é a cobra!\n", jogador+1);
   printf("Digite as coordenadas iniciais (Ambas de 0 a 7):\n");
   printf("Coordenada vertical:\n");

   // Le coordenadas iniciais
   do{
      usleep(100000);
      input = getchar();
   }while(input<'0' || input>'7');

   // e inicializa o tabuleiro
   tab->iA = input-'0';
   tab->iB = tab->iA;

   printf("Coordenada horizontal:\n");

   do{
      usleep(100000);
      input = getchar();
   }while(input<'0' || input>'7');

   tab->jA = input-'0';
   tab->jB = tab->jA;
}

int main(){
   struct termios velhaConf, novaConf;

   tcgetattr(0, &novaConf); //Fazemos copia da configuracao do terminal
   // para restaura-la quando necessario
   velhaConf = novaConf;
   novaConf.c_lflag &= ~( ICANON | ECHO );//Modo nao-canonico e sem eco, para a entrada
   //assim, getchar() não faz o processo ficar em waiting
   novaConf.c_cc[VMIN] = 0;
   novaConf.c_cc[VTIME] = 0;

   int quit = 0;
   do{
      char input;

      tcsetattr(0, TCSANOW, &novaConf);//Aplica a nova configuração do terminal

      do{
         menuPrincipal();//Imprime o menu principal
         usleep(100000);
         input = getchar();
      }while(input!= '1' && input !='2' && input!='3');

      if(input == '1'){// interpreta as opcoes do menu principal
         do{
            menuPartida();//Imprime menu de partida
            usleep(100000);
            input = getchar();
         }while(input!='1' && input!='2' && input!='3');

         int p1, p2;
         Tabuleiro tab;
         switch(input){//interpreta as opcoes do menu de partida
            case '1': //Partida entre humanos

               inicializaTabuleiro(&tab, 0);
               p1 = loopPartida(tab ,0); //abre a primeira rodada
               if(!p1)//zero pontos é ragequit
                  break;

               inicializaTabuleiro(&tab, 1);
               p2 = loopPartida(tab, 1);//abre a segunda rodada
               if(!p2)//zero pontos é quitão
                  break;

               for(int i=5; i>=1; i--){
                  msgVitoria(p1, p2);//mostra mensagem de vitoria ou empate
                  printf("Indo ao menu principal em %d segundos\n", i);
                  sleep(1);
               }
               break;
            case '2'://opcao de humano contra computador
               inicializaTabuleiro(&tab, 0); // Humano dá coordenadas iniciais
               p1 = rodadaComputador(&tab, 0); // Computador é caçador

               if(!p1)
                  break;

               computadorInicializa(&tab); // Computador dá coordenadas iniciais
               p2 = rodadaComputador(&tab, 1); // Computador é cobra

               if(!p2)
                  break;

               for(int i =5; i>=1; i--){
                  msgVitoria(p1, p2);
                  printf("Indo ao menu principal em %d segundos\n", i);
                  sleep(1);
               }
               break;
            case '3':// volta para o menu principal
               quit = 0;
               break;
         }
      }else if(input == '2'){
         for(int i=10; i>=1; i--){
            creditos();
            printf("\n\nIndo ao menu principal em %d segundos\n", i);
            sleep(1);
         }
      }else{
         quit = 1;
      }

      tcsetattr(0, TCSANOW, &velhaConf);//restaura as configurações do terminal
   }while(!quit);

   return 0;
}
