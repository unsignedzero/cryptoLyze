/* A wrapper for sboxSupportLib that uses those functions to analyze an sbox.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.2.0.0
 * Last Modified:12-01-2013
 */

#ifndef MAX_LENGTH
 #define MAX_LENGTH 3
#endif

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
#endif

#ifndef ROTATION_COUNT
 #define ROTATION_COUNT 8
#endif

#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "printStl.hpp"
#include "sboxSupportLib.hpp"
#include "sboxWrapperLib.hpp"

namespace zx{

  extern const std::string ROTATION_LABEL[ROTATION_COUNT];

///////////////////////////////////////////////////////////////////////////////
void analyzeSbox( const std::vector<unsigned int>& sboxVector,
    const std::vector<unsigned int>& identSboxVector,
    std::string sboxName ){

  static unsigned int i;
  static std::ofstream fileOutput;
  static std::stringstream fileNameBuffer;

  static std::vector<std::vector<unsigned int> > originalVectorFamily;

  static unsigned int callNumber = 0;

  fileNameBuffer.str(EMPTY_STRING);

  std::cout << "Analyzing sbox ";

  if ( sboxName == EMPTY_STRING ){
    fileNameBuffer << "output_analyze_"
      << std::setw(3) << std::setfill('0') << callNumber++ << ".txt";
    std::cout << "call number " << callNumber;
  }
  else{
    fileNameBuffer << "output_analyze_"
      << sboxName << ".txt";
    std::cout << "for " << sboxName;
  }

  std::cout << std::endl;

  fileOutput.open( fileNameBuffer.str().c_str() );

  originalVectorFamily.clear();
  originalVectorFamily = createSboxFamily(sboxVector);

  for( i = 0 ; i < ROTATION_COUNT ; ++i ){
    fileOutput
      << "\n\nLooking at " << ROTATION_LABEL[i] << '\n'
      << "The vector is\n"
      << sprintSbox(originalVectorFamily[i]) << '\n' << std::endl;
      /*
    fileOutput
      << "The order of the sbox is "
      << calculateOrderSbox(originalVectorFamily[i]) << std::endl;
      */
    fileOutput
      << "The permutation number is "
      << calculatePermutationNumber(originalVectorFamily[i]) << std::endl;
    fileOutput
      << "The correlation is "
      << correlation<unsigned int>(originalVectorFamily[i], identSboxVector) << std::endl;
    fileOutput
      << "The cycle count data is"
      << sprintCycleCountSbox(originalVectorFamily[i]) << std::endl;
    fileOutput
      << "The linear regression is "
      << linearRegression(originalVectorFamily[i], identSboxVector)
      << std::endl;
  }

  fileOutput.close();
}
///////////////////////////////////////////////////////////////////////////////
void calculateSymmetry( const std::vector<unsigned int>& sboxVector,
    std::string sboxName, unsigned int columnCount ){

  static unsigned int i;
  static std::ofstream fileOutput;
  static std::stringstream fileNameBuffer, fileOutputReorderBuffer;

  static unsigned int callNumber = 0;
  static unsigned int cummulativeCount = 0;
  static std::vector<std::vector<unsigned int> > originalVectorFamily,
    inverseVectorFamily;

  fileNameBuffer.str(EMPTY_STRING);
  fileOutputReorderBuffer.str(EMPTY_STRING);

  std::cout << "Calulating symmetry ";

  if ( sboxName == EMPTY_STRING ){
    fileNameBuffer << "output_symmetry_"
      << std::setw(3) << std::setfill('0') << callNumber++ << ".txt";
    std::cout << "call number " << callNumber;
  }
  else{
    fileNameBuffer << "output_symmetry_"
      << sboxName << ".txt";
    std::cout << "for " << sboxName;
  }

  std::cout << std::endl;

  fileOutput.open( fileNameBuffer.str().c_str() );

  originalVectorFamily.clear();
  inverseVectorFamily.clear();

  originalVectorFamily = createSboxFamily(sboxVector);
  inverseVectorFamily = createSboxFamily(generateInverseSbox(sboxVector));

  for( i = 0 ; i < ROTATION_COUNT ; ++i ){
    if ( isEqual(originalVectorFamily[i], inverseVectorFamily[i]) ){
      cummulativeCount +=1;
      fileOutputReorderBuffer
        << "The " << ROTATION_LABEL[i] << " sboxes are the same.\n"
        << sprintSbox(originalVectorFamily[i], "Sbox", columnCount, 2)
        << std::endl;
    }
    else{
      fileOutputReorderBuffer
        << "The " << ROTATION_LABEL[i] << " sboxes are NOT the same.\n"
        << sprintSbox(originalVectorFamily[i],
            "OriginalSbox", columnCount, 2) << '\n'
        << sprintSbox(inverseVectorFamily[i],
            "InverseSbox", columnCount, 2) << std::endl;
    }
  }

  fileOutput << "The number of sboxes that are commutative is/are "
    << cummulativeCount << "\n\n";

  fileOutput << fileOutputReorderBuffer.str();

  cummulativeCount = 0;

  fileOutput.close();
}
///////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<unsigned int> > createSboxFamily(
  const std::vector<unsigned int> & sboxVector ){

  static std::vector<std::vector<unsigned int> > outputVector;
  static std::vector<unsigned int> tempOutputVector;
  static signed int i, j, vectorLength, sqrtvectorLength;

  // Assume input is sbox or vector whom size is n^2

  vectorLength = sboxVector.size();
  sqrtvectorLength = (unsigned int) sqrt( (double) vectorLength );

  outputVector.clear();
  tempOutputVector.clear();

  // Default
  outputVector.push_back(sboxVector);

  // 90 Degrees
  for( i = sqrtvectorLength - 1 ; i >= 0; --i ){
    for( j = 0 ; j < sqrtvectorLength ; ++j ){
      tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
    }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // 180 Degrees
  for( i = vectorLength - 1 ; i >= 0; --i ){
    tempOutputVector.push_back(sboxVector[i]);
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // 270 Degrees
  for( i = 0 ; i < sqrtvectorLength ; ++i ){
    for( j = sqrtvectorLength - 1 ; j >= 0 ; --j ){
      tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
    }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // Symmetry (x)
  for( j = sqrtvectorLength - 1 ; j >= 0; --j ){
    for( i = 0 ; i < sqrtvectorLength ; ++i ){
     tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
   }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // Symmetry (y)
  for( j = 0 ; j < sqrtvectorLength ; ++j ){
    for( i = sqrtvectorLength - 1 ; i >= 0; --i ){
     tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
   }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // Symmetry (\)
  for( i = 0 ; i < sqrtvectorLength ; ++i ){
    for( j = 0 ; j < sqrtvectorLength ; ++j ){
     tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
   }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  // Symmetry (/)
  for( i = sqrtvectorLength - 1 ; i >= 0; --i ){
    for( j = sqrtvectorLength - 1 ; j >= 0; --j ){
     tempOutputVector.push_back(sboxVector[i+sqrtvectorLength*j]);
   }
  }

  outputVector.push_back(tempOutputVector);
  tempOutputVector.clear();

  return outputVector;
}
///////////////////////////////////////////////////////////////////////////////
};
