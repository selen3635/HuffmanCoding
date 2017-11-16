/**
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 13, 2016
 * File: BitOutputStream.hpp
 */

#include <iostream>
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

class BitOutputStream {

  private:

    // one byte buffer of bits
    char buf;
    // how many bits have been writeen to buf
    int nbits;
    // reference to the output stream to use
    std::ostream & out;

  public:

    /** Initialize a BitOutputStream that will use
     *  the given ostream for output
     */
    BitOutputStream(std::ostream & os) : out(os), buf(0), nbits(0) {
    }

    /** Send the buffer to the output, and clear it */
    void flush();

    /** Write the least significant bit of the argument to 
      * the bit buffer.
      */
    void writeBit(int i);


};

#endif
