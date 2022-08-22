#include "CircularBuffer.hpp"
#include "StringSound.hpp"
#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;

int main(int argc, char* argv[]) {
  string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
  string drumkey = "1as36hl0-";
  int i;  // keyboard index
  double f;  // frequency calculated
  
  sf::RenderWindow window(sf::VideoMode(1200, 350), "My Guitar That Looks Like A Piano");
  sf::Texture texture;
  if(!texture.loadFromFile("piano.png")) return EXIT_FAILURE;
  sf::Sprite sprite(texture);

  vector<vector<sf::Int16>> streams;
  vector<sf::SoundBuffer> buffers(37);
  vector<sf::Sound> sounds(37);

  vector<sf::Int16> samp;
  
  for(int i = 0; i < 37; i++) {
    f = 440*pow(2.0, (i - 24.0)/12.0);
    StringSound string(f);
    samp = makeSamples(string);
    streams.push_back(samp);

    if (!(buffers.at(i)).loadFromSamples(&samp[0], samp.size(), 2, 44100)) return EXIT_FAILURE;

    (sounds.at(i)).setBuffer(buffers.at(i));
  }

  vector<vector<sf::Int16>> drumStreams;
  vector<sf::SoundBuffer> drumBuffers(9);
  vector<sf::Sound> drumSounds(9);
  vector<sf::Int16> drumSamp;

  double drumf;
  
  for(int i = 0; i < 9; i++) {
    drumf = 440*pow(2.0, (i - 24.0)/ 12.0);
    DrumSound drumString(drumf);
    drumSamp = makeDrumSamples(drumString);
    drumStreams.push_back(drumSamp);

    if (!(drumBuffers.at(i)).loadFromSamples(&samp[0], samp.size(), 2, 44100)) return EXIT_FAILURE;

    (drumSounds.at(i)).setBuffer(drumBuffers.at(i));
  }
  
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if(event.type == sf::Event::Closed)
	window.close();
      else if (event.type == sf::Event::TextEntered) {
	char key = static_cast<char>(event.text.unicode);
	int keyIndex = keyboard.find(key);
	int drumIndex = drumkey.find(key);
	if (keyIndex != string::npos) (sounds.at(keyIndex)).play();
      else (drumSounds.at(drumIndex)).play();
      }
    }
    window.clear();
    window.draw(sprite);
    window.display();
  }
  return EXIT_SUCCESS;
}
