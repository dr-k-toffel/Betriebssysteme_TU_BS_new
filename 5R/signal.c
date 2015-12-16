#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "backtrace.h"

/*
void sigfunc(int sig) {
   int c;

   if(sig != SIGINT)
      return;
   else {
      printf("\nWollen Sie das Programm beenden (j/n) : ");
      c=getchar();
      if(c == 'j')
         exit (EXIT_FAILURE);
      else
         return;
   }
}
*/

int main(int argc, char *argv[]) 
{
   /*
    int i;

   //signal(SIGINT, &sigfunc);

   initialize_signal_handler();
   printf("Mit STRG+C beenden");
      
   while(1) {
      //printf("Mit STRG+C beenden");
      for(i = 0; i <= 48; i++) {
         //printf("\b");
         i++;
      }
   }
   */

   if (argc < 2) {
     printf("Bitte rufen die Das Programm wie folgt auf\n\"signal SIG PID\"\n");
     return EXIT_FAILURE;
   }

   int sig = atoi(argv[1]);
   int pid = atoi(argv[2]);
   
   printf("send signal %d to pid %d\n", sig, pid);

   kill(pid, sig);

   return EXIT_SUCCESS;
}
