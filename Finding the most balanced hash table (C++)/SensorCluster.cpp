#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "SensorCluster.hpp"

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int nic) {
  // TODO: implement this function, then delete the return statement below
  nic /= 100000;
  return nic;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
   nic /= 10000;
   nic = nic % 10;
   return nic;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below
   nic /= 1000;
   nic = nic % 10;
 	return nic;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int nic) {
  // TODO: implement this function, then delete the return statement below
  nic /= 100;
  nic = nic % 10;
	return nic;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
  nic /= 10;
  nic = nic % 10;
	return nic;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int nic) {
    // TODO: implement this function, then delete the return statement below
	return (nic % 10);
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int nic):itemName_(itemName), nic_(nic)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void SensorNIC::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int nic;
    while (myfile >> itemName >> nic) {
			if (itemName.size() > 0)
      	addItem(itemName, nic);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void SensorNIC::addItem(string itemName, unsigned int nic) {
  // TO BE COMPLETED
  // function that adds the specified NIC to the sensor network (i.e., to all hash tables)

  hT1[nic] = itemName;
  hT2[nic] = itemName;
  hT3[nic] = itemName;
  hT4[nic] = itemName;
  hT5[nic] = itemName;
  hT6[nic] = itemName;
}

bool SensorNIC::removeItem(unsigned int nic) {
   // TODO: implement this function, then delete the return statement below

  // function that removes the sensor specified by the nic value from the network
  // if sensor is found, then it is removed and the function returns true
  // else returns false

  bool hT1Found = false;
  for (auto it = hT1.begin(); it != hT1.end(); it++) {
    if (it->first == nic) {
      hT1.erase(it);
      hT1Found = true;
      break;
    }
  }

  bool hT2Found = false;
  for (auto it = hT2.begin(); it != hT2.end(); it++) {
    if (it->first == nic) {
      hT2.erase(it);
      hT2Found = true;
      break;
    }
  }

  bool hT3Found = false;
  for (auto it = hT3.begin(); it != hT3.end(); it++) {
    if (it->first == nic) {
      hT3.erase(it);
      hT2Found = true;
      break;
    }
  }

  bool hT4Found = false;
  for (auto it = hT4.begin(); it != hT4.end(); it++) {
    if (it->first == nic) {
      hT4.erase(it);
      hT4Found = true;
      break;
    }
  }

  bool hT5Found = false;
  for (auto it = hT5.begin(); it != hT5.end(); it++) {
    if (it->first == nic) {
      hT5.erase(it);
      hT5Found = true;
      break;
    }
  }

  bool hT6Found = false;
  for (auto it = hT6.begin(); it != hT6.end(); it++) {
    if (it->first == nic) {
      hT6.erase(it);
      hT6Found = true;
      break;
    }
  }

  if (hT1Found == true && hT2Found == true
                      && hT3Found == true
                      && hT4Found == true
                      && hT5Found == true
                      && hT3Found == true)
                      return true;
  return false;
}

unsigned int SensorNIC::bestHashing() {
  // TODO: implement this function, then delete the return statement below

  // function that decides the best hash function, i.e. the ones among
  // fct1-fct6 that creates the most balanced sensor network for the current
  // set of NIC addresses, i.e. data member allItems

	// Hints:
	// Calculate the balance of each hashtable, one by one.
  unsigned int maxHT1Size = hT1.bucket_size(0);
  unsigned int minHT1Size = hT1.bucket_size(0);
	for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT1.bucket_size(i) > maxHT1Size) {
       maxHT1Size = hT1.bucket_size(i);
     }

     if (hT1.bucket_size(i) < minHT1Size) {
       minHT1Size = hT1.bucket_size(i);
     }
  }

  unsigned int balanceHT1 = maxHT1Size - minHT1Size;



  unsigned int maxHT2Size = hT2.bucket_size(0);
  unsigned int minHT2Size = hT2.bucket_size(0);
  for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT2.bucket_size(i) > maxHT2Size) {
       maxHT2Size = hT2.bucket_size(i);
     }

     if (hT2.bucket_size(i) < minHT2Size) {
       minHT2Size = hT2.bucket_size(i);
     }
  }

  unsigned int balanceHT2 = maxHT2Size - minHT2Size;



  unsigned int maxHT3Size = hT3.bucket_size(0);
  unsigned int minHT3Size = hT3.bucket_size(0);
  for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT3.bucket_size(i) > maxHT3Size) {
       maxHT3Size = hT3.bucket_size(i);
     }

     if (hT3.bucket_size(i) < minHT3Size) {
       minHT3Size = hT3.bucket_size(i);
     }
  }

  unsigned int balanceHT3 = maxHT3Size - minHT3Size;



  unsigned int maxHT4Size = hT4.bucket_size(0);
  unsigned int minHT4Size = hT4.bucket_size(0);
  for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT4.bucket_size(i) > maxHT4Size) {
       maxHT4Size = hT4.bucket_size(i);
     }

     if (hT4.bucket_size(i) < minHT4Size) {
       minHT4Size = hT4.bucket_size(i);
     }
  }

  unsigned int balanceHT4 = maxHT4Size - minHT4Size;



  unsigned int maxHT5Size = hT5.bucket_size(0);
  unsigned int minHT5Size = hT5.bucket_size(0);
  for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT5.bucket_size(i) > maxHT5Size) {
       maxHT5Size = hT5.bucket_size(i);
     }

     if (hT5.bucket_size(i) < minHT5Size) {
       minHT5Size = hT5.bucket_size(i);
     }
  }

  unsigned int balanceHT5 = maxHT5Size - minHT5Size;



  unsigned int maxHT6Size = hT6.bucket_size(0);
  unsigned int minHT6Size = hT6.bucket_size(0);
  for (unsigned int i = 0; i < 10; ++i) {
     // Call bucket_size() to get the size of each bucket
     if (hT6.bucket_size(i) > maxHT6Size) {
       maxHT6Size = hT6.bucket_size(i);
     }

     if (hT6.bucket_size(i) < minHT6Size) {
       minHT6Size = hT6.bucket_size(i);
     }
  }

  unsigned int balanceHT6 = maxHT6Size - minHT6Size;



	// Then, calculate the lowest balance

  unsigned int lowestBalance = balanceHT1;
  int hTnum = 1;
  if (balanceHT2 < lowestBalance) {
    lowestBalance = balanceHT2;
    hTnum = 2;
  }

  if (balanceHT3 < lowestBalance) {
    lowestBalance = balanceHT3;
    hTnum = 3;
  }

  if (balanceHT4 < lowestBalance) {
    lowestBalance = balanceHT4;
    hTnum = 4;
  }

  if (balanceHT5 < lowestBalance) {
    lowestBalance = balanceHT5;
    hTnum = 5;
  }

  if (balanceHT6 < lowestBalance) {
    lowestBalance = balanceHT6;
    hTnum = 6;
  }
  return hTnum;
}

// ALREADY COMPLETED
size_t SensorNIC::size() {
    if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) )
  	throw std::length_error("Hash table sizes are not the same");

	return hT1.size();
}
