/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2022
 * Initlab - part2.c
 *
 * ajoutez vos noms, prénoms et matricules
*/
#include <stdio.h>
#include <stdlib.h>
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
// TODO
#include <string.h>
// -------------------------------------------------
void part21 () // On se rend bien compte que write sera executé avant car pas de '\n' qui flusherait le buffer de printf
{
 // TODO
    char* line1 = "77dbcb01f571f1c32e196c3a7d27f62e (printed using write) \n";
    char* line2 = "77dbcb01f571f1c32e196c3a7d27f62e (printed using fprintf)";
    
    for(int i=0 ; i<strlen(line2) ; i++) {
        printf("%c", line2[i]);
    }

    write(0, line1, strlen(line1));
}

void part22 ()
{
 // TODO
    setvbuf(stdout, NULL, _IONBF, 0);

    char* line1 = "77dbcb01f571f1c32e196c3a7d27f62e (printed using write) \n";
    char* line2 = "77dbcb01f571f1c32e196c3a7d27f62e (printed using fprintf)";
    
    for(int i=0 ; i<strlen(line2) ; i++) {
        printf("%c", line2[i]);
    }

    write(0, line1, strlen(line1));

}



int main (int argc, char* argv[])
{
    
    if (argc!=2)
    {   printf("Le programme a un seul paramètre : 1 ou 2\n");
        return 1;
    }
    switch (atoi(argv[1])) {
         case 1:        part21();
                        break;
         case 2:        part22();
                        break;
        default:        printf(" Le paramètre du programme est invalide\n");
                        return 1;
    }
    return 0;
}

