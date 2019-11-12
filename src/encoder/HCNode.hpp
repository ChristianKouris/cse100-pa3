/**
 * This file defines the HC Node which is used to build a Huffman Coding Tree. 
 * Each node with path either to a 1 bit or a 0 bit and will hold it's parent;
 * if it is a leaf it will also hold it's frequency count as well as the 
 * character that the code represents. This file also has a comparator tp make
 * sure that the higher frequency characters are represented by less bits.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: pa3 writeup
 */
#ifndef HCNODE_HPP
#define HCNODE_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
class HCNode {
  public:
    unsigned int count;  // the freqency of the symbol
    byte symbol;         // byte in the file we're keeping track of
    HCNode* c0;          // pointer to '0' child
    HCNode* c1;          // pointer to '1' child
    HCNode* p;           // pointer to parent

    /* Constructor that initialize a HCNode */
    HCNode(unsigned int count, byte symbol, HCNode* c0 = 0, HCNode* c1 = 0,
           HCNode* p = 0)
        : count(count), symbol(symbol), c0(c0), c1(c1), p(p) {}
};

/* For printing an HCNode to an ostream. Possibly useful for debugging */
ostream& operator<<(ostream&, const HCNode&) __attribute__((weak));
ostream& operator<<(ostream& stm, const HCNode& n) {
    stm << "[" << n.count << "," << (int)(n.symbol) << "]";
    return stm;
}

/* Comparator of HCNode pointer. In priority queue, HCNode ptr with lower count
 * has higher priority, and if count is the same, HCNode ptr with larger symbol
 * has higher prioruty.
 */
struct HCNodePtrComp {
    
    bool operator()(HCNode*& lhs, HCNode*& rhs) const { 
    
        //if the count is the same we have to get the higher ascii value
        if( lhs->count == rhs->count ) {
            return lhs->symbol < rhs->symbol;
        }

        //the one with the lower count has a higher priority
        return rhs->count < lhs->count;    
    
    }
};
#endif  // HCNODE_HPP
