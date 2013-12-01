/* A collection of support functions that together, analyze an sbox.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.2.1.0
 * Last Modified:12-01-2013
 */

namespace zx{

///////////////////////////////////////////////////////////////////////////////
// Math
unsigned long long int binGcd( unsigned long long int a,
    unsigned long long int b){

  if ( a == 0 || b == 0 ){
    return 0;
  }
  else if ( a == b ){
    return a;
  }
  else if ( (~a&1) && (~b&1) ){
    return binGcd( a>>1, b>>1 )<<1;
  }
  else if ( (~a&1) ){
    return binGcd( a>>1, b);
  }
  else if ( (~b&1) ){
    return binGcd( a, b>>1);
  }
  // Both are not even
  else if ( a > b ){
    return binGcd( b, (a-b)>>1);
  }
  else{
    return binGcd( a, (a-b)>>1);
  }
}

unsigned long long int gcd( unsigned long long int a,
    unsigned long long int b){

  if ( a == 0 || b == 0 ){
    return 0;
  }
  else if ( a == b ){
    return a;
  }
  else if ( a > b ){
    return gcd ( a - b , b );
  }
  else{
    return gcd ( a , b - a );
  }
}

unsigned long long int lcm( unsigned long long int a,
    unsigned long long int b){

  static unsigned long long int gcdValue;

  gcdValue = gcd(a, b);

  if ( gcdValue == 0 ){
    return 0;
  }
  else if ( gcdValue == 1 ){
    return (a*b);
  }
  else if ( gcdValue == a ){
    return b;
  }
  else if ( gcdValue == b ){
    return a;
  }
  else{
   return ( (a/gcdValue)*b );
  }
}

};
