/* A wrapper for sboxSupportLib that uses those functions to analyze an sbox.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.0.0.0
 * Last Modified:11-28-2013
 */

#ifndef SBOX_WRAPPER_LIB_H
#define SBOX_WRAPPER_LIB_H

#ifndef MAX_LENGTH
 #define MAX_LENGTH 3
#endif

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
#endif

#define ROTATION_COUNT 8

#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>

#include "printStl.hpp"
#include "sboxSupportLib.hpp"

namespace zx{

const std::string ROTATION_LABEL[ROTATION_COUNT] = {
  "original"            ,  "90_rot_right"  ,
  "180_rot_right"       , "270_rot_right"  ,
  "symmetry_xaxis"      , "symmetry_yaxis" ,
  "symmetry_line_neg_x" , "symmetry_line_x"
};

std::vector<std::vector<unsigned int> > createSboxFamily(
    std::vector<unsigned int> sboxVector);
/* Creates a vector which are the eight rotations of the given sbox.
 *
 * sboxVector should be an sbox in vector form for this to make sense.
 */

void analyzeSbox( const std::vector<unsigned int>& sboxVector,
    const std::vector<unsigned int>& identSboxVector,
    const std::string sboxName = EMPTY_STRING );
/* Analyzes an sbox given the sbox and the identity sbox.
 *
 * sboxVector must be a valid sbox.
 * identSboxVector must be the identity sbox of the same size.
 * sboxName is used to name the output file.
 *   (Default output_symmetry_<callNumber>.txt)
 */

void calculateSymmetry( const std::vector<unsigned int>& sboxVector,
    const std::string sboxName = EMPTY_STRING );
/* Prints out symmetry value of a given sbox and its 7 rotations.
 *
 * sboxVector must be a valid sbox.
 * sboxName is used to name the output file.
 *   (Default output_symmetry_<callNumber>.txt)
 */

};

#ifndef SBOX_WRAPPER_LIB_CPP
 #include "sboxWrapperLib.cpp"
 #ifndef SBOX_WRAPPER_LIB_CPP
  #error "sboxWrapperLib.cpp missing"
 #endif
#endif

#endif
