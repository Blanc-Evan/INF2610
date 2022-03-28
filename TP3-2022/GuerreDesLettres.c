#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;
sem_t product;
char* tampon;

// fonction exécutée par les producteurs
void* producteur( void* pid) {
   srand(time(NULL));
   char c;
   while(1) {
      c='A' + rand()%26;

   }
   return NULL;             
}
// fonction exécutée par les consommateurs
void* consommateur(void *cid) {
   while(1) {


   }
  return NULL;   
  
}


// fonction main
int main(int argc, char* argv[]) {
   /* Les paramètres du programme sont, dans l’ordre :
      le nombre de producteurs, le nombre de consommateurs
      et la taille du tampon.*/
    
   unsigned nbProducteurs = argv[1];
   unsigned nbConsomateurs = argv[2];
   tampon = malloc(argv[3]);

   const u_int8_t NUMBER_OF_THREADS = nbProducteurs + nbConsomateurs;
   pthread_t tids[NUMBER_OF_THREADS];
   sem_init(&mutex, 0, 1);
   sem_init(&product, 0, 1);

   for (int i = 0; i < nbProducteurs; i++) {
       pthread_create(&tids[i], NULL, producteur, NULL);
   }

   for (int i = 0; i < nbConsomateurs; i++) {
       pthread_create(&tids[i], NULL, consommateur, NULL);
   }

   for (int i = 0; i < NUMBER_OF_THREADS; i++) {
       pthread_join(tids[i], NULL);
   }

   return 0;
}
