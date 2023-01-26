/*
 * Ecole polytechnique de Montreal - GIGL
 * Automne  2022
 * Initlab - part1.c
 * 
 * ajoutez vos noms, prénoms, matricules et votre section de laboratoire
 */

// TODO
// Si besoin, ajouter ici les directives d'inclusion et les déclarations globales
// -------------------------------------------------
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

char* MSG = "Saisissez votre texte suivi de CTRL-D : \n";
char* MSG_ERROR = "Une erreur s'est produite à l'ouverture du fichier \n";

// -------------------------------------------------

int main () {
    // TODO
    int fd;

    if ( (fd = open("./output2.txt", O_TRUNC | O_WRONLY)) == -1) {
        write(2, MSG_ERROR, strlen( MSG_ERROR ));
        return -1;
    }
    
    char buffer[255];

    write(0, MSG, strlen(MSG));

    while (read(1, buffer, 1) != 0) {
        write(fd, buffer, 1);
    }

    close(fd);

    return 0;
}