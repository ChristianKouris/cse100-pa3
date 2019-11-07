/**
 * TODO: file header
 *
 * Author:
 * Sources: Stepik Chapter 7.3 tree build visualization
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
            unsigned char ch = i;
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

/* TODO */
void HCTree::encode(byte symbol, ostream& out) const {}

/* TODO */
byte HCTree::decode(BitInputStream& in) const { return ' '; }

/* TODO */
byte HCTree::decode(istream& in) const { return ' '; }

void HCTree::deleteNodes( HCNode * n ) {

    if( n == nullptr ) { return; }
    deleteNodes( n->c0 );
    deleteNodes( n->c1 );
    delete n;

}
