///////////////////////// TO-DO (3) //////////////////////////////
/// Include necessary header files
/// Hint:  Include what you use, use what you include
#include <cstdint>    // unsigned int
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iomanip>

#include "Book.hpp"
#include "BookDatabase.hpp"
#include "Bookstore.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////





Bookstore::Bookstore( const std::string & persistenyInventoryDB )
{
  std::ifstream fin( persistenyInventoryDB );    // Creates the stream object, and then opens the file if it can
                                                 // The file is closed as fin goes out of scope

  ///////////////////////// TO-DO (2) //////////////////////////////
  /// The file's inventory contents consists of a quoted ISBN string followed by a quantity on hand unsigned integer separated by
  /// whitespace, like this:
  ///     "9861311467"	8
  ///     "9794201189"    46
  ///     "9971691361"    35
  ///     "9991137319"    9
  ///
  /// While no errors (eof, open failure, data type mismatch, etc,) detected, read the inventory record from the input stream and
  /// then add that information to the memory resident inventory database.
  ///
  /// Hint: Since we didn't define an InventoryRecord class that defines the extraction operator (best practices says we should
  /// have), extract the quoted string and the quantity attributes directly
  std::string isbn;
  unsigned int quantity = 0;

  while( fin >> std::quoted(isbn) >> quantity )
  {
    _inventoryDB[isbn] = quantity;
  }
    /////////////////////// END-TO-DO (2) ////////////////////////////
}    // File is closed as fin goes out of scope







Bookstore::Inventory_DB & Bookstore::inventory()
{
  return _inventoryDB;
}







Bookstore::BooksSold Bookstore::ringUpCustomers( const ShoppingCarts & shoppingCarts )
{
  BooksSold todaysSales;    // a collection of unique ISBNs of books sold

  ///////////////////////// TO-DO (3) //////////////////////////////
  ///  Ring up each customer accumulating the books purchased
  ///  Hint:  merge each customer's purchased books into today's sales.  (https://en.cppreference.com/w/cpp/container/set/merge)


  for( const auto & [name, cart] : shoppingCarts )
  {
    std::cout << name << "'s shopping cart:" << std::endl;
    todaysSales.merge( ringUpCustomer( cart ) );
  }
  /////////////////////// END-TO-DO (3) ////////////////////////////

  return todaysSales;
}    // ringUpCustomers







Bookstore::BooksSold Bookstore::ringUpCustomer( const ShoppingCart & shoppingCart )
{
  auto & worldWideBookDatabase = BookDatabase::instance();    // Get a reference to the database of all books in the world. The
                                                              // database will contains a full description of the item and the
                                                              // item's price.

  BooksSold purchasedBooks;    // a collection books purchased by this customer


  ///////////////////////// TO-DO (4) //////////////////////////////
  /// Print out a receipt containing a full description of books (obtained from the database of all books in the world) in the
  /// customer's shopping cart along with the total amount due. As items are being scanned, decrement the quantity on hand for
  /// that book in the store's inventory.
  ///
  ///
  /// Hint:  Here's some pseudocode to get you started.
  ///       1        Initialize the amount due to zero
  ///       2        For each book in the customer's shopping cart
  ///       2.1          If the book is not found in the database of all books in the world, indicate on the receipt it's free of charge
  ///       2.2          Otherwise
  ///       2.2.1            Print the full description on the receipt
  ///       2.2.2            Add the book's price to the amount due
  ///       2.2.3            If the book is something the store sells (the item is in the store's inventory)
  ///       2.2.3.1              Decrease the number of books on hand for the book sold
  ///       2.2.3.2              Add the book's isbn to the list of books purchased
  ///       3         Print the total amount due on the receipt
  double                                amountDue     = 0;

  // for each cart
  for( auto it = shoppingCart.cbegin(); it != shoppingCart.cend(); ++it )
  {
    const auto & currentIsbn = it->first;
    const auto & book        = it->second;
    // if current isbn is not in database
    if( !worldWideBookDatabase.find( currentIsbn ) )
    {
      std::cout << currentIsbn << " (" << book.title() << ") is free of charge." << std::endl;
    }
    else
    {
      Book * workingBook = worldWideBookDatabase.find( currentIsbn );
      // print full description
      std::cout << *workingBook << std::endl;

      // calculate total amount due
      amountDue += workingBook->price();

      // if isbn is in store's inventory
      auto search = _inventoryDB.find( currentIsbn );

      if( search != _inventoryDB.end() )
      {
        // decrement quantity in book store's inventory
        --search->second;
        // insert isbn into list of books purchased
        purchasedBooks.insert( currentIsbn );
      }
    }
  }
  // print total amount due
  std::cout << "-------------------------" << std::endl;
  std::cout << "Total amount due: $" << amountDue << "\n"
            << std::endl;

  /////////////////////// END-TO-DO (4) ////////////////////////////

  return purchasedBooks;
}    // ringUpCustomer







