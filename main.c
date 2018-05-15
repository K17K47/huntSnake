#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<unistd.h>

#include"ui.h"
#include"logic.h"
#include"aux.h"

void menuPrincipal(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
  (1) Iniciar partida\n\
      (2)  Sair\n");
}

void menuPartida(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
    Tipo de partida:\n\
\n\
(1)  Humano vs. Humano\n\
(2) Máquina vs. Humano\n\
(3)      Voltar\n");
}

void menuWIP(){
   system("clear");

   printf("\
+~~~~~~~~~~~~~~~~~~~~~+\n\
# A Cobra e o Caçador #\n\
+~~~~~~~~~~~~~~~~~~~~~+\n\
\n\
 Item não implementado\n");
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

int loopPartida(Tabuleiro tab, int jogador){ // Loop principal do jogo
   // Toma um tabuleiro com a coordenada inicial inicializada, e o primeiro jogador da rodada
   char input;

   do{
      Direcao dir;
      Framebuffer tabBasico, tabLetras;

      tabBasico = printTab(tab, 2, 1); //Gera o framebuffer com o tabuleiro simples
      tabLetras = printTabWithHints(tab, 2, 1); //Gera o framebuffer com a dica de teclas de jogada

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
      }while(input!= '1' && input !='2');

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
               clearTab(&tab);

               system("clear");
               printf("Jogador 1 é a cobra!\n"); //Inicializa o tabuleiro com coordenadas iniciais
               printf("Digite as coordenadas iniciais (Ambas de 0 a 7):\n");
               printf("Coordenada vertical:\n");
               do{
                  usleep(100000);
                  input = getchar();
               }while(input<'0' || input>'7');
               tab.iA = input-'0';
               tab.iB = tab.iA;

               printf("Coordenada horizontal:\n");
               do{
                  usleep(100000);
                  input = getchar();
               }while(input<'0' || input>'7');
               tab.jA = input-'0';
               tab.jB = tab.jA;

               p1 = loopPartida(tab ,0); //abre a primeira rodada
               if(!p1)//zero pontos é ragequit
                  break;

               clearTab(&tab);

               system("clear");
               printf("Jogador 2 é a cobra!\n"); //inicializa o tabuleiro para o segundo jogador
               printf("Digite as coordenadas iniciais (Ambas de 0 a 7):\n");
               printf("Coordenada vertical:\n");
               do{
                  usleep(100000);
                  input = getchar();
               }while(input<'0' || input>'7');
               tab.iA = input-'0';
               tab.iB = tab.iA;

               printf("Coordenada horizontal:\n");
               do{
                  usleep(100000);
                  input = getchar();
               }while(input<'0' || input>'7');
               tab.jA = input-'0';
               tab.jB = tab.jA;

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
               for(int i =5; i>=1; i--){
                  menuWIP();
                  printf("Indo ao menu principal em %d segundos\n", i);
                  sleep(1);
               }
               break;
            case '3':// volta para o menu principal
               quit = 0;
               break;
         }
      }else{
         quit = 1;
      }

      tcsetattr(0, TCSANOW, &velhaConf);//restaura as configurações do terminal
   }while(!quit);

   return 0;
}
