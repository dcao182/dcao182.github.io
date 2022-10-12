#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <iostream>

void parent() {
  std::vector<std::string> UrlVector;
  std::string urlLink;
  // n is the number of URLs
  int n = 0;
  std::ifstream urls("urls.txt");

  if (!urls.is_open()) {
    std::cout << "urls.txt does not exist!" << std::endl;
    exit(-1);
  }
  else {
    std::cerr << "urls.txt does exist!" << std::endl;
  }

  while (!urls.eof()) {
    urls >> urlLink;

    if (!urls.eof())
      UrlVector.push_back(urlLink);
      n++;
  }
  urls.close();


  for (int i = 0; i < n; i++) {
    pid_t pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork Failed");
      exit(-1);
    }

    if (pid == 0) {
      std::string part1 = "log";
      std::string part2 = ".txt";
      std::string fileName = part1 + std::to_string(i + 1) + part2;

      if (execlp("/usr/bin/wget", "wget", UrlVector[i].c_str(), "-o", fileName.c_str(), NULL) < 0) {
        perror("execlp");
        exit(-1);
      }
    }
  }


  for (int i = 0; i < n; i++) {
    std::cout << "Waiting for child number: " << i << " to complete." << std::endl;

    int exitedChildPid = wait(NULL);

    if (exitedChildPid < 0) {
      perror("wait");
      exit(-1);
    }

    std::cout << "Child number: " << i << " complete!" << std::endl;
  }
}

int main() {
  parent();
  return 0;
}
