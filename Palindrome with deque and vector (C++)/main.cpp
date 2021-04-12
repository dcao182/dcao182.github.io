// Identifying palindrome strings using a deque
#include <cctype>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

bool palindrome(const std::string& s)
{
    std::deque<char> d;

    // add all the string characters that are in the alphabet to the back of the deque in uppercase
    for(char c : s)
        if(std::isalpha(c))
            d.push_back(std::toupper(c));

    char c1{};
    char c2{};
    // while the deque size is greater than 1
    //      grab front character and back characters of the deque
    //      remove the front and back characters of the deque
    //      compare the front and the back characters of the deque
    //      if they are not the same - return false since it can't be a palindrome
    // if the loop is a success, it is a palindrome, return true
    while(d.size() > 1) {
        c1 = d.front();
        c2 = d.back();
        d.pop_front();
        d.pop_back();
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
    for(const auto& s : stringLibrary) {
        std::cout << std::setw(8) << std::left << palindrome(s)  << s << std::endl;
    }
    std::cout << std::endl;
    return 0;
}