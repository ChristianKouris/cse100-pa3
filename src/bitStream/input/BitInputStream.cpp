/**
 * This cpp file defines the methods that are int the BitInputStream class. 
 * The purpose of this file is to overcome the c++ restriction that the minimun 
 * i/o size is a byte for i/ostreams.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Week 6 Discussion, istream, c++ operators doc
 */
#include "BitInputStream.hpp"

/* Fills the byte size buffer with the next char in the input stream.
 * Mainly just uses the get command along with setting the nbits to 8.
 */
void BitInputStream::fill() {

    //ifstream method get
    in.get( buf );
    //8 bits in a byte
    nbits = 8;

}

/* Reads a single bit and returns it in the form of unsigned int.
 * if the entire buffer has been read, then the method calls the fill 
 * method in order to get the next byte of data.
 */
unsigned int BitInputStream::readBit() { 

    // fill the buffer if it is empty
    if( nbits == 0 ) {
        fill();
    }

    //read the bit
    unsigned int bit = (buf >> (nbits - 1)) & 1;

    //subtract nbits
    nbits--;

    //return 
    return bit;

}
