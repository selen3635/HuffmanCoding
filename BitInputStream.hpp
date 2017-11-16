/**
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 13, 2016
 * File: BitInputStream.hpp
 */

#include <iostream>
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

class BitInputStream {

  private:
    // one byte buffer of bits
    char buf;
    //how many bits have been read from buf
    int nbits;
    // the input stream to use
    std::istream & in;

  public:

    /** Initialize a BitIputStream that will use
     *  the given istream for input.
     */
    BitInputStream(std::istream & is) : in(is) {

      //clear buffer
      buf = 0;
      // initialize bit index
      nbits = 0;
    }

    /** Fill the buffer from the input */
    void fill();

    /** Read the next bit from the bit buffer */
    int readBit();

};

#endif
