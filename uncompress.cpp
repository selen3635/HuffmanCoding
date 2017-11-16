/**
  * Name: Ziying Hu & Xiaolong Zhou
  * Login: cs100vat & cs100vcc
  * Date: Aug 8, 2016
  * File: uncompress.cpp
  */

#include "HCTree.hpp"
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include <iostream>
#include <fstream>

using namespace std;


/*
 * main driver of the uncompress process
 * return 0 for exti success, other otherwise
 */
int main( int argc, char* argv[] ) {

  /** check for argument */
  if( argc != 3 ) {

    cout << "Invalid number of arguments. \n"
      << "Usage: ./uncompress <infile> <outfile>. \n";
    
    return -1;
  }

  /** open file */
  ifstream input;
  input.open(argv[1], ios::binary);

  /** check if file was actually opened */
  if( !input.is_open() ) {

    cout << "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }

  /** check if was empty */
  input.seekg(0, ios_base::end);
  unsigned int length = input.tellg();
  if( length == 0 ) {
    cout << "The file is empty. \n";
  }

  /** resets the stream to begining of file */
  input.seekg(0, ios_base::beg);

  /*****
   * Main function
   */

  //vector<int> frequency = vector<int>(256, 0);

  /** a loop to read the header file */
  //for( int i = 0; i < frequency.size(); i++ ) {

    //input >> frequency[i];

  //}

  /* read the number of symbol */
  int totalFreqs;
  input >> totalFreqs;
  (void) input.get();
  
  /* reconstruct hufman tree */
  HCTree myTree;
  myTree.build(input);


  /* open output file for writing */
  ofstream output;
  output.open(argv[2], ios::binary);

  /** call constructor */
  BitInputStream myInput(input);


  /* check if file was actually opened */
  if( !output.is_open() ) {
    cout << "Invalid output file. Nofile was opened. Please try again. \n";
    return -1;
  }

  myInput.fill();

  int j = 0;
  while(1) {

    /* decode the bits from the input file into the output file */
    int myCode = myTree.decode(myInput);
    if( myCode == EOF)
      break;
    /* conditions to stop */
    if(totalFreqs == j)
      break;
    
    output.put( (unsigned char)myCode);
    j++;
  }

  /* close the files */
  if ( input.is_open() ) 
    input.close();
  if( output.is_open() ) 
    output.close();

  return 0;

}// end of main
