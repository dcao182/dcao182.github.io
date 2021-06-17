#include <iostream>
#include <cstddef>         // size_t

#include "CheckResults.hpp"
#include "ExtendedBook.hpp"






int main()
{
  Regression::CheckResults affirm(std::cout);

  // Test set 1 - Frankenstein
  {

    ExtendedBook franky( "Frankenstein", "Shelly", "9789998819450" );
    std::cout << "Test results for:\n" << franky << "\n\n";

    affirm.is_equal( "numberOfWords: Frankenstein   ",    7195U, franky.numberOfWords()             );
    affirm.is_equal( "wordCount: Frankenstein       ",      24U, franky.wordCount( "Frankenstein" ) );
    affirm.is_equal( "wordCount: life               ",     114U, franky.wordCount( "life" )         );
    affirm.is_equal( "wordCount: feared             ",      13U, franky.wordCount( "feared" )       );
    affirm.is_equal( "wordCount: the                ",    4187U, franky.wordCount( "the" )          );
    affirm.is_equal( "mostFrequentWord: Frankenstein",    "the", franky.mostFrequentWord()          );

    std::size_t size = franky.maxBucketSize();
    affirm.is_equal( "maxBucketSize: Frankenstein   ", ( size - 5 <= 2 ? size : 6U ), size );   // expecting 5, 6, or 7 to allow a little wiggle room for different library implementations
                                                                                                // Programming note: intentionally using unsigned subtraction allowing negative number to wrap
                                                                                                // around to become very large positive numbers
  }

  std::cout << "\n\n";

  // Test set 2 - Sleepy Hollow
  {
    ExtendedBook sleepyHollow( "Legend of Sleepy Hollow", "Washington Irving", "9789998302938");
    std::cout << "Test results for:\n" << sleepyHollow << "\n\n";

    affirm.is_equal( "numberOfWords: Sleepy Hollow   ",   3231U, sleepyHollow.numberOfWords()        );
    affirm.is_equal( "wordCount: Ichabod             ",     45U, sleepyHollow.wordCount( "Ichabod" ) );
    affirm.is_equal( "wordCount: the                 ",    917U, sleepyHollow.wordCount( "the" )     );
    affirm.is_equal( "mostFrequentWord: Sleepy Hollow",   "the", sleepyHollow.mostFrequentWord()     );

    std::size_t size = sleepyHollow.maxBucketSize();
    affirm.is_equal( "maxBucketSize: Sleepy Hollow   ", ( size - 4 <= 2 ? size : 5U ), size );  // expecting 4, 5, or 6 to allow a little wiggle room for different library implementations
                                                                                                // Programming note: intentionally using unsigned subtraction allowing negative number to wrap
                                                                                                // around to become very large positive numbers
  }

  std::cout << affirm;

  return 0;
}
