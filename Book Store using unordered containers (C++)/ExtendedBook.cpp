#include <fstream>
#include <iostream>
#include <locale>    // tolower()
#include <string>
#include <string_view>

#include "ExtendedBook.hpp"


namespace
{
  // Non-member helper function
  std::string sanitize( const std::string & word )
  {
    constexpr char     bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";    // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );              // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();    // if the word contains only bad characters ...

    std::size_t count    = 0;                                    // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );    // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1;    // number of characters to use in results

    auto result = word.substr( startIndex, count );              // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );    // convert to lower case

    return result;
  }
}    // namespace







///////////////////////// TO-DO (1) //////////////////////////////
/// Implement ExtendedBook's constructor.  Avoid setting the base class's attributes within the body of this function.  Instead,
/// be sure to use a Constructor Member Initialization List to construct the base class passing the proper values. Look up member
/// initialization if you don't remember what that is.  See
///  - https://en.cppreference.com/w/cpp/language/constructor and
///  - https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
///
///
/// This function constructs an extended book by first constructing the base class and then populating a word frequency table as
/// the book's content is read.  In the function's body:
///   i  Open the disk file containing this book's content as an input file stream.  The name of the disk file, if it exists, is
///      ISBN.bok where ISBN is the book's 10 or 13 digit ISBN.  For example, 9789999275842.bok contains the text of book with
///      an ISBN of "9789999275842" titled "Billboard Music Week (1st edition)" by "Joel Whitburn".
///  ii. Read from the input stream a single word at a time (delimited by whitespace as defined in standard C++) until end of
///      file, and for each word read
/// iii. increment the number of times this (sanitized) word has appeared in the text if it has been seen before, otherwise add
///      it to the table and initialize the frequency.
///
/// Constraint: Only "sanitized" words should be added to the frequency table. For example, leading and trailing punctuation,
/// parentheses, brackets, etc. should be removed, but intra - word punctuation should remain. A working sanitize function has
/// been provided.

ExtendedBook::ExtendedBook( std::string_view theTitle, std::string_view theAuthor, std::string_view theIsbn, double thePrice )
  : Book( theTitle, theAuthor, theIsbn, thePrice )
{
  std::string diskFile = Book::isbn();
  diskFile += ".bok";
  // open the disk file
  std::ifstream fin( diskFile );

  std::string word;

  // read from input stream, one word at a time
  while( fin >> word )
  {
    // sanitize word
    word = sanitize( word );

    // search for word in unordered container
    auto search = _frequency.find( word );
    // if word exists in container
    if( search != _frequency.end() )
    {
      // increment the value for the word
      search->second++;
    }
    else
    {
      // if word is not in the frequency container,
      // insert the word and initialize it to 1
      _frequency[word] = 1;
    }
  }
}
/////////////////////// END-TO-DO (1) ////////////////////////////



///////////////////////// TO-DO (2) //////////////////////////////
/// Implement numberOfWords - This function takes no arguments and returns the number of unique words.
std::size_t ExtendedBook::numberOfWords() const
{
  std::size_t size = 0;
  for( auto it = _frequency.begin(); it != _frequency.end(); ++it )
  {
    ++size;
  }
  return size;
}
/////////////////////// END-TO-DO (2) ////////////////////////////



///////////////////////// TO-DO (3) //////////////////////////////
/// Implement wordCount - This function takes a constant reference to a standard string as a parameter and returns the frequency
/// of occurrence of the that sanitized word.

std::size_t ExtendedBook::wordCount( const std::string & word ) const
{
  // make sure the word is sanitized
  std::string currentWord = sanitize( word );

  // return word count for the word
  return _frequency.at( currentWord );
}
/////////////////////// END-TO-DO (3) ////////////////////////////



///////////////////////// TO-DO (4) //////////////////////////////
/// Implement mostFrequentWord - This function takes no arguments and returns the most frequent word.
std::string ExtendedBook::mostFrequentWord() const
{
  std::size_t max = 0;
  std::string currentWord;
  auto        word = _frequency.begin();

  while( word != _frequency.end() )
  {
    // for each word in container, if word count > max, set word count to max
    if( word->second > max )
    {
      max         = word->second;
      currentWord = word->first;
    }
    ++word;
  }
  return currentWord;
}
/////////////////////// END-TO-DO (4) ////////////////////////////




///////////////////////// TO-DO (5) //////////////////////////////
/// Implement maxBucketSize - This function takes no arguments and returns the size of the largest bucket in the hash table
///
/// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map

std::size_t ExtendedBook::maxBucketSize() const
{
  std::size_t largestBucket = 0;
  std::size_t currentBucketSize = 0;
  std::size_t bucketCount       = _frequency.bucket_count();

  // for each bucket in hash table
  for( std::size_t i = 0; i < bucketCount; ++i )
  {
    // size of bucket at index i in hash table
    currentBucketSize = _frequency.bucket_size( i );
    // if the current bucket size is greater than the size of the largest bucket
    if( currentBucketSize > largestBucket )
    {
      // assign current bucket size as the largest bucket size
      largestBucket = currentBucketSize;
    }
  }
  return largestBucket;
}
/////////////////////// END-TO-DO (5) ////////////////////////////
