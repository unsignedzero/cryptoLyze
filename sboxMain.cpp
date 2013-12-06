/* This program analyzes sboxes or runs symmetry tests on them.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.1.0.1
 * Last Modified:12-06-2013
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define SBOX_COLUMN_COUNT 16
#include "data/sboxdata256.hpp"

#include "printStl.hpp"
#include "sboxSupportLib.hpp"
#include "sboxWrapperLib.hpp"

///////////////////////////////////////////////////////////////////////////////
int main(){

  static std::string userInput;
  static unsigned long long int i;
  std::vector<unsigned int>
    AES, INV_AES,
    FRANK, INV_FRANK,
    SMS4, INV_SMS4,
    IDENT;

  AES.clear();
  INV_AES.clear();
  FRANK.clear();
  INV_FRANK.clear();
  SMS4.clear();
  INV_SMS4.clear();
  IDENT.clear();

  for ( i = 0 ; i < sboxData256::sboxLength ; ++i ){
     AES.push_back(sboxData256::aes[i]);
     INV_AES.push_back(sboxData256::inv_aes[i]);
     FRANK.push_back(sboxData256::magic_square[i]);
     INV_FRANK.push_back(sboxData256::inv_magic_square[i]);
     SMS4.push_back(sboxData256::sms4_box[i]);
     INV_SMS4.push_back(sboxData256::inv_sms4_box[i]);
     IDENT.push_back(i);
  }

  std::cout << "Do you want to analyze the sbox or run symmetry tests?"
    << std::endl;
  std::cin >> userInput;
  std::transform(userInput.begin(), userInput.end(),
      userInput.begin(), ::tolower);

  if ( userInput == "symmetry" ){
    std::cout << "Running symmetry tests" << std::endl;
    zx::calculateSymmetry(IDENT, "Identity", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(AES, "AES", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(INV_AES, "Inverse_AES", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(FRANK, "Franklin", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(INV_FRANK, "Inverse_Franklin", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(SMS4, "SMS4", SBOX_COLUMN_COUNT);
    zx::calculateSymmetry(INV_SMS4, "Inverse_SMS4", SBOX_COLUMN_COUNT);
  }
  else if ( userInput == "analyze" ){
    std::cout << "Running analysis tests" << std::endl;
    zx::analyzeSbox(IDENT, IDENT, "Identity");
    zx::analyzeSbox(AES, IDENT, "AES");
    zx::analyzeSbox(INV_AES, IDENT, "Inverse_AES");
    zx::analyzeSbox(FRANK, IDENT, "Franklin");
    zx::analyzeSbox(INV_FRANK, IDENT, "Inverse_Franklin");
    zx::analyzeSbox(SMS4, IDENT, "SMS4");
    zx::analyzeSbox(INV_SMS4, IDENT, "Inverse_SMS4");
  }
  else if ( userInput == "exit" ){
    std::cout << "Exiting" << std::endl;
  }
  else{
    std::cout << "Error: Bad input. Exiting" << std::endl;
  }

  return(0);
}
///////////////////////////////////////////////////////////////////////////////
