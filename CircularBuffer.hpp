#ifndef CIRCULARBUFFER_HPP
#define CIRCULARBUFFER_HPP

#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

class CircularBuffer {
public:
  CircularBuffer(int capacity);
  int size();
  bool isEmpty();
  bool isFull();
  void enqueue(int16_t x);
  int16_t dequeue();
  int16_t peek();
private:
  int cap;
  vector<int16_t> ring_buf;
};

#endif
