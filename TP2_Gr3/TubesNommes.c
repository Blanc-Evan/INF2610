// ajouter les directives d'inclusion nécessaires
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>

/**
 * Evan BLANC Groupe 4 2079808
 * 
 */
 * @brief Question 2 : Tubes nommés et redirections
 */
int main() {
    int status;
    mkfifo("tube1", 0660);
    mkfifo("tube2", 0660);
    int fd, ab;
    if(!fork()) { 
        if(!fork()) {
            if(!fork()) { // P1
                int file = open("./In.txt", O_RDONLY);
                fd = open("tube1", O_WRONLY);
                dup2(file, STDIN_FILENO);
                dup2(fd, STDOUT_FILENO);
                close(fd);
                execlp("rev", "rev", NULL);
                exit(0);
            } else { //P2
                fd = open("tube1", O_RDONLY);
                ab = open("tube2", O_WRONLY);
                dup2(fd, STDIN_FILENO);
                dup2(ab, STDOUT_FILENO);
                close(fd);
                close(ab);
                execlp("rev", "rev", NULL);
                exit(0);         
            }
        } else { // P3
            ab = open("tube2", O_RDONLY);
            dup2(ab, STDIN_FILENO);
            close(ab);
            execlp("diff","diff", "-s", '-', "In.txt", NULL);
            exit(0);
        }
    }
    close(fd);
    close(ab);
    return 0;
}
