/* Simple functions that print out all the values of the STL containers.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.0.0.0
 * Last Modified:11-28-2013
 */

#ifndef PRINTSTL_CPP
#define PRINTSTL_CPP

#ifndef PRINTSTL_HPP
 #include "printStl.hpp"
 #ifndef PRINTSTL_HPP
  #error "MISSING printStl HPP FILE"
 #endif
#endif

#include <iomanip>
#include <sstream>

#if ( PRINTSTL_DEBUG == true )
  #include <iostream>
#endif

namespace zx{

bool validInterval(
  signed long long int& startValue,
  signed long long int& endValue,
  const signed long long int stepValue,
  const signed long long int containerSize){
  static signed long long int i;

  if ( (containerSize <= 0LL) ||
       (startValue >= containerSize) ||
       (startValue < 0LL) || (endValue < 0LL) || (stepValue == 0LL) ){
    return false;
  }

  if ( endValue > startValue && endValue > containerSize){
    endValue = containerSize;
  }
  else if ( startValue > endValue && startValue > containerSize){
    startValue = containerSize;
  }

  if ( ( (stepValue > 0LL) && (startValue > endValue) ) ||
       ( (stepValue < 0LL) && (endValue < startValue) )
     ){
    i = startValue;
    startValue = endValue;
    endValue = i;
  }

  #if ( PRINTSTL_DEBUG == true )
  std::cout
    << "DEBUG ON"   << '\n'
    << "startValue is " << startValue << '\n'
    << "endValue is " << endValue << '\n'
    << "stepValue is " << stepValue << std::endl;
  #endif

  return true;
}

#ifdef _GLIBCXX_VECTOR
template <class data_type>
std::string sprint(
  const std::vector<data_type>& vectorInput,
  signed long long int startValue,
  signed long long int endValue,
  signed long long int stepValue,
  std::string delmiterString,
  bool printEndDelimiter
  ){

  static std::stringstream stringBuffer;
  static signed long long int i, containerSize;

  containerSize = vectorInput.size();

  if ( !validInterval(startValue, endValue, stepValue, containerSize) ){
    return EMPTY_STRING;
  }

  stringBuffer.str(EMPTY_STRING);

  if ( printEndDelimiter ){
    stringBuffer << '<';
  }

  stringBuffer << vectorInput[startValue];

  for( i = (startValue+stepValue) ; i < endValue ; i+=stepValue){
    stringBuffer << delmiterString << vectorInput[i];
  }

  if ( printEndDelimiter ){
    stringBuffer << '>';
  }

  return stringBuffer.str();
}

template <class data_type>
std::string sprintSbox(
  const std::vector<data_type>& vectorInput,
  std::string vectorName,
  unsigned int numOfCols,
  unsigned int printPaddingWidth,
  signed long long int startValue,
  signed long long int endValue,
  signed long long int stepValue,
  std::string delmiterString
  ){

  static std::stringstream stringBuffer;
  static signed long long int i, containerSize;
  static unsigned int count;

  containerSize = vectorInput.size();

  if ( !validInterval(startValue, endValue, stepValue, containerSize) ){
    return EMPTY_STRING;
  }

  if ( endValue >= containerSize ){
    endValue = containerSize;
  }

  if ( numOfCols == 0 ){
    numOfCols = 16;
  }
  if ( printPaddingWidth == 0 ){
    printPaddingWidth = 3;
  }

  stringBuffer.str("\n");

  stringBuffer << vectorName << '[' << containerSize << "] = {\n";

  count = 1;

  stringBuffer << "  " << std::setfill(' ') << std::setw(printPaddingWidth)
      << vectorInput[startValue];

  for( i = (startValue+stepValue) ; i < endValue ; i+=stepValue ){
    if ( count != 0ULL ){
      stringBuffer << delmiterString;
    }
    stringBuffer << std::setfill(' ') << std::setw(printPaddingWidth)
      << vectorInput[i];

    count+=1;

    if ( count == numOfCols ){
      count = 0LL;
      stringBuffer << delmiterString << "\n  ";
    }
  }

  stringBuffer << "};\n";

  return stringBuffer.str();
}
#endif

#ifdef _GLIBCXX_SET
template <class data_type>
std::string sprint(
  const std::set<data_type>& setInput,
  signed long long int startValue,
  signed long long int endValue,
  signed long long int stepValue,
  std::string delmiterString,
  bool printEndDelimiter
   ){

  static std::stringstream stringBuffer;
  typename std::set<data_type>::const_iterator iteratorPtr;
  typename std::set<data_type>::const_iterator endPtr;
  static signed long long int i, containerSize;
  static bool terminateLoop;

  containerSize = setInput.containerSize();

  if ( !validInterval(startValue, endValue, stepValue, containerSize) )
    return EMPTY_STRING;

  stringBuffer.str(EMPTY_STRING);
  terminateLoop = false;

  iteratorPtr = setInput.begin();
  endPtr = setInput.end();
  i = 0LL;

  if ( printEndDelimiter )
    stringBuffer << '{';

  while( i != startValue ){
    iteratorPtr++;
    i++;
    if ( iteratorPtr == endPtr ){
      terminateLoop = true;
      break;
    }
  }

  stringBuffer << *iteratorPtr;

  while( !terminateLoop && i != stepValue ){
    iteratorPtr++;
    i++;
    if ( iteratorPtr == endPtr ){
      terminateLoop = true;
      break;
    }
  }

  for( ; !terminateLoop ; ){
    stringBuffer << delmiterString << *iteratorPtr;
    i = 0LL;
    while( i != stepValue ){
      iteratorPtr++;
      i++;
      if ( iteratorPtr == endPtr ){
        terminateLoop = true;
        break;
      }
    }
  }

  if ( printEndDelimiter )
    stringBuffer << '}';

  return stringBuffer.str();
}
#endif

#ifdef _GLIBCXX_LIST
template <class data_type>
std::string sprint(
  std::list<data_type>& listInput,
  signed long long int startValue,
  signed long long int endValue,
  signed long long int stepValue,
  std::string delmiterString,
  bool printEndDelimiter
   ){

  static std::stringstream stringBuffer;
  typename std::list<data_type>::iterator iteratorPtr, endValue;
  static signed long long int i, containerSize;
  static bool terminateLoop;

  containerSize = listInput.containerSize();

  if ( !validInterval(startValue, endValue, stepValue, containerSize) )
    return EMPTY_STRING;

  stringBuffer.str(EMPTY_STRING);
  terminateLoop = false;

  iteratorPtr = listInput.begin();
  endValue = listInput.endValue();
  i = 0LL;

  if ( printEndDelimiter )
    stringBuffer << '<';

  while( i != startValue ){
    iteratorPtr++;
    i++;
    if ( iteratorPtr == endValue ){
      terminateLoop = true;
      break;
    }
  }

  stringBuffer << *iteratorPtr;

  while( !terminateLoop && i != stepValue ){
    iteratorPtr++;
    i++;
    if ( iteratorPtr == endValue ){
      terminateLoop = true;
      break;
    }
  }

  for( ; !terminateLoop ; ){
    stringBuffer << delmiterString << *iteratorPtr;
    i = 0LL;
    while( i != stepValue ){
      iteratorPtr++;
      i++;
      if ( iteratorPtr == endValue ){
        terminateLoop = true;
        break;
      }
    }
  }

  if ( printEndDelimiter )
    stringBuffer << '>';

  return stringBuffer.str();
}
#endif

};

#endif
