/* A wrapper for sboxSupportLib that uses those functions to analyze an sbox.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.2.0.0
 * Last Modified:12-01-2013
 */

#include <vector>

namespace zx{

#ifndef EMPTY_STRING
 #define EMPTY_STRING ""
#endif

#ifndef ROTATION_COUNT
 #define ROTATION_COUNT 8
#endif

const std::string ROTATION_LABEL[ROTATION_COUNT] = {
  "original"            ,  "90_rot_right"  ,
  "180_rot_right"       , "270_rot_right"  ,
  "symmetry_xaxis"      , "symmetry_yaxis" ,
  "symmetry_line_neg_x" , "symmetry_line_x"
};

void analyzeSbox( const std::vector<unsigned int>& sboxVector,
    const std::vector<unsigned int>& identSboxVector,
    std::string sboxName = EMPTY_STRING );
/* Analyzes an sbox given the sbox and the identity sbox.
 *
 * sboxVector must be a valid sbox.
 * identSboxVector must be the identity sbox of the same size.
 * sboxName is used to name the output file.
 *   (Default output_symmetry_<callNumber>.txt)
 */

void calculateSymmetry( const std::vector<unsigned int>& sboxVector,
    std::string sboxName = EMPTY_STRING,
    unsigned int columnCount = 16 );
/* Prints out symmetry value of a given sbox and its 7 rotations.
 *
 * sboxVector must be a valid sbox.
 * sboxName is used to name the output file.
 *   (Default output_symmetry_<callNumber>.txt)
 * columnCount is the number of entries per column. Used fr print formatting.
 */

std::vector<std::vector<unsigned int> > createSboxFamily(
   const std::vector<unsigned int>& sboxVector );
/* Creates a vector which are the eight rotations of the given sbox.
 *
 * sboxVector should be an sbox in vector form for this to make sense.
 */


};
