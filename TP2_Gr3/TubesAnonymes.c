// ajouter les directives d'inclusion nécessaires
#include <unistd.h>
#include<stdio.h>
#include <fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

/**
 * Evan BLANC Groupe 4 2079808
 * 
 */
 * @brief Question 1 : Tubes anonymes et redirections
 */
int main() {
    int fd[2];
    int ab[2];

    if (pipe(fd) == -1 && pipe(ab) == -1) { 
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    
    if(!fork()) { 
        if(!fork()) {
            if(!fork()) { // P1
                int file = open("./In.txt", O_RDONLY);
                dup2(file, STDIN_FILENO);
                dup2(fd[1], STDOUT_FILENO);
                execlp("rev", "rev", NULL);
                exit(0);
            } else { //P2
                dup2(fd[0], STDIN_FILENO);
                dup2(ab[1], STDOUT_FILENO);
                execlp("rev", "rev", NULL);
                exit(0);         
            }
        } else { // P3
            dup2(ab[0], STDIN_FILENO);
            execlp("diff","diff", "-s", '-', "In.txt", NULL);
            exit(0);
        }
    }
    close(fd[0]);
    close(fd[1]);
    close(ab[0]);
    close(ab[1]);
    return 0;
}
