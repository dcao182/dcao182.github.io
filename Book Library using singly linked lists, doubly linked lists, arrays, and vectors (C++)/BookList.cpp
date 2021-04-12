#include <algorithm>    // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cstddef>      // size_t
#include <initializer_list>
#include <iomanip>      // setw()
#include <iterator>     // distance(), next()
#include <stdexcept>    // logic_error
#include <string>

#include "Book.hpp"
#include "BookList.hpp"

#define exception_location "\n detected in function \"" + std::string(_func_) + "\"" \
                           "\n at line " + std::to_string(_LINE_) +
                           "\n in file \"" _FILE_ "\""




/*******************************************************************************
**  Private implementations, types, and objects
*******************************************************************************/
bool BookList::containersAreConsistant() const
{
  // Sizes of all containers must be equal to each other
  if(    _books_array_size != _books_vector.size()
      || _books_array_size != _books_dl_list.size()
      || _books_array_size !=  books_sl_list_size() ) return false;

  // Element content and order must be equal to each other
  auto current_array_position   = _books_array  .cbegin();
  auto current_vector_position  = _books_vector .cbegin();
  auto current_dl_list_position = _books_dl_list.cbegin();
  auto current_sl_list_position = _books_sl_list.cbegin();

  while( current_vector_position != _books_vector.cend() )
  {
    if(    *current_array_position != *current_vector_position
        || *current_array_position != *current_dl_list_position
        || *current_array_position != *current_sl_list_position ) return false;

    // Advance the iterators to the next element in unison
    ++current_array_position;
    ++current_vector_position;
    ++current_dl_list_position;
    ++current_sl_list_position;
  }

  return true;
}




// Calculate the size of the singly linked list on demand
std::size_t BookList::books_sl_list_size() const
{
  if constexpr( (true) )
    return std::distance( _books_sl_list.cbegin(), _books_sl_list.cend() ); // traverses the singly linked list from beginning to end
  else
  {
    // another approach
    std::size_t size = 0;
    for( auto current = _books_sl_list.cbegin(); current != _books_sl_list.cend(); ++size, ++current )
    return size;
  }
}











/*******************************************************************************
**  Constructors, destructor, and assignment operators
*******************************************************************************/
// Rule of 6
BookList::BookList()                                     = default;

BookList::BookList( const BookList  & other )            = default;
BookList::BookList(       BookList && other )            = default;

BookList & BookList::operator=( BookList    rhs )        { swap( rhs ); return *this; }
BookList & BookList::operator=( BookList && rhs )        = default;

BookList::~BookList()                                    = default;



BookList::BookList( const std::initializer_list<Book> & initList )
  : _books_vector ( initList.begin(), initList.end() ),
    _books_dl_list( initList.begin(), initList.end() ),
    _books_sl_list( initList.begin(), initList.end() )
{
  // Unlike the other containers that are expandable, the array has a fixed capacity N.  Copy only the first N elements of the
  // initialization list into the array.
  for( auto p = initList.begin();  _books_array_size < _books_array.size()  &&  p != initList.end();   ++_books_array_size, ++p)
  {
    _books_array[_books_array_size] = *p;
  }
}



BookList & BookList::operator+=( const std::initializer_list<Book> & rhs )
{
  // Concatenate the right hand side book list of books to this list by repeatedly inserting at the bottom of this book list.
  for( const auto & book : rhs ) 
    insert( book, Position::BOTTOM );

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}



BookList & BookList::operator+=( const BookList & rhs )
{
    /// Concatenate the right hand side book list of books to this list by repeatedly inserting at the bottom of this book list.
    /// All the rhs containers (array, vector, list, and forward_list) contain the same information, so pick just one to traverse.
    /// Walk the container you picked inserting its books to the bottom of this book list.
  for( const auto & book: rhs._books_sl_list )
    insert( book, Position::BOTTOM );

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
  return *this;
}







/*******************************************************************************
**  Queries
*******************************************************************************/
std::size_t BookList::size() const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  return _books_vector.size();
}



std::size_t BookList::find( const Book & book ) const
{
  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

    /// Locate the book in this book list and return the zero-based position of that book.  If the book does not exist, return the
    /// size of this book list as an indicator the book does not exist.
  if constexpr( (true) )
  {
    // get the iterator of the book
    return std::find( _books_vector.cbegin(), _books_vector.cend(), book ) - _books_vector.cbegin();
    // subtract to convert iterator to offset
  }
  else
  {
    // alternative implementation
    for( std::size_t offset = 0; offset < _books_vector.size(); ++offset ) {
      if( _books_vector[offset] == book )
        return offset;
    }
    return _books_vector.size();
  }
}












/*******************************************************************************
**  Mutators
*******************************************************************************/
void BookList::insert( const Book & book, Position position )
{
  // Convert the TOP and BOTTOM enumerations to an offset and delegate the work
  if     ( position == Position::TOP    )  insert( book, 0      );
  else if( position == Position::BOTTOM )  insert( book, size() );
  else throw std::logic_error( "Unexpected insertion position" exception_location );  // Programmer error.  Should never hit this!
}



