// Determine if a string is a palindrome using a queue and a stack

#include <cctype>
#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

bool palindrome(const std::string& s)
{
    std::stack<char> stk;
    std::queue<char> q;

    // add all characters in the alphabet to the back of the queue in uppercase
    // push all characters that are alphabet on the stack
    
    for(char c : s)
        if(std::isalpha(c)) {
            c = std::toupper(c);
            q.push(c);
            stk.push(c);
        }

    char c1{};
    char c2{};    
    
    // while the queue is not empty
    //      grab front character of queue & top character of stack
    //      remove front character of queue & top character of stack
    //      compare the two characters, if they are not the same, it is not a palindrome, return false
    // if the loop completes then it is a palindrome, return true
    while(!q.empty()) {
        c1 = q.front();
        q.pop();
        c2 = stk.top();
        stk.pop();
        if(c1 != c2)
            return false;
    }
    return true;
}

int main()
{
    std::vector<std::string> stringLibrary{ "a", "aa", "aba", "abba", "abbcbba", "ab", "abc", "radar", "bob", "ana",
        "avid diva", "Amore, Roma", "A Toyota's a toyota", "A Santa at NASA", "C++",
        "A man, a plan, a cat, a ham, a yak, a yam, a hat, a canal-Panama!", "This is a palindrome", "palindrome" };
   
    std::cout << std::boolalpha;
    std::cout << std::setw(8) << std::left << "Result" << "String" << std::endl;
    // prints out all palindromes in the string library vector
    for(const auto& s : stringLibrary) {
        std::cout << std::setw(8) << std::left << palindrome(s)  << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
