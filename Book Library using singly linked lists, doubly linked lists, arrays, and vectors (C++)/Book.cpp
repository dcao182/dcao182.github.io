#include <iomanip>
#include <string>
#include <string_view>
// Includes the quotation keyword

#include "Book.hpp"

// Defines EPSILON in unnamed autonomous namespace
namespace
{
  const double EPSILON = 1.0E-4;
}

// Constructors
// Book::Book puts the Constructor in the scope of class Book
Book::Book( std::string_view isbn,
            std::string_view title,
            std::string_view author,
            double           price )
  : _isbn  ( isbn   ),
    _title ( title  ),
    _author( author ),
    _price ( price  )
{
}

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

// Mutator/Setters
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
  Book              workingItem;
  char delimiter = ',';

  stream >> std::quoted( workingItem._isbn   ) >> delimiter
         >> std::quoted( workingItem._title  ) >> delimiter
         >> std::quoted( workingItem._author ) >> delimiter
         >> workingItem._price;

  if( stream ) book = std::move( workingItem );
  // If all is okay in stream, move workingItem into the returned book.
  // Copying the info also "works" but moving is more efficient.
  // Note this uses Book's move assignment operator

  return stream;
}




std::ostream & operator<<( std::ostream & stream, const Book & book )
{
  const std::string delimiter = ", ";

  stream << std::quoted( book.isbn()   ) << delimiter
         << std::quoted( book.title()  ) << delimiter
         << std::quoted( book.author() ) << delimiter
         << book.price();

  return stream;
}




// Overloaded relational operators
bool operator==( const Book & lhs, const Book & rhs )
{
  return    lhs._isbn   == rhs._isbn
         && lhs._title  == rhs._title
         && lhs._author == rhs._author
         && std::abs( lhs._price - rhs._price ) < EPSILON;
}




bool operator<( const Book & lhs, const Book & rhs )
{
  // if isbn are equal (result == 0), check the next attribute
  // if isbn are not equal, result will be negative or positive, result will be returned
  if( auto result = lhs._isbn.compare( rhs._isbn     ); result != 0 ) return result < 0;
  if( auto result = lhs._title.compare( rhs._title   ); result != 0 ) return result < 0;
  if( auto result = lhs._author.compare( rhs._author ); result != 0 ) return result < 0;
  if( std::abs(lhs._price - rhs._price) >= EPSILON   )                return lhs._price < rhs._price;

  // all attributes are equal after being checked, return false
  return false;
}

bool operator!=( const Book & lhs, const Book & rhs ) { return !( lhs == rhs ); }

bool operator<=( const Book & lhs, const Book & rhs ) { return !( rhs <  lhs ); }

bool operator> ( const Book & lhs, const Book & rhs ) { return  ( rhs <  lhs ); }

bool operator>=( const Book & lhs, const Book & rhs ) { return !( lhs <  rhs ); }
