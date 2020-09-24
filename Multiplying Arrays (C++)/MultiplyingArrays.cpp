#include <iostream>

int * apply_all(const int *const arr1, int size1, const int *const arr2, int size2);
void print(const int *const array, int size);

int * apply_all(const int *const arr1, int size1, const int *const arr2, int size2) {
    int *new_array {};
    
    new_array = new int[size1 * size2];
    
    int position = 0;
    for (int i = 0; i < size2; i++) {
        for (int j = 0; j < size1; j++) {
            new_array[position] = arr1[j] * arr2[i];
            position++;
        }
    }
    return new_array;
}

void print(const int *const arr, int size) {
    std::cout << "[ ";
    for (size_t i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout <<  "]";
    std::cout << std::endl;
}

int main() {
    const size_t array1_size {5};
    const size_t array2_size {3};
    
    int array1[] {1,2,3,4,5};
    int array2[] {10,20,30};
    
    std::cout << "Array 1: " ;
    print(array1,array1_size);
    
    std::cout << "Array 2: " ;
    print(array2,array2_size);
    
    int *results = apply_all(array1, array1_size, array2, array2_size);
    int results_size {array1_size * array2_size};
    
    std::cout << "Result: " ;
    print(results,results_size);
    
    delete [] results;
    std::cout << std::endl;
    return 0;
}

