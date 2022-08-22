// Copyright 2021 Gillian Seed
#include "CircularBuffer.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <exception>

using std::invalid_argument;
using std::runtime_error;

CircularBuffer::CircularBuffer(int capacity) {
  if (capacity < 1) {
    throw invalid_argument("Constructor: capacity must be greater than zero");
  } else {
    cap = capacity;
    ring_buf.reserve(cap);
  }
}

int CircularBuffer::size() {
  return ring_buf.size();
  }

bool CircularBuffer::isEmpty() {
  if (ring_buf.size() == 0) return true;
  else
    return false;
}

bool CircularBuffer::isFull() {
  if (ring_buf.size() >= cap) return true;
  else
    return false;
}

void CircularBuffer::enqueue(int16_t x) {
  if (isFull()) throw runtime_error("enqueue: can't enqueue to a full ring");
  else
    ring_buf.push_back(x);
}

int16_t CircularBuffer::dequeue() {
  if (isEmpty()) {
    throw runtime_error("dequeue: can't dequeue from empty buffer");
  } else {
    int16_t start = ring_buf.front();
    ring_buf.erase(ring_buf.begin());
    return start;
  }
}

int16_t CircularBuffer::peek() {
  auto lambda = [this]() {
		  if (isEmpty()) {
		    throw runtime_error("peek: can't peek from empty buffer");
		  }
		};
  lambda();
  return ring_buf.front();
}
