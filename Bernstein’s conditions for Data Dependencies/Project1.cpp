#include <iostream>
#include <string>

/*
Group Members:
Daniel Cao
Andy Cao


INPUT:
Instruction:
I1: d = b + ( c – d / e)

Block:
I2: b = b * c
I3: c = c – a
I4: a = a + b * c

OUTPUT:
Then the output should be:
a = a + b * c

Pseudocode:
Can I1 be parallel with I2?
OUT(I1) ∩ IN(I2) = d ∩ {b, c} = empty set
IN(I1) ∩ OUT(I2) = {b, c, d, e} ∩ {b} != empty set
OUT(I1) ∩ OUT(I2) = d ∩ b = empty set

Therefore, I1 CANNOT be parallel with I2

Can I1 be parallel with I3?
OUT(I1) ∩ IN(I3) = d ∩ {c, a} = empty set
IN(I1) ∩ OUT(I3) = {b, c, d, e} ∩ {c} != empty set
OUT(I1) ∩ OUT(I3) = d ∩ c = empty set

Therefore, I1 CANNOT be in parallel with I3

Can I1 be in parallel with I4?
OUT(I1) ∩  IN(I4) = d ∩ {a, b, c} = empty set
IN(I1) ∩ OUT(I4) = {b, c, d, e} ∩ {a} = empty set
OUT(I1) ∩ OUT(I4) = d ∩ a = empty set

Therefore, I1 CAN be in parallel with I4


if output of the simple instruction does not have an intersection with input of instruction n then it has an empty set
if input of the simple instruction does not have an intersection with output of instruction n then it has an empty set
if output of the simple instruction does not have an intersection with output of instruction n then it has an empty set
if all 3 conditions result in empty sets, then true, the simple instruction can run in parallel with instruction n
*/

bool algorithm_calculate(std::string &simple, std::string &block) {
    // Let simple be the simple instruction
    // Let block be an instruction coming from the block of instructions

    // Keep track of empty sets
    // Assume all are empty sets represented by 0 in result
    // If there is an intersection, we switch 0 in result to 1 to indicate no empty set
    int result_size = 3;
    int result[result_size] = {0, 0, 0};

    // Can I1 be parallel with the current Block instruction?
    // i starts at 4 to begin at character after the equal sign in a block instruction
    // we begin checking for intersections 
    char output_i1 = simple[0];
    for(char &c : block) {
        // OUT(I1) ∩ IN(Block instruction)
        if (isalpha(c) && isalpha(output_i1)) {
            if (c == output_i1) {
                result[0] = 1;
                break;
            }
        }
    }

    char output_i2 = block[0];
    // IN(I1) ∩ OUT(Block instruction)
    for(char &c : simple) {
        if (isalpha(c) && isalpha(output_i2)) {
            if (c == output_i2) {
                result[1] = 1;
                break;
            }
        }
    }

    // OUT(I1) ∩ OUT(Block instruction)
    if (output_i1 == output_i2) {
        if (isalpha(output_i1) && isalpha(output_i2)) {
            result[2] = 1;
        }
    }

    // we check for empty sets
    // if all conditions are NOT empty sets, return false
    // otherwise, all conditions are empty sets, return true
    for (int i = 0; i < result_size; i++) {
        if (result[i] == 1) {
            return false;
        }
    }
    return true;
}



bool algorithm_verify(std::string &instruction1, std::string &instruction2) {
    int result_size = 3;
    int result[result_size] = {0, 0, 0};

    // Can I1 be parallel with the current Block instruction?
    // i starts at 4 to begin at character after the equal sign in a block instruction
    // we begin checking for intersections 
    char output_i1 = instruction1[0];
    for(char &c : instruction2) {
        // OUT(I1) ∩ IN(Block instruction)
        // Make sure character is a letter and not an operator or whitespace
        if (isalpha(c) && isalpha(output_i1)) {
            if (c == output_i1) {
                result[0] = 1;
                break;
            }
        }
    }

    char output_i2 = instruction2[0];
    // IN(I1) ∩ OUT(Block instruction)
    for(char &c : instruction1) {
        if (isalpha(c) && isalpha(output_i2)) {
            if (c == output_i2) {
                result[1] = 1;
                break;
            }
        }
    }

    // OUT(I1) ∩ OUT(Block instruction)
    if (output_i1 == output_i2) {
        if (isalpha(output_i1) && isalpha(output_i2)) {
            result[2] = 1;
        }
    }

    // we check for empty sets
    // if all conditions are NOT empty sets, return false
    // otherwise, all conditions are empty sets, return true
    for (int i = 0; i < result_size; i++) {
        if (result[i] == 1) {
            return false;
        }
    }
    return true;
}



int main() {
    // Simple instruction
    std::string d = "d = b + ( c - d / e )";

    // Block of instructions
    std::string b = "b = b * c";
    std::string c = "c = c - a";
    std::string a = "a = a + b * c";

    // size of Block instructions
    int n = 3;

    std::string block1[n] = {"b = b * c", "c = c - a", "a = a + b * c"};

    // Loop through block of instructions
    // Run algorithm on the simple instruction, d, with each instruction in the block
    // If the algorithm returns true, the simple instruction can be run with the current block instruction
    // Algorithm Calculate
    for (int i = 0; i < n; i++) {
        bool result_calculate = algorithm_calculate(d, block1[i]);
        if (result_calculate == true) {
            std::cout << block1[i] << std::endl;
        }
    }



    bool result_verify = false;
    int count = 0;
    // Block of instructions for Algorithm Verify
    std::string block2[n] = {"b = b * c", "d = c - a", "a = a + b * c"};
    // Algorithm Verify
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            result_verify = algorithm_verify(block2[i], block2[j]);

            if (result_verify == true) {
                std::cout << "The pairs of instructions that can be executed in parallel are:" << std::endl;
                std::cout << "( " + block2[i] + ", " + block2[j] + " )" << std::endl;
                break;
            }
        }
        count++;

        if (count == n && result_verify == false) {
            std::cout << "The pairs of instructions that can be executed in parallel are:" << std::endl;
            std::cout << "NONE" << std::endl;
        } 
    }



    std::string block3[n] {"a = a * b * c", "c = c - a", "a = a + b * c"};
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            result_verify = algorithm_verify(block3[i], block3[j]);

            if (result_verify == true) {
                std::cout << "The pairs of instructions that can be executed in parallel are:" << std::endl;
                std::cout << "( " + block3[i] + ", " + block3[j] + " )" << std::endl;
                break;
            }
        }
        count++;

        if (count == n && result_verify == false) {
            std::cout << "The pairs of instructions that can be executed in parallel are:" << std::endl;
            std::cout << "NONE" << std::endl;
        }
    }

    return 0;
}