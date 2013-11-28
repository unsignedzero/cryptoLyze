/* Contained are small sboxes used mainly for testing functions.
 *
 * Created by David Tran (unsignedzero)
 * Version 1.0.0.0
 * Last Modified:11-28-2013
 */

#ifndef SBOX16_CPP
#define SBOX16_CPP

namespace sboxData16{

const unsigned int sboxLength = 16;

const unsigned int ident[sboxLength] = {
  0x0, 0x1, 0x2, 0x3,
  0x4, 0x7, 0x6, 0x7,
  0x8, 0x9, 0xA, 0xB,
  0xC, 0xD, 0xE, 0xF
};

const unsigned int magic_square[sboxLength] = {
  0xF, 0xE, 0xD, 0xC,
  0xB, 0xA, 0x9, 0x8,
  0x7, 0x6, 0x5, 0x4,
  0x3, 0x2, 0x1, 0x0
};

const unsigned int inv_magic_square[sboxLength] = {
  0x0, 0x1, 0x2, 0x3,
  0x4, 0x7, 0x6, 0x7,
  0x8, 0x9, 0xA, 0xB,
  0xC, 0xD, 0xE, 0xF
};

const unsigned int sms4_box[sboxLength] = {
   0,  3, 15,  8,
   6, 10,  8,  5,
  11, 14,  2, 12,
   1, 13,  4,  7
};

const unsigned int inv_sms4_box[sboxLength] = {
   0, 12, 10,  1,
  14,  7,  4, 15,
   3,  6,  5,  8,
  11, 13,  9,  2
};

};

#endif
