/* Simple functions that print out all the values of the STL containers.
 *
 * See http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
 *
 * Created by David Tran (unsignedzero)
 * Version 1.2.0.0
 * Last Modified:12-01-2013
 */

#ifndef PRINTSTL_DEBUG
 #define PRINTSTL_DEBUG false
#endif

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
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

};
