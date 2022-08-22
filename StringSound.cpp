#include "StringSound.hpp"
#include "CircularBuffer.hpp"
#include <stdint.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace std;

StringSound::StringSound(double frequency) {
  // sampling rate of 44,100 Hz
  N = ceil(44100.0/frequency);
  // N is number of samples and ceil() rounds up
  _time = 0;

  // N is going to be our buffer capacity
  _cb = new CircularBuffer(N);
}

StringSound::StringSound(vector<sf::Int16> init) {
  // create guitar string with size and initial values given by the vector
  _cb = new CircularBuffer(init.size());
  _time = 0;
  
  for(int i = 0; i < init.size(); i++) {
    _cb->enqueue((int16_t)init.at(i));
  }
}


void StringSound::pluck() {
  // pluck guitar string by replacing buffer with random values, representing
  // white noise
  // check if buffer is full, and clear it if so

  while(!(_cb->isEmpty())) { _cb->dequeue(); }
  
  for (int i = 0; i < N; i++) {
    int16_t sample = (int16_t)(rand() % 65536);
    // sample is in range 0 to 65,535
    
    sample -= 32768;
    // sample is now in range -32,768 to 32,767
    
    _cb->enqueue(sample);
  }
}

void StringSound::tic() {
  // advance the simulation one time step
  int16_t rmSample = _cb->dequeue();
  int16_t newFront = _cb->peek();
  int16_t newSample = 0.996*(rmSample + newFront)/2;
  _cb->enqueue(newSample);
  _time += 1;
}

sf::Int16 StringSound::sample() {
  // return the current sample
  return (sf::Int16)_cb->peek();
}

int StringSound::time() {
  // return number of times tic was called so far
  return _time;
}

vector<sf::Int16> makeSamples(StringSound& string) {
  vector<sf::Int16> samples;

  string.pluck();
  int dur = 8;  // duration = 8 sec
  for (int i = 0; i < 44100*dur; i++) {
    string.tic();
    samples.push_back(string.sample());
  }
  return samples;
}

DrumSound::DrumSound(double frequency) {
  N = ceil(44100.0/frequency);
  _time = 0;
  _cb = new CircularBuffer(N);
}

DrumSound::DrumSound(vector<sf::Int16> init) {
  _cb = new CircularBuffer(init.size());
  _time = 0;
  for(int i = 0; i < init.size(); i++) {
    _cb->enqueue((int16_t)init.at(i));
  }
}


void DrumSound::pluck() {
  while(!(_cb->isEmpty())) { _cb->dequeue(); }
  for (int i = 0; i < N; i++) {
    int16_t sample = (int16_t)(rand() % 65536);
    // sample is in range 0 to 65,535
    
    sample -= 32768;
    // sample is now in range -32,768 to 32,767
    _cb->enqueue(sample);
  }
}

void DrumSound::tic() {
  // advance the simulation one time step
  int16_t rmSample = _cb->dequeue();
  int16_t newFront = _cb->peek();
  int16_t newSample = 0.996*(rmSample + newFront)/4;
  _cb->enqueue(newSample);
  _time += 1;
}

sf::Int16 DrumSound::sample() {
  // return the current sample
  return (sf::Int16)_cb->peek();
}

int DrumSound::time() {
  // return number of times tic was called so far
  return _time;
}

vector<sf::Int16> makeDrumSamples(DrumSound& string) {
  vector<sf::Int16> samples;

  string.pluck();
  int dur = 8;  // duration = 8 sec
  for (int i = 0; i < 44100*dur; i++) {
    string.tic();
    samples.push_back(string.sample());
  }
  return samples;
}
