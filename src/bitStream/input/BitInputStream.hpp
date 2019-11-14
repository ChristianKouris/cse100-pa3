/**
 * This hpp file creates the method signatures for the BitInputStream class
 * as well as the default constructor. The purpose of this file is to overcome
 * the c++ restriction that the minimun i/o size is a byte for i/ostreams.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Week 6 Discussion, istream, c++ operators doc
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** The two main methods in this class are the fill and readBit methods.
 *  We usually will just concern ourselves with readBit as when the entire
 *  byte buffer is read, readBit calls fill automatically.
 */
class BitInputStream {
  private:
    char buf;     // one byte buffer of bits
    int nbits;    // number of bits have been writen to buf
    istream& in;  // reference to the input stream to use

  public:
    /* The default contructor for the BitInputStream. The only input is
     * the file stream we are reading from (istream). the buf and nbits
     * are set to 0 as they are not important initially.
     * Parameter: is - the input stream we want to read from.
     */
    explicit BitInputStream(istream& is) : in(is){
        buf = 0; nbits = 0;
    };

    /* Fills the byte size buffer with the next char in the input stream.
     * Mainly just uses the get command along with setting the nbits to 8.
     */
    void fill();

    /* Reads a single bit and returns it in the form of unsigned int.
     * if the entire buffer has been read, then the method calls the fill 
     * method in order to get the next byte of data.
     */
    unsigned int readBit();
};

#endif
