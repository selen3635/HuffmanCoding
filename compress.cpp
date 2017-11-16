/**
  * Name: Ziying Hu & Xiaolong Zhou
  * Login: cs100vat & cs100vcc
  * Date: Aug 8, 2016
  * File: compress.cpp
  */

#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>

using namespace std;

/* 
 * main driver of the compress process
 * return 0 for exit success, other otherwise
 */
int main( int argc, char* argv[]) {

  /* check for arguments */
  if ( argc != 3 ) {
    cout << "Invalid number of arguments.\n"
         << "Usage: ./compress <infile> <outfile>.\n";
    return -1;
  }

  /* open file */
  ifstream input;
  input.open(argv[1], ios::binary);

  /* check if file was actually opened */
  if ( !input.is_open() ) {
    cout << "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }

  /* check if was empty */
  input.seekg( 0, ios_base::end );
  unsigned int length = input.tellg();
  if ( length == 0 ) {
    cout << "The file is empty.\n";
    return -1;
  }

  /* resets the stream to beginning of file */
  input.seekg( 0, ios_base::beg );


  /*****************************
   * Main function 
   *
   */

  /* read the file byte by byte and count the frequency */
  vector<int> frequency = vector<int>(256, 0);

  /* while is not the end of file */
  while ( 1 ) {
    int character = input.get();
    if( input.eof())
      break;
    frequency[character]++;

  }

  /* close the file */
  if ( input.is_open() ) 
    input.close();

  /* build a huffman trie */
  HCTree myTree;
  myTree.build(frequency);

  /* open the output file for writing */
  ofstream output;
  output.open( argv[2], ios::binary );

  /* check if file was actually opened */
  if ( !output.is_open() ) {
    cout << "Invalid output file. No file was opened. Please try again.\n";
    return -1;
  }

  /* write the file header */
  //for ( int i = 0; i < frequency.size(); i++ ) {

    //output << frequency[i] << endl;
  //}

  /** write the frequency */
  int count = myTree.myCount();
  output << count << endl;

  /** efficient way to print header */
  myTree.printHeader(myTree.getRoot(), output);
  output<< endl;


  /* open the input file again */
  input.open( argv[1], ios::binary );

  byte myChar;
  /* create a BitOutputStream object */
  BitOutputStream myOutput(output);
  /* translate the input file into haffman code based on the tree */
  while ( 1 ) {

    myChar = input.get(); 
    if( input.eof())
      break;

    myTree.encode( myChar, myOutput );
  }
  myOutput.flush();

  /* close the files */
  if ( input.is_open() )
    input.close();
  if ( output.is_open() )
    output.close();
  
  return 0;
}
