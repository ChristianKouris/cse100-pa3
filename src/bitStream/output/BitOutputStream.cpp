/**
 * This cpp file adds implementation to write bits to an output file
 * using a buffer. The input will take a bit and add it to the end of the
 * buffer unless the buffer is full to which it will flush the buffer.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Week 6 Discussion, c++ operators doc, ostream
 */
#include "BitOutputStream.hpp"

/* Flushes the buffer into the output stream. */
void BitOutputStream::flush() {

    // write buf to out and set buffer/nbits to 0
    out << buf;
    buf = 0;
    nbits = 0;

}

/* Writes a single bit to the buffer. If the buffer has had 8 bits written
 * then the flush method is called.
 * Parameter: i - the bit to be written (i is assumed to be either 1 or 0)
 */
void BitOutputStream::writeBit(int i) {

    //if bit buffer is fully written, flush it
    if( nbits == 8 ) {
        flush();
    }

    //add the new bit to the buffer
    buf = (buf << 1) | i;
    nbits++;

}