void Bookstore::reorderItems( BooksSold & todaysSales )
{
  auto & worldWideBookDatabase = BookDatabase::instance();    // Get a reference to the database of all books in the world. The
                                                              // database will contains a full description of the item and the
                                                              // item's price.

  ///////////////////////// TO-DO (5) //////////////////////////////
  /// For each book that has fallen below the reorder threshold, assume an order has been placed and now the shipment has
  /// arrived. Update the store's inventory to reflect the additional items on hand.
  ///
  /// Hint:  Here's some pseudocode to get you started.
  ///        1       For each book sold today
  ///        1.1         If the book is not in the store's inventory or if the number of books on hand has fallen below the re-order threshold (REORDER_THRESHOLD)
  ///        1.1.1           If the book is not in the database of all books in the world,
  ///        1.1.1.1             display just the ISBN
  ///        1.1.2           Otherwise,
  ///        1.1.2.1             display the book's full description
  ///        1.1.3           If the book is not in the store's inventory
  ///        1.1.3.1             display a notice indicating the book no longer sold in this store and will not be re-ordered
  ///        1.1.4           Otherwise,
  ///        1.1.4.1             Display the current quantity on hand and the quantity re-ordered
  ///        1.1.4.2             Increase the quantity on hand by the number of items ordered and received (LOT_COUNT)
  ///        2       Reset the list of book sold today so the list can be reused again later
  ///
  /// Take special care to avoid excessive searches in your solution

  // for each isbn in list of books sold
  for( const auto & isbn : todaysSales )
  {
    auto search = _inventoryDB.find( isbn );
    // if isbn is no in stock OR if quantity of stock is less than threshold
    if( ( search == _inventoryDB.end() ) || ( search->second < REORDER_THRESHOLD ) )
    {
      // if isbn is not in database
      if( !worldWideBookDatabase.find( isbn ) )
      {
        std::cout << isbn << std::endl;
      }
      else
      {
        Book * workingBook = worldWideBookDatabase.find( isbn );
        // print full description
        std::cout << *workingBook << std::endl;
      }


      // if isbn is not in stock
      if( search == _inventoryDB.end() )
      {
        std::cout << "no longer sold in this store and will not be re-ordered" << std::endl;
      }
      else
      {
        std::cout << "Quantity on hand: " << search->second << std::endl;
        std::cout << "Quantity re-ordered: " << LOT_COUNT << std::endl;
        // order more stock
        search->second += LOT_COUNT;
      }
    }
  }
  // reset list of book sales
  todaysSales.clear();
  /////////////////////// END-TO-DO (5) ////////////////////////////
}







Bookstore::ShoppingCarts Bookstore::makeShoppingCarts()
{
  // Our store has many customers, and each (identified by name) is pushing a shopping cart. Shopping carts are structured as
  // trees of trees of books.
  ShoppingCarts carts =
      {
          // first shopping cart
          { "Red Baron", { { "9789999995641", { "Mgt styles" } }, { "9991137319", { "Grasses of U of L" } }, { "9789999513104", { "Computer Impact on Children" } }, { "54782169785", { "131 Answer Key" } }, { "9792430091", { "Fiqh & manajemen" } }, { "9991130306", { "Birds Atlas" } } } },

          // second shopping cart
          { "Peppermint Patty", { { "9829062015", { "Fishing in Melekeok" } }, { "9789999710718", { "You Can't See Round Corners" } }, { "9810233094", { "Fuzzy logic" } }, { "9798184242729", { "Crossroads logic" } }, { "981012399X", { "Walking balloon" } }, { "9789999706124", { "Prof Bear's Math World" } }, { "9990395128", { "Thorns & roses" } }, { "9789998470804", { "Help or Hindrance" } }, { "9789998379794", { "Freedom & Beyond" } }, { "998761776X", { "Health management assessment" } }, { "9810209746", { "Waves & distributions" } }, { "9799577623217", { "Have You Seen My Cat?" } } } },

          // third shopping cart
          { "Woodstock", { { "9810234910", { "Algebraic K-theory" } }, { "9789999338493", { "Car Care" } }, { "9789998609976", { "Money & Wealth" } }, { "9789999984270", { "Our 2 Minds" } }, { "9983993279", { "Call me" } }, { "9789999987653", { "Who's Who" } }, { "9789999141079", { "Folk Songs" } }, { "9789998830035", { "Org Dev" } }, { "9789999902199", { "Be Outstanding" } }, { "9802161748", { "Wild mammals" } }, { "9812040463", { "Dirty dozen" } }, { "9789999670272", { "Breaking Promises" } }, { "9988584865", { "Ghost names" } }, { "9789999706124", { "Prof Bear's Math World" } }, { "9976910584", { "Cooking with vegetables" } }, { "9789999712651", { "Advertising Secrets" } } } },

          // forth shopping cart
          { "Schroeder", { { "9999977219", { "Sound of Her Laugh" } }, { "9789999746892", { "Children & TV" } }, { "9820000858", { "Fish Manual" } }, { "9799317207", { "Upland agriculture" } }, { "9810227639", { "Advances in robotics" } }, { "9964988028", { "Beyond the rivers" } }, { "9964782578", { "Delivered through rain" } }, { "9987617891", { "Wwomen's participation" } }, { "9964953453", { "Ile of No Return" } }, { "9810500246", { "Secret goldfish" } } } },

          // fifth shopping cart
          { "Lucy van Pelt", { { "9964781385", { "Violence" } }, { "9810458290", { "xKnowledge capital investments" } }, { "9798059840", { "Economic assessment" } }, { "9839629549", { "Hawkers delight" } }, { "9789999689182", { "Sacred Deposit" } }, { "9789999638722", { "12 Crimes of Christmas" } }, { "9856194261", { "Scales and consequences" } }, { "9810083262", { "2nd chance" } }, { "9812387285", { "Energy and geometry" } }, { "9966960619", { "A better bonfire" } }, { "9844122961", { "Looking back" } }, { "9789999706124", { "Prof Bear's Math World" } }, { "9789999275842", { "Billboard Music Week" } } } },

          // sixth shopping cart
          { "Charlie Brown", { { "9789998852051", { "From the Coal Mines" } } } } };

  return carts;
}    // makeShoppingCarts
