/**
 * This file takes in an input file along with an output file as well as 
 * arguments if necessary. The program will then use huffman encoding
 * to compress the input file and write it to the output file.
 *
 * Author: Christian Kouris
 * Email: ckouris@ucsd.edu
 * Sources: cplusplus reference isream/ostream/ifstream/ofstream, std::vector,
 *          
 */
#include <fstream>
#include <iostream>

#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
#include "cxxopts.hpp"

/* Reads all the characters from the infile and counts their frequencies. It
 * then builds a HCTree using the frequencies and encodes the characters in 
 * the input file and writes them to the output file.
 * Parameter: inFileName - the name of the input file
 * Parameter: outFileName - the name of the output file
 */
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
    ofstream outfile;
    outfile.open( outFileName, ios::out | ios::trunc );

    //print the header for the array
    for( unsigned int i = 0; i < 256; i++ ) {
        outfile << freqs[i] << endl;
    }

    //encode each character using the HC tree and put it in outfile
    while( infile.peek() != EOF ) {
        char ch = infile.get();
        hctree.encode( ch, outfile );
    }
    //close the files
    infile.close();
    outfile.close();

}

/* Reads all the characters from the infile and counts their frequencies. It
 * then builds a HCTree using the frequencies and encodes the characters in 
 * the input file. The encoded bits are written to outfile using a bit stream.
 * Parameter: inFileName - the name of the input file
 * Parameter: outFileName - the name of the output file
 */
void trueCompression(string inFileName, string outFileName) {

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
    ofstream outfile;
    outfile.open( outFileName, ios::out | ios::trunc );

    //print the header for the array
    for( unsigned int i = 0; i < 256; i++ ) {
        outfile << freqs[i] << endl;
    }

    //create a bit input stream for infile and outfile
    BitOutputStream bOutfile = BitOutputStream( outfile );

    //encode each character using the HC tree and put it in bit outputStream
    while( infile.peek() != EOF ) {

        char ch = infile.get();
        hctree.encode( ch, bOutfile );

    }
    //close the files
    infile.close();
    outfile.close();

}

/* The main driver for compress.cpp which uses cxxopts for arg processing.
 * Parameter: argc - the count of all the arguments
 * Parameter: argv - an array of all of the arguments
 */
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
