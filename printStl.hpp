/* Simple functions that print out all the values of the STL containers.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.0.0.1
 * Last Modified:12-01-2013
 */

#ifndef PRINTSTL_HPP
#define PRINTSTL_HPP

#ifndef PRINTSTL_DEBUG
 #define PRINTSTL_DEBUG false
#endif

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
#endif

#include <iomanip>
#include <iostream>
#include <sstream>

namespace zx{

bool validInterval(
  signed long long int& startValue,
  signed long long int& endValue,
  const signed long long int stepValue = 1,
  const signed long long int containerSize = (1ULL<<62)-1ULL
);
/* Checks if the interval between a to b is a valid interval to iterate on.
 * As this is NOT python, a and b must be non-negative calues, i.e. possible
 * index values in a container.
 *
 * Values are signed to that if we print backwards, it will stop at -1
 *
 * startValue is the startValue position
 * endValue is the endValue position
 * stepValue is the step interval
 * containerSize is the size of the container
 */

#ifdef _GLIBCXX_VECTOR
template <class data_type>
std::string sprint(
  const std::vector<data_type>& vectorInput,
  signed long long int startValue = 0LL,
  signed long long int endValue = ((1LL<<62)-1LL),
  signed long long int stepValue = 1LL,
  std::string delmiterString = ", ",
  bool printEndDelimiter = true
);
/* Prints the contents of an std::vector. By default it will print all elements
 * seperated by ,
 *
 * vectorInput is the vector input that will be sprinted
 * startValue is the startValue position
 * endValue is the endValue position
 * stepValue is the step interval
 * delmiterString is a delimiter string between each entry printed
 * printEndDelimiter sets if it should print < and >
 */

template <class data_type>
std::string sprintSbox(
  const std::vector<data_type>& vectorInput,
  std::string vectorName = "const static unsigned int vectorInput",
  unsigned int mumOfCols= 16,
  unsigned int printPaddingWidth = 3,
  signed long long int startValue = 0,
  signed long long int endValue = ((1LL<<62)-1LL),
  signed long long int stepValue= 1,
  std::string delmiterString= ", "
);
/* A print variant that prints out the sbox so that it can be used in other
 * C/ C++ code base.
 *
 * vectorInput is the sbox vector
 * vectorName will be the name of the array that will be sprinted
 * numOfCols is the numebr of columns that will be printed per row
 * printPaddingWidth sets the padding for each number so it all aligns
 * startValue is the startValue position
 * endValue is the endValue position
 * stepValue is the step interval
 * delmiterString is a delimiter string between each entry printed
 */
#endif

#ifdef _GLIBCXX_SET
template <class data_type>
std::string sprint(
  const std::set<data_type>& setInput,
  signed long long int startValue = 0,
  signed long long int endValue = ((1LL<<62)-1LL),
  signed long long int stepValue= 1,
  std::string delmiterString = ", ",
  bool printEndDelimiter = true
);
/* Prints the contents of an std::set. By default it will print all elements
 * seperated by ,
 *
 * setInput is the set that will be sprinted
 * startValue is the startValue position
 * endValue is the endValue position
 * stepValue is the step interval
 * delmiterString is a delimiter string between each entry printed
 * printEndDelimiter sets if it should print { and }
 */
#endif

#ifdef _GLIBCXX_LIST
template <class data_type>
std::string sprint(
  std::list<data_type>& listInput,
  signed long long int startValue = 0,
  signed long long int endValue = ((1LL<<62)-1LL),
  signed long long int stepValue= 1,
  std::string delmiterString = ", ",
  bool printEndDelimiter = true
);
/* Prints the contents of an std::list, By default it will print all elements
 * seperated by ,
 *
 * listInput is the set that will be sprinted
 * startValue is the startValue position
 * endValue is the endValue position
 * stepValue is the step interval
 * delmiterString is a delimiter string between each entry printed
 * printEndDelimiter sets if it should print < and >
 */
#endif

};

#ifndef PRINTSTL_CPP
 #include "printStl.cpp"
 #ifndef PRINTSTL_CPP
  #error "MISSING printStl CPP FILE"
 #endif
#endif

#endif
