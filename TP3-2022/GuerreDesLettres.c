#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

sem_t mutex;
sem_t libre;
sem_t occupe;

char* tampon;
unsigned int nbProducteurs=0;
unsigned int nbConsomateurs=0;
unsigned int  nbCharEcrit = 0;
unsigned int  nbCharLu = 0;
unsigned int tailleTampon;
unsigned int ic=0, ip=0;
bool flag_de_fin = false;

void write_zero() {
   for (int i=0; i < nbConsomateurs; i++) {
      tampon[i] = '0';
   }
}

void sig_handler(int signum){
   flag_de_fin = true;
}

// fonction exécutée par les producteurs
void* producteur( void* pid) {
   char c;
   while(1) {
      sem_wait(&libre);
      sem_wait(&mutex);
      printf("caractère écrit : %c\n", c);
      tampon[ip] = 'A' + rand()%26;
      ip = (ip+1) % tailleTampon;
      nbCharEcrit++;
      sem_post(&mutex);
      sem_post(&occupe);
      if(flag_de_fin) break;
   }
   return NULL;             
}

// fonction exécutée par les consommateurs
void* consommateur(void *cid) {
   while(1) {
      sem_wait(&occupe);
      sem_wait(&mutex);
      char c = tampon[ic];
      if(c == '0') break;
      printf("caractère lu : %c \n", c);
      ic = (ic+1) % tailleTampon;
      nbCharLu++;
      sem_wait(&mutex);
      sem_post(&libre);
   }
  return NULL;   
}

// fonction main
int main(int argc, char* argv[]) {
   /* Les paramètres du programme sont, dans l’ordre :
      le nombre de producteurs, le nombre de consommateurs
      et la taille du tampon.*/

   signal(SIGALRM,sig_handler);
   srand(time(NULL));
    
   nbProducteurs = atoi(argv[1]);
   nbConsomateurs = atoi(argv[2]);
   tailleTampon = atoi(argv[3]);
   tampon = malloc(tailleTampon);

   const u_int8_t NUMBER_OF_THREADS = nbProducteurs + nbConsomateurs;
   pthread_t tids[nbProducteurs];
   pthread_t cids[nbConsomateurs];
   sem_init(&mutex, 0, 1);
   sem_init(&libre, 0, 1);
   sem_init(&occupe, 0, 1);

   for (int i = 0; i < nbProducteurs; i++) {
       pthread_create(&tids[i], NULL, producteur, (void*)i);
   }

   for (int i = 0; i < nbConsomateurs; i++) {
       pthread_create(&cids[i], NULL, consommateur, (void*)i);
   }

   alarm(1);

   for (int i = 0; i < nbProducteurs; i++) {
       pthread_join(tids[i], NULL);
   }

   write_zero();

   for (int i = 0; i < nbConsomateurs; i++) {
             pthread_join(cids[i], NULL);
   }

   printf("Les consomateurs ont fait en tout %d écritures et les lecteurs ont fait %d lectures \n", nbCharEcrit, nbCharLu);

   return 0;
}
