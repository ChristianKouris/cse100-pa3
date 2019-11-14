/**
 * This file takes in an input file along with an output file as well as 
 * arguments if necessary. The program will then use huffman encoding
 * to uncompress the input file and write it to the output file.
 *
 * Author: Chrisitan Kouris
 * Email: ckouris@ucsd.edu
 * Sources: cplusplus reference isream/ostream/ifstream/ofstream, std::vector,
 *          std::stoul
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

#define NUM_ARGS 3

/* This program reads the header that was included in the encrypted 
 * input file and builds an HCTree off of them. The HCTree is then used to
 * decode the infile and write the original chars to the outfile.
 * Parameter: inFileName - the name of the input file
 * Parameter: outFileName - the name of the output file
 */
void pseudoDecompression(string inFileName, string outFileName) {

    //open the infile for reading and the outfile for writing
    ifstream infile;
    infile.open( inFileName, ios::in );
    
    //get the frequencies of each character
    vector<unsigned int> freqs = std::vector<unsigned int>(256, 0);
    for( unsigned int i = 0; i < 256; i++ ) {

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
    while( infile.peek() != EOF ) {
        outfile << hctree.decode( infile );
    }

    //close the files
    infile.close();
    outfile.close();

}

/* This program reads the header that was included in the encrypted input
 * file and builds an HCTree off of them. The HCTree is then used to decode
 * the bits from the infile and write the original chars to the outfile.
 * Parameter: inFileName - the name of the input file
 * Parameter: outFileName - the name of the output file
 */
void trueDecompression(string inFileName, string outFileName) {}

/* The main driver for uncompress.cpp which uses cxxopts for arg processing.
 * Parameter: argc - the count of all the arguments
 * Parameter: argv - an array of all of the arguments
 */
int main(int argc, char* argv[]) { 
    
    //implementation given in pa3 writeup
    cxxopts::Options options("./uncompress",
                             "Decompresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");
 
    bool isAsciiOutput = false;
    string inFileName, outFileName;
    options.allow_unrecognised_options().add_options()(
        "ascii", "Take input in ascii mode instead of bit stream",
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
    if( true/*isAsciiOutput*/ ) {
        pseudoDecompression( inFileName, outFileName );
    } else {
        trueDecompression( inFileName, outFileName );
    }

    return 0;

}
