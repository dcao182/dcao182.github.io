## Daniel Cao
## 0074
## dcao182@csu.fullerton.edu

# In order to run the program, simply open the python program file using Visual Studio Code.
# Once the python program is opened in Visual Studio Code, simply right click anywhere in the code,
# and click "Run Python File in Terminal."
# The program shall run in the terminal asking for input of two words.

# The output should look like the following:
# Welcome to Edit Distance Demonstration.

# Please input two words for the edit distance: 

# The first word: evaluation
# The second word: elution

# The matrix:
#     0   1   2   3   4   5   6   7   8
# -----------------------------------
# 0 |   0 : 1 : 2 : 3 : 4 : 5 : 6 : 7 :

# -----------------------------------
# 1 |   1 : 0 : 1 : 2 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 2 |   2 : 1 : 1 : 2 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 3 |   3 : 2 : 2 : 2 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 4 |   4 : 3 : 2 : 3 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 5 |   5 : 4 : 3 : 2 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 6 |   6 : 5 : 4 : 3 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 7 |   7 : 6 : 5 : 4 : 3 : 4 : 5 : 6 :

# -----------------------------------
# 8 |   8 : 7 : 6 : 5 : 4 : 3 : 4 : 5 :

# -----------------------------------
# 9 |   9 : 8 : 7 : 6 : 5 : 4 : 3 : 4 :

# -----------------------------------
# 10 |   10 : 9 : 8 : 7 : 6 : 5 : 4 : 3 :

# -----------------------------------

# The edit distance is : 3.0

# Alignment is:
# evaluation
# e__lu_tion

import numpy as np
from difflib import ndiff



def printDistances(distances, word1_length, word2_length):
    # Prints the top row of index integers on top of the matrix
    indexRow = "      "
    for i in range(word1_length - 1):
        indexRow += str(i) + "   "
    print(indexRow)
    print("  -----------------------------------")
    
    currentRow = ""
    for r in range(word1_length + 1):
        # Prints the column of index integers to the left of the matrix
        currentRow += str(r) + " |   "
        for c in range(word2_length + 1):
            # Prints the current row of computed values in dynamic programming array
            currentRow += str(int(distances[r][c])) + " : "
        print(currentRow)
        print()
        print("  -----------------------------------")
        currentRow = ""
        
        
        
def calculate_editdistance(word1, word2):
    word1_len = len(word1)
    word2_len = len(word2)
    
    # Initialize matrix to all zeroes
    distances = np.zeros((word1_len + 1, word2_len + 1))

     # Initialize top row of matrix
    for i in range(word1_len + 1):
        distances[i][0] = i
    
    # Initialize left most column of matrix
    for j in range(word2_len + 1):
        distances[0][j] = j

            
    a = 0
    b = 0
    c = 0    
    # Start filling the memoization array
    # Loop second word
    for i in range(1, word1_len + 1):
        
        # Compare each char to each char in first word
        for j in range(1, word2_len + 1):
            
            # if i is the first column
            if i == 0:
                distances[i][j] = j
            
            # if j is the left most column
            elif j == 0:
                distances[i][j] = i
            
            # if we find a character match in both words
            # we have a match, take previous calculated value from diagonal in matrix to current cell in matrix
            # else, add 1 to any previously calculated value and store the minimum in current cell
            elif word1[i - 1] == word2[j - 1]:
                distances[i][j] = distances[i - 1][j - 1]
            
            else:
                distances[i][j] = 1 + min(distances[i][j - 1], distances[i - 1][j], distances[i - 1][j - 1])
    
    ## Output matrix of calculation
    print("The matrix: ")
    printDistances(distances, word1_len, word2_len)
    print()
    
    # The edit distance will be stored in the last cell in the matrix
    # Bottom right cell of the matrix
    print("The edit distance is : " + str(distances[word1_len][word2_len]))
    print()
    
    

## Output matrix of alignment that verifies edit distance
def alignment(word1, word2):
    result = ""
    position = 0
    removed = 0
    
    # for each indifference in both words
    for i in ndiff(word1, word2):
        # test if first word has insert/delete penalty
        if position < len(word1) and word1[position] == i[2]:
            position += 1
            result += i[2]
            
            if i[0] == "_":
                removed += 1
            continue
        else:
            if removed > 0:
                removed -= 1
            else:
                result += "_"
    print(result)

if __name__ == '__main__':
    print("Welcome to Edit Distance Demonstration.")
    print()
    print("Please input two words for the edit distance: ")
    print()
    word1 = str(input("The first word: "))
    word2 = str(input("The second word: "))
    print()
    
    calculate_editdistance(word1, word2)
    
    print("Alignment is: ")
    alignment(word1, word2)
    alignment(word2, word1)