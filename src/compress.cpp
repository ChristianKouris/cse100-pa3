/**
 * TODO: file header
 *
 * Author:
 * Sources: cplusplus reference isream/ostream/ifstream/ofstream, std::vector,
 *          
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

#define NUM_ARGS 3

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    
    //open the infile for reading
    ifstream infile( inFileName, ios::in );
    //get the frequencies of each character
    vector<unsigned int> freqs = std::vector<unsigned int>(256, 0);
    char ch;
    while( infile.get( ch ) ) {
        freqs[ch]++;
    }
    //build a HC tree using freqs
    HCTree hctree = HCTree();
    hctree.build( freqs );

    //set the infile to the beginning and open the outfile
    infile.seekg(0);
    ofstream outfile( outFileName, ios::out | ios::trunc );

    //print the header for the array
    for( unsigned int i = 0; i < freqs.size(); i++ ) {
        outfile << freqs[i] << endl;
    }

    //encode each character using the HC tree and put it in outfile
    while( infile.get(ch) ) {
        hctree.encode( ch, outfile );
    }
    //close the files
    infile.close();
    outfile.close();

}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 

    //first check to see if there are only 2 arguments
    if( argc != NUM_ARGS ) {
        return 0;
    }

    //call the pseudoCompression method
    pseudoCompression( argv[1], argv[2] );


}
