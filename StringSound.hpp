#ifndef STRINGSOUND_HPP
#define STRINGSOUND_HPP

#include "CircularBuffer.hpp"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

class StringSound {
public:
  explicit StringSound (double frequency);
  explicit StringSound (vector<sf::Int16> init);
  StringSound (const StringSound &obj) {};
  ~ StringSound() { delete _cb; }
  void pluck();
  void tic();
  sf::Int16 sample();
  int time();
private:
  CircularBuffer * _cb;
  int _time;
  int N;
};

class DrumSound {
public:
  explicit DrumSound (double frequency);
  explicit DrumSound(vector<sf::Int16> init);
  DrumSound (const DrumSound &obj) {};
  ~ DrumSound() { delete _cb; }
  void pluck();
  void tic();
  sf::Int16 sample();
  int time();
private:
  CircularBuffer *_cb;
  int _time;
  int N;
};

vector<sf::Int16> makeSamples(StringSound& string);
vector<sf::Int16> makeDrumSamples(DrumSound& string);

#endif
