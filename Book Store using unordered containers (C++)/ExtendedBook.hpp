#pragma once
#include <cstddef>                                                      // size_t
#include <string>
#include <string_view>
#include <unordered_map>

#include "Book.hpp"


class ExtendedBook : public Book
{
  public:
    // Constructors
    ExtendedBook( std::string_view theTitle  = {},
                  std::string_view theAuthor = {},
                  std::string_view theIsbn   = {},
                  double           thePrice  = 0.0 );

    // Queries
    std::size_t numberOfWords   (                          ) const;     // Returns the number of unique words
    std::size_t wordCount       ( const std::string & word ) const;     // Returns the number of occurrences of the given word
    std::string mostFrequentWord(                          ) const;     // Returns the most frequent word, or the empty string if the Book is empty.
    std::size_t maxBucketSize   (                          ) const;     // Returns the size of the hashtable's largest bucket. See the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map

  private:
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// The class should have a single member attribute, of type std::unordered_map which is the C++ Standard Library's
      /// implementation of a hash table, to store the association of words (key) to the number of times a word occurs (value), also
      /// called the word's frequency.

    std::unordered_map<std::string, std::size_t> _frequency;
    /////////////////////// END-TO-DO (1) ////////////////////////////
};
