#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

void parent() {
  char cmd[10];

  while (true) {
    printf("cmd>");
    std::cin >> cmd;

    if (strcmp(cmd, "exit") == 0) {
      exit(0);
    }

    pid_t pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }

    if (pid == 0) {
      char filePath[30] = "/usr/bin/";
      strcat(filePath, cmd);

      if (execlp(filePath, cmd, NULL) < 0) {
        perror("execlp");
        exit(-1);
      }
    }
    else {
      printf("Inside the parent: %d\n", pid);

      int exitedChildPid = wait(NULL);

      if (exitedChildPid < 0) {
        perror("wait");
        exit(-1);
      }

      printf("Child complete: %d\n", exitedChildPid);
    }
  }
}

int main() {
  parent();
  return 0;
}
