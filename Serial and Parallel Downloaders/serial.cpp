#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>


void parent() {
  std::vector<std::string> url_vector;
  std::string url;
  std::ifstream url_file("urls.txt");
  if (url_file.is_open()) {
    std::cout << "urls.txt exists!\n";
  }
  else {
    std::cerr << "urls.txt does not exist!\n";
    exit(-1);
  }

  while (!url_file.eof()) {
    url_file >> url;

    if (!url_file.eof()) {
      url_vector.push_back(url);
    }
  }
  url_file.close();

  for (int i = 0; i < url_vector.size(); i++) {
    pid_t pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }

    if (pid == 0) {
      std::string part1 = "log";
      std::string part2 = ".txt";
      std::string fileName = part1 + std::to_string(i + 1) + part2;

      if (execlp("/usr/bin/wget", "wget", url_vector[i].c_str(), "-o", fileName.c_str(), NULL) < 0) {
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
