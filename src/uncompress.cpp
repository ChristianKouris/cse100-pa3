/**
 * TODO: file header
 *
 * Author: Chrisitan Kouris
 * Sources: cplusplus reference isream/ostream/ifstream/ofstream, std::vector,
 *          std::stoul
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

#define NUM_ARGS 3

/* TODO: Pseudo decompression with ascii encoding and naive header (checkpoint)
 */
void pseudoDecompression(string inFileName, string outFileName) {

    //open the infile for reading and the outfile for writing
    ifstream infile( inFileName, ios::in );
    
    //get the frequencies of each character
    vector<unsigned int> freqs = std::vector<unsigned int>(256, 0);
    for( byte i = 0; i < freqs.size(); i++ ) {

        char charFreq[BUFSIZ];
        infile.getline( charFreq, BUFSIZ );
        unsigned int fr = std::stoul( charFreq );
        freqs[i] = fr;

    }

    //build a HC tree using freqs
    HCTree hctree = HCTree();
    hctree.build( freqs );

    //decode each character using the HC tree and put it in outfile
    ofstream outfile( outFileName, ios::out | ios::trunc );
    while( !infile.eof() ) {
        outfile << hctree.decode( infile );
    }

    //close the files
    infile.close();
    outfile.close();

}

/* TODO: True decompression with bitwise i/o and small header (final) */
void trueDecompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the uncompress */
int main(int argc, char* argv[]) { 
    
    //first check to see if there are only 2 arguments
    if( argc != NUM_ARGS ) {
        return 0;
    }

    //call the pseudoCompression method
    pseudoDecompression( argv[1], argv[2] );

}
