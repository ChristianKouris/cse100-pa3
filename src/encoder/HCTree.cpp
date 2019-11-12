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

/* Add function header from hpp file */
HCTree::~HCTree() {

    deleteNodes( root );

}

/* Add function header from hpp file */
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
    root = forest[0];

}

/* TODO */
void HCTree::encode(byte symbol, BitOutputStream& out) const {}

/* Add function header from hpp file */
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

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* Add function header from hpp file */
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

/* Add function header from hpp file */
void HCTree::deleteNodes( HCNode * n ) {

    if( n == nullptr ) { return; }
    deleteNodes( n->c0 );
    deleteNodes( n->c1 );
    delete n;

}
