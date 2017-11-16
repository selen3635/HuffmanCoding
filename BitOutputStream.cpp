/**
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 13, 2016
 * File: BitOutputStream.cpp
 */

#include <iostream>
#include "BitOutputStream.hpp"

/** Send the buffer to the output, and clear it*/
void BitOutputStream::flush() {

  out.put(buf);
  out.flush();
  buf = nbits = 0;
}

/** Write the least significant bit of the argument to 
  * the bit buffer, and increament the bit buffer index.
  * But flush the buffer first, if it is full.
  */
void BitOutputStream::writeBit(int i) {

  //Is the bit buffer full: Then flush it.
  if ( nbits == 8 )
    flush();

  //Write the least significant bit of i into buffer
  // at the current index
  buf = buf | (i << (7 - nbits));


  //Increment the index
  nbits++;

}
