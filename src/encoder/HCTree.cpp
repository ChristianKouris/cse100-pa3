/**
 * This cpp file takes all of the methods defined in the hpp file and 
 * writes implementation for it. The build method takes in a vector of
 * frequencies and builds a corresponding tree. the encode and decode
 * methods each have two different signatures depending on if we want to 
 * use a normal i/ostream or a biti/ostream.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: Stepik Chapter 7.3 tree build visualization,
 *          cplusplus reference for: std::vector, std::sort, ostream, istream
 */
#include "HCTree.hpp"

/* The destructor for the HCTree. */
HCTree::~HCTree() {

    deleteNodes( root );

}

/* Takes in a vector of frequencies for each character in ASCII and 
 * creates an HCTree based on them. The higher the frequency, the lower
 * number of bits each character represents. Each actual character is a
 * leaf in the tree rather than a node.
 * Parameter: freqs - the frequencies of each ASCII character for the Tree
 */
void HCTree::build(const vector<unsigned int>& freqs) {

    
    //weed out the 0 freq chars, add the chars to a node in vector leaves
    for( unsigned int i = 0; i < freqs.size(); i++ ) {
        if( freqs[i] != 0 ) {
            byte ch = i;
            HCNode * validNode = new HCNode( freqs[i], ch );
            leaves.push_back( validNode );
        }
    }
    
    //create a temp vector to hold all the root nodes
    vector<HCNode*> forest = leaves;

    //keep building the subtrees until we are left with a single tree
    while( forest.size() > 1 ) {

        std::sort( forest.begin(), forest.end(), HCNodePtrComp() );
        //get the two nodes at the end and give them a parent
        HCNode* zeroNode = forest.back();
        forest.pop_back();
        HCNode* oneNode = forest.back();
        forest.pop_back();
        //parent for both nodes has added freq, both as children, no char
        HCNode* parentNode = new HCNode( zeroNode->count + oneNode->count, 0, 
                                         zeroNode, oneNode );
        //set both nodes' parent to be new node and add it to the forest
        oneNode->p = parentNode;
        zeroNode->p = parentNode;
        forest.push_back( parentNode );

    }

    //set the root to be the last pointer of forest
    if( forest.size() > 0 ) {
        root = forest[0];
    }

}

/* This method takes in an already build HCTree and encodes
 * a single ASCII character to an output stream. The difference between
 * this signature and the other signature is that this encode writes to 
 * a BitOutputStream instead of just an ostream.
 * Parameter: symbol - the single byte that we are encoding
 * Parameter: out - the output stream we are writing single bits to
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {

    //search through the leaves and find the node for our symbol
    HCNode * curNode = nullptr;
    for( unsigned int i = 0; i < leaves.size(); i++ ) {
        if( leaves[i]->symbol == symbol ) {
            curNode = leaves[i];
            break;
        }
    }

    unsigned int encSymb = 0; unsigned int nbits = 0;
    while( curNode != root ) {
        
        //check to see if we are a 0 or 1 child
        unsigned int curBit = 0;
        if( curNode == curNode->p->c1 ) {
            curBit = 1;
        }
        
        encSymb = (encSymb << 1) | curBit;
        nbits++;
        curNode = curNode->p;
    
    }

    for( unsigned int i = nbits; i > 0; i-- ) {

        out.writeBit( (encSymb >> (i-1)) & 1 );
    
    }

}

/* This method takes in an already build HCTree and encodes
 * a single ASCII character to an output stream. The difference between
 * this signature and the other signature is that this encode writes chars
 * to an ostream instead of bits to a BitOutputStream.
 * Parameter: symbol - the single byte that we are encoding
 * Parameter: out - the output stream we are writing characters to
 */
void HCTree::encode(byte symbol, ostream& out) const {

    //search through the leaves and find the node for our symbol
    HCNode * curNode = nullptr;
    for( unsigned int i = 0; i < leaves.size(); i++ ) {
        if( leaves[i]->symbol == symbol ) {
            curNode = leaves[i];
            break;
        }
    }
    
    string encSymb = "";
    //go up the tree to get the message
    while( curNode != root ) {
        
        //check to see if we are a 0 or 1 child
        char curBit = '0';
        if( curNode == curNode->p->c1 ) {
            curBit = '1';
        }
        
        encSymb = curBit + encSymb;
        curNode = curNode->p;

    }

    //write the string to the ostream
    out << encSymb;

}

/* This method uses an already build HCTree and decodes a single ASCII
 * charcter from an input stream and returns it. This version of the 
 * decode uses a BitInputStream instead of an istream in order to read
 * bits instead of chars.
 * Parameter: in - the BitInputStream we are reading bits from.
 */
byte HCTree::decode(BitInputStream& in) const { 
    
    //start at the root node
    HCNode * curNode = root;

    //go down the tree reading each char until we reach a leaf
    while( curNode->c0 != 0 && curNode->c1 != 0 ) {

        if( in.readBit() == 1 ) {

            curNode = curNode->c1;

        } else {

            curNode = curNode->c0;

        }

    }

    return curNode->symbol; 

}

/* This method uses an already build HCTree and decodes a single ASCII
 * charcter from an input stream and returns it. This version of the 
 * decode uses a istream so it reads chars instead of bits.
 * Parameter: in - the istream we are reading chars from.
 */
byte HCTree::decode(istream& in) const {
    
    //start at the root node
    HCNode * curNode = root;

    //go down the tree reading each char until we reach a leaf
    while( curNode->c0 != 0 && curNode->c1 != 0 ) {

        if( in.get() == '1' ) {

            curNode = curNode->c1;

        } else {

            curNode = curNode->c0;

        }

    }

    return curNode->symbol; 

}

/* Helper function for the class destrucctor which recursively deletes the
 * Nodes in the HCTree.
 * Parameter: n - The current HCNode in the recursion.
 */
void HCTree::deleteNodes( HCNode * n ) {

    if( n == nullptr ) { return; }
    deleteNodes( n->c0 );
    deleteNodes( n->c1 );
    delete n;

}
