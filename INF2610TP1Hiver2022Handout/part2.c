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
    int numberOfProcessusCreated;
    while(wait(&status) > 0) {
      numberOfProcessusCreated+=status;
    }
    registerProc(0, 0, getpid(), getppid());
    execl("/user/bin/ls", "ls -l", NULL);
        if (fork() == 0) {    // Level 1.2
          int processus;
          while(wait(&status) > 0) {
              processus+=status;
          }
          registerProc(1, 2, getpid(), getppid());
            if (fork()) {    // Level2.5
              while(wait(&numberOfProcessusCreated) > 0);
              registerProc(2, 5, getpid(), getppid());
                if (fork()) { // Level2.6
                  while(wait(&numberOfProcessusCreated) > 0);
                  registerProc(2, 6, getpid(), getppid());
                    if (fork()) { // Level2.7
                      while(wait(&numberOfProcessusCreated) > 0);
                      registerProc(2, 7, getpid(), getppid());
                    }
                }
            }
            _exit(processus);
        }
        _exit(numberOfProcessusCreated);
    } else {    // Level 1.1
      int processus;
      while(wait(&status) > 0){
        processus+=status;
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
        _exit(processus);
    }
}