void BookList::insert( const Book & book, std::size_t offsetFromTop )       // insert new book at offsetFromTop, which places it before the current book at offsetFromTop
{
  // Validate offset parameter before attempting the insertion.  std::size_t is an unsigned type, so no need to check for negative
  // offsets, and an offset equal to the size of the list says to insert at the end (bottom) of the list.  Anything greater than the
  // current size is an error.
  if( offsetFromTop > size() ) throw InvalidOffset_Ex( "Insertion position beyond end of current list size" exception_location );


    /// Silently discard duplicate items from getting added to the book list.  If the to-be-inserted book is already in the list,
    /// simply return.
  if( find( book ) != size() ) return;





  // Inserting into the book list means you insert the book into each of the containers (array, vector, list, and forward_list).
  // Because the data structure concept is different for each container, the way a book gets inserted is a little different for
  // each.  You are to insert the book into each container such that the ordering of all the containers is the same.  A check is
  // made at the end of this function to verify the contents of all four containers are indeed the same.


  /**********  Insert into array  ***********************/
  {
    std::move_backward( _books_array.begin() + offsetFromTop,
                        _books_array.begin() + _books_array_size,
                        _books_array.begin() + _books_array_size + 1 );

    // insert the book and increment size
    _books_array[offsetFromTop] = book;
    ++_books_array_size;
  }  // Insert into array



  /**********  Insert into vector  **********************/
  {
    _books_vector.insert( std::next( _books_vector.begin() + offsetFromTop ), book );
  } // Insert into vector



  /**********  Insert into doubly linked list  **********/
  {
    _books_dl_list.insert( std::next( _books_dl_list.begin(), offsetFromTop ), book );
  } // Insert into doubly linked list



  /**********  Insert into singly linked list  **********/
  {
    _books_sl_list.insert_after( std::next( _books_sl_list.before_begin(), offsetFromTop ), book );
  } // Insert into singly linked list

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
} // insert( const Book & book, std::size_t offsetFromTop )



void BookList::remove( const Book & book )
{
  remove( find( book ) );
}



void BookList::remove( std::size_t offsetFromTop )
{
  // Removing from the book list means you remove the book from each of the containers (array, vector, list, and forward_list).
  // Because the data structure concept is different for each container, the way an book gets removed is a little different for
  // each.  You are to remove the book from each container such that the ordering of all the containers is the same.  A check is
  // made at the end of this function to verify the contents of all four containers are indeed the same.

  if( offsetFromTop >= size() ) return;                                            // no change occurs if (zero-based) offsetFromTop >= size()

  /**********  Remove from array  ***********************/
  {
    std::move( _books_array.begin() + offsetFromTop + 1,
               _books_array.begin() + _books_array_size,
               _books_array.begin() + offsetFromTop );)
    --_books_array_size;
    _books_array[_books_array_size] = {};
  } // Remove from array



  /**********  Remove from vector  **********************/
  {
    _books_vector.erase( _books_vector.begin() + offsetFromTop );
  } // Remove from vector



  /**********  Remove from doubly linked list  **********/
  {
    _books_dl_list.erase( std::next( _books_dl_list.begin(), offsetFromTop) );
  } // Remove from doubly linked list



  /**********  Remove from singly linked list  **********/
  {
    _books_sl_list.erase_after( std::next( _books_sl_list.before_begin(), offsetFromTop ) );
  } // Remove from singly linked list

  // Verify the internal book list state is still consistent amongst the four containers
  if( !containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );
} // remove( std::size_t offsetFromTop )



void BookList::moveToTop( const Book & book )
{
  if( auto offset = find( book ); offset != size() )
  {
    remove( offset );
    insert( book, Position::TOP );
  }
}



void BookList::swap( BookList & rhs ) noexcept
{
  if( this == &rhs ) return;

  _books_array  .swap( rhs._books_array   );
  _books_vector .swap( rhs._books_vector  );
  _books_dl_list.swap( rhs._books_dl_list );
  _books_sl_list.swap( rhs._books_sl_list );

  std::swap( _books_array_size, rhs._books_array_size );
}












/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/
std::ostream & operator<<( std::ostream & stream, const BookList & bookList )
{
  if( !bookList.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  unsigned count = 0;
  for( const auto & book : bookList._books_sl_list )   stream << '\n' << std::setw(5) << count++ << ":  " << book;

  return stream;
}



std::istream & operator>>( std::istream & stream, BookList & bookList )
{
  if( !bookList.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  for( Book book; stream >> book; )   bookList.insert( book, BookList::Position::BOTTOM );
  
  return stream;
}












/*******************************************************************************
**  Relational Operators
*******************************************************************************/
int BookList::compare( const BookList & other ) const
{
  if( !containersAreConsistant() || !other.containersAreConsistant() ) throw BookList::InvalidInternalState_Ex( "Container consistency error" exception_location );

  ///////////////////////// TO-DO (16) //////////////////////////////
    /// Compare this Booklist object with the other Booklist object.  Return a negative number if this Booklist object is less than
    /// the other Booklist object, zero if this Booklist object is equal to the other Booklist object, and a positive number if this
    /// Booklist object is greater than the other Booklist object.
    /// 
    /// Compare the size of the two Booklist objects first.  If the sizes are different, you have your answer: if size() <
    /// other.size() then return -1, and so on. If the sizes are equal, then walk the lists from beginning to end comparing the
    /// contents of the two books, one from this Booklist and one from the other Booklist. The content of all the containers in a
    /// Booklist is the same - so pick one to walk. If the books are different, you have your answer. If you get all the way to the
    /// end of the list and found no books that are different, you have your answer:  the lists are equal.

  /////////////////////// END-TO-DO (16) ////////////////////////////
}



bool operator==( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) == 0; }
bool operator!=( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) != 0; }
bool operator< ( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) <  0; }
bool operator<=( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) <= 0; }
bool operator> ( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) >  0; }
bool operator>=( const BookList & lhs, const BookList & rhs )  { return lhs.compare( rhs ) >= 0; }
