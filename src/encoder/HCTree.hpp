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

    /* Helper function for the class destrucctor which recursively deletes the
     * Nodes in the HCTree.
     * Parameter: n - The current HCNode in the recursion.
     */
    void deleteNodes( HCNode * n );

  public:
    /* The default constructor for the HCTree which sets root to 0 and
     * sets leaves to an empty vector of HCNode pointers. There are no
     * input parameters for the constructor since the build method is
     * how each HCTree is individually built. 
     */
    HCTree() {

        root = 0;
        leaves =  std::vector<HCNode*>();

    }

    /* The destructor for the HCTree. */
    ~HCTree();

    /* Takes in a vector of frequencies for each character in ASCII and 
     * creates an HCTree based on them. The higher the frequency, the lower
     * number of bits each character represents. Each actual character is a
     * leaf in the tree rather than a node.
     * Parameter: freqs - the frequencies of each ASCII character for the Tree
     */
    void build(const vector<unsigned int>& freqs);

    /* This method takes in an already build HCTree and encodes
     * a single ASCII character to an output stream. The difference between
     * this signature and the other signature is that this encode writes to 
     * a BitOutputStream instead of just an ostream.
     * Parameter: symbol - the single byte that we are encoding
     * Parameter: out - the output stream we are writing single bits to
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /* This method takes in an already build HCTree and encodes
     * a single ASCII character to an output stream. The difference between
     * this signature and the other signature is that this encode writes chars
     * to an ostream instead of bits to a BitOutputStream.
     * Parameter: symbol - the single byte that we are encoding
     * Parameter: out - the output stream we are writing characters to
     */
    void encode(byte symbol, ostream& out) const;

    /* This method uses an already build HCTree and decodes a single ASCII
     * charcter from an input stream and returns it. This version of the 
     * decode uses a BitInputStream instead of an istream in order to read
     * bits instead of chars.
     * Parameter: in - the BitInputStream we are reading bits from.
     */
    byte decode(BitInputStream& in) const;

    /* This method uses an already build HCTree and decodes a single ASCII
     * charcter from an input stream and returns it. This version of the 
     * decode uses a istream so it reads chars instead of bits.
     * Parameter: in - the istream we are reading chars from.
     */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
