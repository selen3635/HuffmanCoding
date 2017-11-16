/**
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 13, 2016
 * File: BitInputStream.cpp
 */
#include "BitInputStream.hpp"

/** Fill the buffer from the input */
void BitInputStream::fill() {

  buf = in.get();
  nbits = 0;
}

/** Read the next bit from the bit buffer.
 *  Fill the buffer from the input stream first if needed.
 *  Return 1 if the bit read is 1;
 *  Return 0 if the bit read is 0;
 */
int BitInputStream::readBit() {

  /** If all bits in the buffer are read, fill the buffer first */
  if ( nbits == 8 ){
    fill();

  }

  if( in.eof())
    return EOF;
  
  // Get the bit at the appropriate location in the bit
  //  buffer, and return the appropriate int

  int num = (buf >> (7-nbits)) & 1;
  if ( num == 1 ) {
    nbits++;
    return 1;
  }
  else {
    // Increament the index
    nbits++;
    return 0;
  }
  

}



