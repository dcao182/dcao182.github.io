#include <cmath>      // abs()
#include <iomanip>    // quoted()
#include <iostream>
#include <string>
#include <string_view>
#include <utility>    // move()

#include "Book.hpp"

                           namespace    // unnamed, autonomous namespace
{
  // Avoid direct equality comparisons on floating point numbers.
  // Two values are equal if they are "close enough", which is represented by Epsilon.
  // Usually, this is a pretty small number, but since we are dealing with money
  // (only 3 or 3 decimal places) we can be more tolerant.  Two floats are considered equal
  // if they are within EPSILON of each other.

  constexpr auto EPSILON = 2.0E-4;
}    // namespace




// Constructors
Book::Book( std::string_view title, std::string_view author, std::string_view isbn, double price )
  : _isbn( isbn ), _title( title ), _author( author ), _price( price )
{}    // Avoid setting values in constructor's body (when possible)




// Queries/Getters
std::string Book::isbn() const
{
  return _isbn;
}



std::string Book::title() const
{
  return _title;
}



std::string Book::author() const
{
  return _author;
}



double Book::price() const
{
  return _price;
}



// Mutators/Setters
void Book::isbn( std::string_view newIsbn )
{
  _isbn = newIsbn;
}



void Book::title( std::string_view newTitle )
{
  _title = newTitle;
}



void Book::author( std::string_view newAuthor )
{
  _author = newAuthor;
}



void Book::price( double newPrice )
{
  _price = newPrice;
}



// Overloaded insertion & extraction operators
std::istream & operator>>( std::istream & stream, Book & book )
{
  // Reading from streams can go wrong - no permission, wrong types, end of file etc.
  // Minimal exception guarantee says there should be no side affects if an error/exception occurs
  // Do our work in a local object & move it into place at the end if all goes well.
  Book workingItem;

  char delimiter = ',';

  stream >> std::quoted( workingItem._isbn ) >> delimiter
      >> std::quoted( workingItem._title ) >> delimiter
      >> std::quoted( workingItem._author ) >> delimiter
      >> workingItem._price;

  // If all is okay, move workingItem into the book being returned.
  // Copying the info also "works" but move is more efficient.
  // Note this uses Book's move assignment operator
  if( stream ) book = std::move( workingItem );

  return stream;
}




std::ostream & operator<<( std::ostream & stream, const Book & book )
{
  const std::string delimiter = ", ";

  stream << std::quoted( book.isbn() ) << delimiter
         << std::quoted( book._title ) << delimiter
         << std::quoted( book.author() ) << delimiter
         << book.price();

  return stream;
}




// Relational operators
bool operator==( const Book & lhs, const Book & rhs )
{
  // Implement equality in terms of "less than" to enforce identical column priority ordering
  // and floating point epsilon comparison tolerance.  This has the advantage of guaranteeing
  // checking for equality and inequality are consistent. It has the disadvantage of doubling
  // the work because you ahve to check for inequality twice.  2*O(n) vice O(n).
  if constexpr( ( false ) )
  {
    return !( lhs < rhs ) && !( rhs < lhs );
  }
  else
  {
    // Alternate implementation
    return lhs._isbn == rhs._isbn
           && lhs._author == rhs._author
           && lhs._title == rhs._title
           && std::abs( lhs._price - rhs._price ) < EPSILON;
  }
}



bool operator<( const Book & lhs, const Book & rhs )
{
  // Sort by ISBN, Author, Title, then Price
  // C++20's spaceship operator should optimize this algorithm, but for now...
  if( auto result = lhs._isbn.compare( rhs._isbn ); result != 0 ) return result < 0;
  if( auto result = lhs._author.compare( rhs._author ); result != 0 ) return result < 0;
  if( auto result = lhs._title.compare( rhs._title ); result != 0 ) return result < 0;

  if( std::abs( lhs._price - rhs._price ) >= EPSILON ) return lhs._price < rhs._price;

  // At this point, all attributes are equal to each other, so lhs cannot be less than rhs
  return false;
}



bool operator!=( const Book & lhs, const Book & rhs ) { return !( lhs == rhs ); }
bool operator<=( const Book & lhs, const Book & rhs ) { return !( rhs < lhs ); }
bool operator>( const Book & lhs, const Book & rhs ) { return ( rhs < lhs ); }
bool operator>=( const Book & lhs, const Book & rhs ) { return !( lhs < rhs ); }
