#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define ARRAY_SIZE 100
struct node * BSTroot = NULL;
pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

struct node {
  int value;
  struct node *left, *right;
};

struct node * BST(int item) {
  struct node * self = (struct node *)malloc(sizeof(struct node));
  self->value = item;
  self->left = NULL;
  self->right = NULL;
  return self;
}

struct node * insert(struct node *node, int value) {
  if (node == NULL) {
    return BST(value);
  }

  if (value < node->value) {
    node->left = insert(node->left, value);
  }
  else {
    node->right = insert(node->right, value);
  }
  return node;
}

void printInorder(struct node *root) {
  if (root != NULL) {
    // Print tree in order traversal
    printInorder(root->left);

    std::cout << root->value << " ";

    printInorder(root->right);
  }
}

void * genRandNum (void * data) {
  int randomNumbersArray[ARRAY_SIZE];
  // generate 100 numbers into an array
  for (int i = 0; i < ARRAY_SIZE; i++) {
	     randomNumbersArray[i] = rand() % 100000;
	}

  // Semaphore/Mutex
  if (pthread_mutex_lock(&myMutex) != 0) {
    perror("pthread_mutex_lock");
    exit(-1);
  }
  // Critical section for inserting values into BST
  for (int j = 0; j < ARRAY_SIZE; j++) {
    BSTroot = insert(BSTroot, randomNumbersArray[j]);
  }

  if (pthread_mutex_unlock(&myMutex) != 0) {
      perror("pthread_mutex_unlock");
      exit(-1);
  }

  pthread_exit(0);
}

// Main thread
int main(int argc, char* argv[]) {
  int numThreads = atoi(argv[1]);
  pthread_t tids[numThreads];

  for (int i = 0; i < numThreads; i++) {
    if (pthread_create(&tids[i], NULL, genRandNum, NULL) != 0) {
      perror("pthread_create");
      exit(-1);
    }
  }

  for (int j = 0; j < numThreads; j++) {
    if (pthread_join(tids[j], NULL) != 0) {
      perror("pthread_join");
      exit(-1);
    }
  }

  printInorder(BSTroot);
  return 0;
}
