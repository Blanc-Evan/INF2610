/*
 *  part1.c
 * 
 * BLANC Evan, 2079808, groupe lab 4, equipe_58
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

#include "./libprocesslab/libprocesslab.h"

void question1(int choix) {
    char* messagePrintf = "75dbcb01f571f1c32e196c3a7d27f62e (printed using printf)\n";
    char* messageWrite = "75dbcb01f571f1c32e196c3a7d27f62e (printed using write)\n";

    if (choix == 1) {
        // Question 1.1
        for(int i=0; messagePrintf[i] != '\0'; i++) {
            printf("%c", messagePrintf[i]);
        }

        write(STDOUT_FILENO, messageWrite, strlen(messageWrite));
    } else if (choix == 2) {
        // Question 1.2
        char buffer[1024];
        setvbuf(stdout, buffer, _IOFBF, 1024);
        for(int i=0; messagePrintf[i] != '\0'; i++) {
            printf("%c", messagePrintf[i]);
        }

        write(STDOUT_FILENO, messageWrite, strlen(messageWrite));
    }
}