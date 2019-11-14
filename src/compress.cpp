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
#include "cxxopts.hpp"

#define NUM_ARGS 3

/* TODO: add pseudo compression with ascii encoding and naive header
 * (checkpoint) */
void pseudoCompression(string inFileName, string outFileName) {
    
    //open the infile for reading
    ifstream infile;
    infile.open( inFileName, ios::in );
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
    infile.close();
    infile.open( inFileName, ios::in );
    ofstream outfile( outFileName, ios::out | ios::trunc );

    //print the header for the array
    for( unsigned int i = 0; i < 256; i++ ) {
        outfile << freqs[i] << endl;
    }

    //encode each character using the HC tree and put it in outfile
    while( infile.peek() != EOF ) {
        hctree.encode( infile.get(), outfile );
    }
    //close the files
    infile.close();
    outfile.close();

}

/* TODO: True compression with bitwise i/o and small header (final) */
void trueCompression(string inFileName, string outFileName) {}

/* TODO: Main program that runs the compress */
int main(int argc, char* argv[]) { 

    //implementation given in pa3 writeup
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");
 
    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");
 
    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);
 
    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName) ||
        outFileName.empty()) {
        cout << options.help({""}) << std::endl;
        exit(0);
    }

    //use isAsciiOutput to determine wether to use psuedo or real compression
    if( isAsciiOutput ) {
        pseudoCompression( inFileName, outFileName );
    } else {
        trueCompression( inFileName, outFileName );
    }

    return 0;
}
