/*
 * processlab - part2.c
 *
 * Ecole polytechnique de Montreal,Hiver  2022
 * BLANC Evan, 2079808, groupe lab 4, equipe_58
*/

#include "libprocesslab/libprocesslab.h"


// TODO
// Si besoin, ajouter ici les directives d'inclusion
// -------------------------------------------------

// -------------------------------------------------

void question2( )   {
  int status;
    if(fork()) {    // Level 0
    int numberOfProcessesCreated;
    while(wait(&status) > 0) {
      numberOfProcessesCreated+=status;
    }
    registerProc(0, 0, getpid(), getppid());
    execl("/user/bin/ls", "ls -l", NULL);
        if (fork() == 0) {    // Level 1.2
          int process;
          while(wait(&status) > 0) {
              process+=status;
          }
          registerProc(1, 2, getpid(), getppid());
            if (fork()) {    // Level2.5
              while(wait(&numberOfProcessesCreated) > 0);
              registerProc(2, 5, getpid(), getppid());
                if (fork()) { // Level2.6
                  while(wait(&numberOfProcessesCreated) > 0);
                  registerProc(2, 6, getpid(), getppid());
                    if (fork()) { // Level2.7
                      while(wait(&numberOfProcessesCreated) > 0);
                      registerProc(2, 7, getpid(), getppid());
                    }
                }
            }
            _exit(process);
        }
        _exit(numberOfProcessesCreated);
    } else {    // Level 1.1
      int process;
      while(wait(&status) > 0){
        process+=status;
      }
      registerProc(1, 1, getpid(), getppid());
        if (fork()) {    // Level2.1
          registerProc(2, 1, getpid(), getppid());
          _exit(1);
            if (fork()) { // Level2.2
              registerProc(2, 2, getpid(), getppid());
              _exit(1);
                if (fork()) { // Level2.3
                  registerProc(2, 3, getpid(), getppid());
                  _exit(1);
                    if (fork()) {   // Level2.4
                      registerProc(2, 4, getpid(), getppid());
                      _exit(1);
                    }
                }
            }
        }
        _exit(process);
    }
}
