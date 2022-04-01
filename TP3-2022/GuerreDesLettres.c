#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

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
      sem_wait(&libre);
      sem_wait(&mutex);
      tampon[ip] = '0';
      ip = (ip+1) % tailleTampon;
      nbCharEcrit++;
      sem_post(&mutex);
      sem_post(&occupe);
   }
}

void sig_handler(int signum){
   flag_de_fin = true;
}

// fonction exécutée par les producteurs
void* producteur( void* pid) {
   char c;
   int nbEcritures = 0;
   while(1) {
      sem_wait(&libre);
      sem_wait(&mutex);
      tampon[ip] = 'A' + rand()%26;
      ip = (ip+1) % tailleTampon;
      nbCharEcrit++;
      nbEcritures++;
      sem_post(&mutex);
      sem_post(&occupe);
      if(flag_de_fin) {
         printf("Le producteur %d a écrit %d lettres dans le tampon \n", pid, nbEcritures);
         pthread_exit(NULL);
      }
   }
   return NULL;             
}

// fonction exécutée par les consommateurs
void* consommateur(void *cid) {
   int nbConsomations = 0;
   while(1) {
      sem_wait(&occupe);
      sem_wait(&mutex);
      char c = tampon[ic];
      //printf("caractère lu : %c \n", c);
      ic = (ic+1) % tailleTampon;
      nbConsomations++;
      nbCharLu++;
      sem_post(&mutex);
      sem_post(&libre);
      if(c == '0') {
         printf("Le consomateur %d a consomé %d lettres dans le tampon \n", cid, nbConsomations);
         pthread_exit(NULL);
      }
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
   tampon = calloc(tailleTampon, sizeof(char));

   pthread_t tids[nbProducteurs];
   pthread_t cids[nbConsomateurs];

   sem_init(&mutex, 0, 1);
   sem_init(&libre, 0, tailleTampon);
   sem_init(&occupe, 0, 0);

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

   printf("Les consomateurs ont fait en tout %d productions et les consomateurs ont fait %d consomations \n", nbCharEcrit, nbCharLu);

   return 0;
}
