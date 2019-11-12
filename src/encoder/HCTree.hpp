/**
 * This hpp file defines all of the method headers for the HCTree. The HCTree
 * object itself is empty until the build command is called, none of the other
 * methods can be called without build being called first. The other four
 * methods involve using the HCTree to encode and decode characters in 
 * a file.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Stepik Chapter 7.3 tree build visualization,
 *          cplusplus reference for: std::vector, std::sort, ostream, istream
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** The purpose of the HCTree is to encode text files in order to compress 
 *  them. Each HCTree holds a vector of each leaf which represents an encoded 
 *  character.
 */
class HCTree {
  private:
    HCNode* root;            // the root of HCTree
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

    /* TODO: add function header */
    void deleteNodes( HCNode * n );

  public:
    /* TODO: add function header and implement */
    HCTree() {

        root = 0;
        leaves =  std::vector<HCNode*>();

    }

    /* TODO: add function header */
    ~HCTree();

    /* TODO: add function header */
    void build(const vector<unsigned int>& freqs);

    /* TODO: add function header */
    void encode(byte symbol, BitOutputStream& out) const;

    /* TODO: add function header */
    void encode(byte symbol, ostream& out) const;

    /* TODO: add function header */
    byte decode(BitInputStream& in) const;

    /* TODO: add function header */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
