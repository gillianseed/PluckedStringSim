/*************** SHOULD BE SAME AS ps4a_CircularBuffer.cpp ***************/
// class definition
// Copyright 2021 Gillian Seed
#include "CircularBuffer.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <exception>  // is this needed?

//  using namespace std;
using std::invalid_argument;
using std::runtime_error;

CircularBuffer::CircularBuffer(int capacity) {
  if (capacity < 1) {
    throw invalid_argument("Constructor: capacity must be greater than zero");
    // try catch block? print exception?
  } else {
    cap = capacity;
    ring_buf.reserve(cap);
  }
}

int CircularBuffer::size() {
  return ring_buf.size();
  }

bool CircularBuffer::isEmpty() {
  // if (sz == 0) return true; // do I need private member?
  if (ring_buf.size() == 0) return true;
  else
    return false;
}

bool CircularBuffer::isFull() {
  // if (sz == cap) return true; // do I need private member?
  if (ring_buf.size() >= cap) return true;
  else
    return false;
}

void CircularBuffer::enqueue(int16_t x) {
  /** try {
      if (isFull()) throw runtime_error("enqueue: can't enqueue to a full ring");
      }
      catch (runtime_error& e) {
      cout << e.what() << endl;
      } **/
  if (isFull()) throw runtime_error("enqueue: can't enqueue to a full ring");
  // catch exception? do I need a try-catch block?
  // use size() member func?
  else
    ring_buf.push_back(x);
  // throw exception?
}

int16_t CircularBuffer::dequeue() {
  /*** try { }
       catch (e) { } **/
  if (isEmpty()) {
    throw runtime_error("dequeue: can't dequeue from an empty buffer");
    // catch exception? try-catch?
    // use size() member func?
  } else {
    int16_t start = ring_buf.front();  // Do I need to use new here?
    ring_buf.erase(ring_buf.begin());
    return start;
  }
  // throw exception?
}

int16_t CircularBuffer::peek() {
  //if (isEmpty()) throw runtime_error("peek: can't peek from an empty buffer");
  // try catch block? print error statement?
  auto lambda = [this]() {
		  if (isEmpty()) {
		    throw runtime_error("peek: can't peek from an empty buffer");
		  }
		};

  // don't you need to call lambda();?
  return ring_buf.front();
}
