/*
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 8, 2016
 * File: HCTree.cpp
 */
#include "HCTree.hpp"
#include <queue>
#include <stack>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"

/* destructor */
HCTree::~HCTree() {

  deleteAll(root);
  root = nullptr;
  return;  

}


/** a function to delete all node on the tree */
void HCTree::deleteAll(HCNode* n) {

  /** base case */
  if ( n == nullptr ) return;
  /* recursively call to delete all node */
  deleteAll(n->c0);
  deleteAll(n->c1);
  delete n;
  n = 0;

}

/** build a huffman coding trie */
void HCTree::build(const vector<int>& freqs) {

  /* declare a priority queue */
  std::priority_queue<HCNode*,vector<HCNode*>,HCNodePtrComp> myQ;

  /* a loop to push all freqs to priority queue */
  for( int i = 0; i < freqs.size(); i++) {

    /* check whether frequence is 0 */
    if( freqs[i] != 0 ) {
      leaves[i] = new HCNode( freqs[i], i, 0, 0, 0 );
      myQ.push(leaves[i]);
    }
  }

  if ( myQ.size() > 1 ) {
    /* a loop to build huffman tree */
    while ( myQ.size() > 1 ) {

      /* pop the two smallest element */
      auto smallest = myQ.top();
      myQ.pop();
      auto small = myQ.top();
      myQ.pop();

      /** create a new root for two smallest leaves */
      auto myRoot = new HCNode((smallest->count + small->count), 
          smallest->symbol,smallest, small, 0);

      /** set two smalllest leaves parent to myRoot */
      smallest->p = small->p = myRoot;

      myQ.push(myRoot);
    }//end of while

    /** set root to the top of queue */
    root = myQ.top();
  }
  /* if it is only one node */
  else {
    auto myRoot = new HCNode( myQ.top()->count, myQ.top()->symbol, myQ.top(),
        0,0);

    myQ.top()->p = myRoot;
    root = myRoot;
  }
}//end of build

/** encode the message with given ofstream */
void HCTree::encode(byte symbol, ofstream& out) const {

  char myCode[BUFSIZ];
  HCNode* curNode = leaves[symbol];
  int i = 0;

  /* start from the leaves to encode */
  while( curNode != root ) {

    /* if it is the left child */
    if( curNode == curNode->p->c0 ) {
      myCode[i] = '0';
    }
    /* if it is the right child */
    else {
      myCode[i] = '1';
    }

    curNode = curNode->p;
    i++;

  }//end of while

  /* write the encoded information reversely */
  for( ; i > 0; i--) {

    out<< myCode[i-1];

  }

}//end of encode

/** Return the symbol coded in the next sequence of bits (represented as  
 *  ASCII text) from the ifstream. 
 *  PRECONDITION: build() has been called, to create the coding 
 *  tree, and initialize root pointer and leaves vector. 
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED 
 *  IN THE FINAL SUBMISSION. 
 */
int HCTree::decode(ifstream& in) const {

  /** set current node to root */
  HCNode* curNode = root;

  /* while the curNode is not leaf */
  while ( curNode->c0 != nullptr || curNode->c1 != nullptr ) {


    /* if the character of the file is 1 */
    if ( in.get() == '1' ) {
      curNode = curNode->c1;
    } 
    /** check whether reach the end of file */   
    else if(in.eof())
      return -1;


    /* if is 0 */
    else {
      curNode = curNode->c0;
    }
  }

  return curNode->symbol;

}//end of decode

/**
  * Output the file header by using postorder traversal of the tree
  */
void HCTree::printHeader(HCNode* root, ofstream& out) {

  /* base case for the recursive call */
  if( root == nullptr )
    return;

  printHeader(root->c0, out);
  printHeader(root->c1, out);
  /* determine whether its leave node */
  if( root->c0 == nullptr && root->c1 == nullptr) {

    out << '1';
    out << root->symbol;
  }
  /* if it is a root node */
  else {
    out << '0';
  }
    
}

/** a helper method to get root */
HCNode* HCTree::getRoot() const {

  return root;

}

/** Rebuild tree according to header file*/
void HCTree::build( ifstream& in ) {

  /** create a stack */
  std::stack<HCNode*> myStack;

  while(1) {

    int num = in.get();

    /* if it is 1, it must be a child */
    if( num == '1' ) {

      /* store the byte to the node */
      byte myChar = in.get();
      HCNode* myNode = new HCNode(0, myChar, 0,0,0);
      myStack.push(myNode);


    }
    /* if it is 0, it must be a root */
    else if ( num == '0' ){
    
      /* if the stack is larger than 1 */
      if ( myStack.size() > 1 ) {

        /* pop the left and right child */
        auto right = myStack.top();
        myStack.pop();
        auto left = myStack.top();
        myStack.pop();

        /* create a root node */
        HCNode* myRoot = new HCNode(0, left->symbol, left, right, 0 );

        left->p = right->p = myRoot;

        /* push it to the stack again */
        myStack.push(myRoot);

      } 
      /* if there is only one node in the stack */
      else{

        /* pop the only node */
        auto left = myStack.top();
        myStack.pop();

        /* create a root node */
        HCNode* myRoot = new HCNode(0, left->symbol, left, 0, 0);

        left->p = myRoot;

        myStack.push(myRoot);

      }

    }//end of else if
    else if ( num == '\n' ) {
      break;
    }

  }//end of while

  root = myStack.top();

}

/**
  * Write to the given BitOutputStream
  * the sequence of bits coding the given symbol.
  */
void HCTree::encode(byte symbol, BitOutputStream & out) const {

  HCNode* curNode = leaves[symbol];
  int myCode[BUFSIZ];
  int i = 0;


  /** a loop from leave of tree to root */
  while ( curNode != root ) {

    /** If it is parent left child, write 0 */
    if ( curNode == curNode->p->c0 ) {
      myCode[i] = 0;      
    }
    /** it is right child, write 1 */
    else {
      myCode[i] = 1;
    }

    /** set curNode to its parent */
    curNode = curNode->p;
    i++;

  }//end of while


  /* write the encoded information reversely */
  for( ; i > 0; i--) {
    out.writeBit(myCode[i-1]);

  }

}

/**
  * Return the symbol coded in the next sequence of bit form the stream.
  */
int HCTree::decode(BitInputStream & in ) const {

  /* set current node to root */
  HCNode* curNode = root;

  /* while current node is not leaf */
  while(curNode->c0 != nullptr || curNode->c1 != nullptr ) {

    int read = in.readBit();

    /* check if we get eof */
    if( read == EOF ) {

      return EOF;
    }
    else if( read == 1 ) {
      curNode = curNode->c1;
    }
    else {
      curNode = curNode->c0;
    }

  }//end of while

  return curNode->symbol;

}

/**
  * Return the number of items in the HCTree
  */
unsigned int HCTree::myCount() {
  return root->count;
}
