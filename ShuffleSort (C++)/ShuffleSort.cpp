// Daniel Cao
// This program takes a user defined array of strings, shuffles,
// sorts, and then prints the array.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

const int NELM = 5;

void print_array(std::string the_array[], int size) {
  for (int i = 0; i < size; i++) {
    std::cout << "Index " << i << ": " << the_array[i] << std::endl;
  }
}

void swap(std::string the_array[], int size, int string_a_location, int string_b_location) {
  if (string_a_location > size || string_b_location > size) {
    std::cout << "Out of bounds! Doesn't exist!" << std::endl;
    exit(1);
  }

  std::string temp = the_array[string_a_location];
  the_array[string_a_location] = the_array[string_b_location];
  the_array[string_b_location] = temp;
}

void shuffle_array(std::string the_array[], int size) {
  for(int i = 0; i < size - 1; i++) {
    for(int j = i + 1; j < size; j++) {
        swap(the_array, size, i, j);
    }
  }
}

void selection_sort(std::string the_array[], int size) {
  for(int i = 0; i < size - 1; i++) {
    for(int j = i + 1; j < size; j++) {
      if(the_array[i] > the_array[j]) {
        swap(the_array, size, i, j);
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if(argc < 5) {
    std::cout << "This program requires at least 5 arguments!" << std::endl;
    return 0;
  }

  srand(time(0));

  std::string my_array[NELM];

  for (int i = 0; i < NELM; i++) {
    my_array[i] = argv[i + 1];
  }
  print_array(my_array, NELM);

  shuffle_array(my_array, NELM);

  std::cout << "Shuffled\n";

  print_array(my_array, NELM);

  std::cout << "\n";

  selection_sort(my_array, NELM);

  std::cout << "Sorted\n";

  print_array(my_array, NELM);

  return 0;
}