/*
 * processlab - part1.c
 *
 * Ecole polytechnique de Montreal, GIGL, Automne  2022
 * Blanc, Evan 2079808
 * Mouchahid, Ali 2060842
 */

#include "libprocesslab/libprocesslab.h"

// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

void question1()
{
    int status = 0;
    int processesCreated = 0;
    if (!fork())
    { // Level 1.1
        if (!fork())
        { // Level 2.1
            while (wait(&status) > 0)
                processesCreated++; // On attend la fin de tous les fils et on incrémente
            registerProc(2, 1, getpid(), getppid());
            processesCreated += status; // On y ajoute les fils créés par ses fils
            exit(processesCreated);     // On retourne le nombre de fils créés par ce processus
        }

        while (wait(&status) > 0)
            processesCreated++;
        registerProc(1, 1, getpid(), getppid());
        processesCreated += status;
        exit(processesCreated);
    }
    else
    { // Level 0
        if (!fork())
        { // Level 1.2
            if (!fork())
            { // Level 2.2
                while (wait(&status) > 0)
                    processesCreated++;
                registerProc(2, 2, getpid(), getppid());
                processesCreated += status;
                exit(processesCreated);
            }

            while (wait(&status) > 0)
                processesCreated++;
            registerProc(1, 2, getpid(), getppid());
            processesCreated += status;
            exit(processesCreated);
        }
        else
        { // Level 0
            if (!fork())
            { // Level 1.3
                if (!fork())
                { // Level 2.3
                    while (wait(&status) > 0)
                        processesCreated++;
                    registerProc(2, 3, getpid(), getppid());
                    processesCreated += status;
                    exit(processesCreated);
                }
                if (!fork())
                { // Level 2.4
                    while (wait(&status) > 0)
                        processesCreated++;
                    registerProc(2, 4, getpid(), getppid());
                    processesCreated += status;
                    exit(processesCreated);
                }
                if (!fork())
                { // Level 2.5
                    while (wait(&status) > 0)
                        processesCreated++;
                    registerProc(2, 5, getpid(), getppid());
                    processesCreated += status;
                    exit(processesCreated);
                }
                if (!fork())
                { // Level 2.6
                    while (wait(&status) > 0)
                        processesCreated++;
                    registerProc(2, 6, getpid(), getppid());
                    processesCreated += status;
                    exit(processesCreated);
                }
                while (wait(&status) > 0)
                    processesCreated++;
                registerProc(1, 3, getpid(), getppid());
                processesCreated += status;
                exit(processesCreated);
            }
        }
        while (wait(&status) > 0)
            processesCreated++;
        registerProc(0, 0, getpid(), getppid());
        processesCreated += status;
        printf("Processes created: %d\n", processesCreated);
        printProcRegistrations();
        execl("/user/bin/ls", "ls -l", NULL);
    }
}
