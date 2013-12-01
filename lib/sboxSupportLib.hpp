/* A collection of support functions that together, analyze an sbox.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.1.0.0
 * Last Modified:12-01-2013
 */

#include <vector>

namespace zx{

/* As a whole, many of these functions, mainly statistical, can work on any
 * set of numeric vectors but not all functions have that flexibility. These
 * will be noted in their function name, containing Sbox, as well as the
 * name of the parameter, sboxVector.
 *
 * Sbox vectors are vectors of length 16^n, n>0 and contain all values from
 * 0, 1... 16^n-1 in any order. These are 2d square matrices, of side length
 * 4^n, collapsed into a flat 1d vector.
 */

///////////////////////////////////////////////////////////////////////////////
// Order
template <class type>
std::vector<type> applyPermutation( const std::vector<type>& pboxVector,
    const std::vector<type>& sboxVector );
/* NOT USED
 * Applies a permutation (pbox) to an sbox, resulting in another sbox.
 *
 * pboxVector is a vector that will contain the arragement that will
 *   create a new sbox.
 * sboxVector is the vector that will be used to generate a new sbox.
 */

template <class type>
unsigned int calculateOrderSbox( const std::vector<type>& sboxVector );
/* Calculates the order of the sbox. This exploits one of the properties
 * of an sbox. Each n cycle in an sbox takes n permutations to return to its
 * original position. Thus given cycles of length n1, n2, n3, ... nk, it will
 * take lcm( n1, n2, n3, ... nk ) iterations to get the original sbox.
 *
 * Returns zero if its a bad vector (contains zero) for the cycle count.
 *
 * sboxVector must be the sbox in vector form.
 */

template <class type>
std::vector< std::vector< type > > calculateOrderSboxNaive(
    const std::vector<type>& sboxVector );
/* NOT USED
 * A naive approach on calculating the order of an sbox by permutating until
 * we have the original sbox. Inefficient and doesn't exploit some of the
 * properties of an sbox.
 *
 * sboxVector must be the sbox in vector form.
 */

template <class type>
std::vector<type> generateInverseSbox( const std::vector<type>& sboxVector );
/* Generates the inverse sbox such that, applyPermutation of the sbox and
 * its inverse, in any order, yield the identity sbox.
 *
 * sboxVector must be the sbox in vector form.
 */

///////////////////////////////////////////////////////////////////////////////
// Cycle
template <class type>
std::vector<unsigned long long int> calculateCycleCountSbox(
    const std::vector<type>& sboxVector );
/* Calculates the cycle counts of an sbox vector. Duplicate values are
 * ignored in this case.
 *
 * sboxVector must be the sbox in vector form.
 */

template <class type>
std::string sprintCycleCountSbox( const std::vector<type>& sboxVector );
/* A variant of calculateCycleCountSbox made for printing. This will print out
 * all cycles, the elements contained within each cycle and its length.
 *
 * sboxVector must be the sbox in vector form.
 */

///////////////////////////////////////////////////////////////////////////////
// Permutation Number
unsigned long long int calculatePermutationNumber(
    const std::vector<unsigned int>& inputVector );
/* Calculates the permutation number of an sbox.
 *
 * inputVector should be an sbox in vector form for this to make sense.
 */

///////////////////////////////////////////////////////////////////////////////
// Expected Value (Correlation)
template <class type>
long double correlation( std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Calculate the correlation of vectors A and B.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

template <class type>
inline long double correlation( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Calculate the correlation of vectors A and B.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

template <class type>
long double covariance( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Calculates the covariance of vectors A and B.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

template <class type>
inline long double mean( const std::vector<type>& inputVector );
/* Calculates the mean.
 *
 * inputVector must be a vector of numeric type.
 */

template <class type>
long double standardDeviation( const std::vector<type>& inputVector );
/* Calculates the standard deviation.
 *
 * inputVector must be a vector of numeric type.
 */

template <class type>
long double variance( const std::vector<type>& inputVector );
/* Calculates the variance.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

///////////////////////////////////////////////////////////////////////////////
// Line
template <class type>
std::string linearRegression( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Preforms a simple linear regression and returns the line from that model
 * as a string or an error message.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

///////////////////////////////////////////////////////////////////////////////
// Check
template <class type>
bool isEqual(const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Checks if vectors A and B are the same vector.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB are vectors in which '==' is well-defined.
 */

template <class type>
bool isIdentSbox(const std::vector<type>& inputVector );
/* NOT USED
 * Checks if the sbox is the same as the identity sbox.
 *
 * inputVector should be an sbox in vector form for this to make sense.
 */

///////////////////////////////////////////////////////////////////////////////
// Math
unsigned long long int binGcd ( unsigned long long int a,
    unsigned long long int b );
/* A variant of the original gcd using only subtract and division by two.
 *
 * Returns zero if a or b is zero.
 *
 * a, b are positive integers that will be used to find the gcd.
 */

template <class type>
signed long long int dotProduct( const std::vector<type>& inputVectorA,
    const std::vector<type>& inputVectorB );
/* Calculates the dot product between two vectors A and B.
 *
 * Should the lengths be unequal, we will assume the shorter length.
 *
 * inputVectorA, inputVectorB must be vectors of numeric type.
 */

unsigned long long int gcd ( unsigned long long int a,
    unsigned long long int b );
/* Finds the gcd between two unsigned integers a and b.
 *
 * Returns zero if a or b is zero.
 *
 * a, b are positive integers that will be used to find the gcd.
 */

template <class type>
unsigned long long int lcm ( const std::vector<type>& inputVector );
/* Finds the least common multiple between a vector of integers.
 *
 * Returns zero if at least one value in the vector is zero.
 *
 * inputVector should be a collection of positive integer types that will be
 *   used to find the lcm.
 */

unsigned long long int lcm ( unsigned long long int a,
    unsigned long long int b );
/* Finds the least common multiple between two integers a and b.
 *
 * Returns zero if a or b is zero.
 *
 * a, b are positive integers that will be used to find the lcm.
 */

template <class type>
signed long long int sum( const std::vector<type>& inputVector );
};
/* Calculates the sum.
 *
 * inputVector must be a vector of numeric type.
 */
