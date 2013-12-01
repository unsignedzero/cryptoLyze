/* A collection of support functions that together, analyze an sbox.
 *
 * See http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
 *
 * Created by David Tran (unsignedzero)
 * Version 1.2.1.0
 * Last Modified:12-01-2013
 */

#ifndef MAX_NUMBER_LENGTH
 #define MAX_NUMBER_LENGTH 3
#endif

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
#endif

#ifndef DEBUG
 #define DEBUG 0
#endif

#ifndef debug
 #define debug if(DEBUG)
#endif

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <vector>

namespace zx{

///////////////////////////////////////////////////////////////////////////////
// Order
template <class type>
std::vector<type> applyPermutation( const std::vector<type>& pboxVector,
    const std::vector<type>& sboxVector ){
  static unsigned long long int i, vectorLength;
  static std::vector<type> resultVector;

  vectorLength = pboxVector.size();
  resultVector.clear();

  if ( vectorLength != sboxVector.vectorLength() ){
    return resultVector;
  }

  resultVector.resize(vectorLength, 0);

  for( i = 0 ; i < vectorLength ; i++ ){
    resultVector[i] = sboxVector[pboxVector[i]];
  }

  return resultVector;
}

template <class type>
unsigned int calculateOrderSbox( const std::vector<type>& sboxVector ){
  return lcm( calculateCycleCountSbox(sboxVector) );
}

template <class type>
std::vector< std::vector< type > > calculateOrderSboxNaive(
    const std::vector<type>& sboxVector ){
  static std::vector<std::vector<type> > solutionVectors;
  static std::vector<type> current;
  static unsigned int vectorLength;

  current.clear();
  solutionVectors.clear();

  vectorLength = sboxVector.size();

  if ( vectorLength == 0 ){
    return solutionVectors;
  }
  if ( vectorLength == 1 ){
    solutionVectors.push_back(sboxVector);
    return solutionVectors;
  }

  solutionVectors.push_back(sboxVector);

  current = generateInverseSbox(sboxVector);

  solutionVectors.push_back(current);

  while( !isEqual(current, sboxVector) ){
    current = generateInverseSbox(current);
    solutionVectors.push_back(current);
  }

  return solutionVectors;
}

template <class type>
std::vector<type> generateInverseSbox( const std::vector<type>& sboxVector ){
  static unsigned long long int i, vectorLength;
  static std::vector<type> result;

  vectorLength = sboxVector.size();
  result.clear();

  if ( vectorLength == 0 ){
    return result;
  }

  result.resize(vectorLength, 0);

  for( i = 0 ; i < vectorLength ; i++ ){
    result[sboxVector[i]] = i;
  }

  return result;
}
///////////////////////////////////////////////////////////////////////////////
// Cycle
template <class type>
std::vector<unsigned long long int> calculateCycleCountSbox(
    const std::vector<type>& sboxVector){

  static unsigned int vectorLength, i;
  static std::vector<bool> hasVisitedNode;

  static unsigned short currentPos, currentCycleCount;
  static std::set<type> storeUniqueCycleCountValue;

  static std::vector<unsigned long long int> outputVector;
  static typename std::set<type>::iterator currentLocation, lastLocation;

  vectorLength = sboxVector.size();

  outputVector.clear();
  storeUniqueCycleCountValue.clear();
  hasVisitedNode.clear();

  for( i = 0 ; i < vectorLength ; i++ ){
    hasVisitedNode.push_back(false);
  }

  for( i = 0 ; i < vectorLength ; i++ ) {
    if ( hasVisitedNode[sboxVector[i]] == false ) {
      debug std::cout << "starting new loop\n" << i << '\n';

      currentCycleCount = 1;
      hasVisitedNode[sboxVector[i]] = true;
      currentPos = sboxVector[sboxVector[i]];
      while ( hasVisitedNode[currentPos] == false ) {
         debug std::cout << "Found a loop. Scanning\n";
         debug std::cout << currentPos << '\n';

         hasVisitedNode[currentPos] = true;

         currentCycleCount +=1;
         currentPos = sboxVector[currentPos];

         debug std::cout << "new position is now" << currentPos << "\n";
      }
      debug std::cout << "currentCycleCount is " << currentCycleCount
        << std::endl;
      storeUniqueCycleCountValue.insert(currentCycleCount);
    }
  }

  currentLocation = storeUniqueCycleCountValue.begin();
  lastLocation = storeUniqueCycleCountValue.end();

  if ( *currentLocation == 1 ){
    currentLocation++;
  }

  for( ; currentLocation != lastLocation ; currentLocation++ ){
    outputVector.push_back(*currentLocation);
  }

  return outputVector;
}

template <class type>
std::string sprintCycleCountSbox( const std::vector<type>& sboxVector ){

  static std::stringstream output;
  static unsigned int vectorLength, i;
  static short currentPos, loopCount, currentCycleCount, currentLongestCycle;
  static std::vector<bool> hasVisitedNode;

  vectorLength = sboxVector.size();

  hasVisitedNode.resize(vectorLength);

  for( i = 0 ; i < vectorLength ; i++ ){
    hasVisitedNode[i] = false;
  }

  output.str(EMPTY_STRING);
  currentLongestCycle = 0;
  loopCount = 0;

  output << "\n\nAnalyzing cycles of numbers\n";

  for( i = 0 ; i < vectorLength ; i++ ) {
    if ( hasVisitedNode[sboxVector[i]] == false ) {
      loopCount+=1;

      currentCycleCount = 1;
      hasVisitedNode[sboxVector[i]] = true;
      currentPos = (sboxVector[i]);

      output << "Cycle: ( "
      << std::setw(MAX_NUMBER_LENGTH) << std::setfill('0')
      << (currentPos);
      currentPos = sboxVector[currentPos];
      while ( hasVisitedNode[currentPos] == false ) {
         currentCycleCount += 1;
         hasVisitedNode[currentPos] = true;

         output << ", "
         << std::setw(MAX_NUMBER_LENGTH) << std::setfill('0')
         << (currentPos);

         currentPos = sboxVector[currentPos];
      }
      if ( currentCycleCount > currentLongestCycle){
        currentLongestCycle = currentCycleCount;
      }
      output << " )\nLength is: " << currentCycleCount << '\n';;
    }
  }

  output << "\nThere " << ((loopCount==1) ? "is" : "are");
  output << ' ' << loopCount << " loop";
  output << ((loopCount==1) ? ' ' : 's' ) << '\n';
  output << "The longest cycle contains " << currentLongestCycle
    << " element(s)\n";

  currentCycleCount = 0;

  output << "\nLocating all fixed points\n";
  for( i = 0 ; i < vectorLength ; i++ ){
    if ( sboxVector[i] == ( i ) ){
      currentCycleCount+=1;

      output << "Loop at pos: "
      << std::setw(MAX_NUMBER_LENGTH) << std::setfill('0')
      << (i) << '\n';
    }
  }

  output
    << "\nThere " << ((currentCycleCount==1) ? "is" : "are")
    << ' ' << currentCycleCount << " fixed points.\n";
  output
    << "\nThere " << ((vectorLength-currentCycleCount==1) ? "is" : "are")
    << ' ' << (vectorLength-currentCycleCount)
    << " deranged points.\n";

  return output.str();
}
///////////////////////////////////////////////////////////////////////////////
// Permutation Number
template <class type>
unsigned long long int calculatePermutationNumber(
    const std::vector<type>& inputVector){

  static unsigned int i, j, currentValue, vectorLength;
  static unsigned int count;

  vectorLength = inputVector.size();
  count = 0;

  for( i = 0 ; i < vectorLength ; i++ ){
    currentValue = inputVector[i];
    for( j = (i+1) ; j < vectorLength ; ++j ){
      if ( currentValue > inputVector[j] ){
        count+=1;
      }
    }
  }

  return count;
}
///////////////////////////////////////////////////////////////////////////////
// Expected Value (Correlation)
template <class type>
inline long double correlation( std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB){
  const std::vector <type> constInputVectorA = inputVectorA;

  return correlation(constInputVectorA, inputVectorB);
}

template <class type>
inline long double correlation( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB){
  return (covariance(inputVectorA, inputVectorB))/
          sqrt(variance(inputVectorA)*variance(inputVectorB));
}

template <class type>
long double covariance( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB ){

  static unsigned long long int i, vectorLength;
  static long double result, meanX, meanY;

  vectorLength = std::min( inputVectorA.size(), inputVectorB.size() );
  meanX = mean(inputVectorA);
  meanY = mean(inputVectorB);
  result = 0.0;

  for( i = 0 ; i < vectorLength ; i++ ){
    result += (inputVectorA[i] - meanX) * (inputVectorB[i] - meanY);
  }

  return(result);
}

template <class type>
inline long double mean( const std::vector<type>& inputVector ){
  return ( ((long double)sum(inputVector))/inputVector.size() );
}

template <class type>
long double standardDeviation( const std::vector<type>& inputVectorA ){

  static unsigned long long int i, vectorLength;
  static long double sumValue, meanValue, finalResult;

  vectorLength = inputVectorA.size();

  if ( vectorLength <= 1 ){
    return 0;
  }

  sumValue = 0;
  meanValue = mean(inputVectorA);

  for ( i = 0 ; i < vectorLength ; i++ ){
    sumValue += pow( (((long double)(inputVectorA[i]))-meanValue), 2.0 );
  }

  finalResult = sqrt((sumValue/ vectorLength));

  return( finalResult );
}

template <class type>
long double variance( const std::vector<type>& inputVector ){
  return(covariance(inputVector, inputVector));
}
///////////////////////////////////////////////////////////////////////////////
// Line
template <class type>
std::string linearRegression( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB ){

  static std::stringstream stringBuffer;
  static unsigned int vectorLength;
  static long double yShift, slope;

  vectorLength = std::min( inputVectorA.size(), inputVectorB.size() );

  stringBuffer.str(EMPTY_STRING);

  if ( vectorLength == 1 ){
    return "Invalid. Two or more points needed to preform regression analysis!";
  }

  slope = ((long double)((vectorLength*dotProduct(inputVectorA, inputVectorB))-
            (sum(inputVectorA)*sum(inputVectorB))))/
          ((long double)((vectorLength*dotProduct(inputVectorA, inputVectorA))-
            (sum(inputVectorA)*sum(inputVectorA))));
  yShift = ((long double)(sum(inputVectorB)-slope*sum(inputVectorA)))/
           ((long double)vectorLength);

  stringBuffer << "y=" << yShift << std::showpos << slope << "x"
    << std::noshowpos;

  return stringBuffer.str();
}
///////////////////////////////////////////////////////////////////////////////
// Check
template <class type>
bool isEqual( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB){

  static unsigned long long int i, vectorLength;

  vectorLength = std::min( inputVectorA.size(), inputVectorB.size() );

  if ( vectorLength != inputVectorB.size() ){
    return false;
  }

  for( i = 0 ; i < vectorLength ; i++ ){
    if ( inputVectorA[i] != inputVectorB[i] ){
      return false;
    }
  }

  return true;
}

template <class type>
bool isIdentSbox( const std::vector<type>& inputVector){

  // This is isEqual( inputVector, ident_permutation );

  static unsigned long long int i, vectorLength;

  vectorLength = inputVector.size();

  if ( vectorLength == 0 ){
    return true;
  }

  for( i = 0 ; i < vectorLength ; i++ ){
    if ( inputVector[i] != i ){
      return false;
    }
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////
// Math
template <class type>
signed long long int dotProduct( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB ){

  static unsigned long long int i, vectorLength;
  static signed long long int sumValue;

  vectorLength = std::min( inputVectorA.size(), inputVectorB.size() );

  if ( vectorLength == 0 ){
    return 0;
  }

  sumValue = inputVectorA[0]*inputVectorB[0];

  for ( i = 1 ; i < vectorLength ; i++ ){
    sumValue += (inputVectorA[i]*inputVectorB[i]);
  }

  return(sumValue);
}

template <class type>
unsigned long long int lcm( const std::vector<type>& inputVector){

  static unsigned int vectorLength, i;
  static unsigned long long int currentNumber;

  vectorLength = inputVector.size();

  if ( vectorLength == 0 ){
    return 1;
  }
  if ( vectorLength == 1 ){
    return inputVector[0];
  }

  currentNumber = lcm( inputVector[0] , inputVector[1] );

  for ( i = 2 ; i < vectorLength ; i++ ){
    currentNumber = lcm ( currentNumber , inputVector[i] );
    if ( currentNumber == 0 ){
      break;
    }
  }

  return currentNumber;
}

template <class type>
signed long long int sum( const std::vector<type>& inputVector ){

  static unsigned long long int i, vectorLength;
  static signed long long int sumValue;

  vectorLength = inputVector.size();

  if ( vectorLength == 0 ){
    return 0;
  }

  sumValue = inputVector[0];

  for ( i = 1 ; i < vectorLength ; i++ ){
    sumValue += inputVector[i];
  }

  return(sumValue);
}

};
