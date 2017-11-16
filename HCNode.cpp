/*
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 6, 2016
 * File: HCNode.cpp
 */

#include "HCNode.hpp"

/**
 * Compare this HCNode and other for priority odering.
 * Smaller count means higher priority.
 * Use node symbol for deterministic tiebreaking
 */
bool HCNode::operator<(const HCNode& other) {

  //if counts are different, just compare counts
  if( count != other.count) return count > other.count;

  //counts are equal, use symbol value to break tie.
  return symbol < other.symbol;
}



