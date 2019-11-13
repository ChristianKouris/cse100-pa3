/**
 * This hpp file creates the method signatures for the BitOuputStream class
 * as well as the default constructor. The purpose of this file is to write 
 * bits to an output file instead of bytes.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Week 6 Discussion, c++ operators doc, ostream
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** The BitOutputStream class is a fancy way to write bits to an output stream.
 *  the only input in the constructor is an output stream to be written to.
 *  All of the other instance variables are set to 0.
 */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* This is the constructor for the BitOutputStream class.
     * The only parameter we take is an ostream reference set to the
     * variable out. buf and nbits are set to 0 in this constructor
     * Parameter: os - the output stream we want to write bits to.
     */
    explicit BitOutputStream(ostream& os) : out(os){
        buf = 0; nbits = 0;
    };

    /* Flushes the buffer into the output stream. */
    void flush();

    /* Writes a single bit to the buffer. If the buffer has had 8 bits written
     * then the flush method is called.
     * Parameter: i - the bit to be written (i is assumed to be either 1 or 0)
     */
    void writeBit(int i);
};

#endif
