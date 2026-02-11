#include <array>
// Aidan Carey, main.cpp

#include <algorithm>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <SFML/Graphics.hpp>

#include "algorithms.hpp"

int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1000, 1200)), "Sorting");
  //window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(20);
  
  sf::Vector2u size = window.getSize();

  // create, fill, and shuffle array
  std::array<int, SIZE> array;
  std::iota(array.begin(), array.end(), 1);
  std::shuffle(array.begin(), array.end(),
               std::default_random_engine(std::time(0)));

  int step = 0;
  bool done = false;
  bool paused = false;

  // text at top left
  sf::Font font("Roboto-Light.ttf");
  sf::Text text(font), stepCounter(font), helpText(font), doneText(font);

  text.setString("Selection Sort");
  text.setFillColor(sf::Color::Green);
  text.setFont(font);
  text.setCharacterSize(20);
  text.setPosition(sf::Vector2f(5, 5));

  stepCounter.setFillColor(sf::Color::Green);
  stepCounter.setFont(font);
  stepCounter.setCharacterSize(20);
  stepCounter.setPosition(sf::Vector2f(5, 25));

  helpText.setString("Space to pause, R to reset");
  helpText.setFillColor(sf::Color::Green);
  helpText.setFont(font);
  helpText.setCharacterSize(20);
  helpText.setPosition(sf::Vector2f(5, 45));

  doneText.setString("Sorting...");
  doneText.setFillColor(sf::Color::Green);
  doneText.setFont(font);
  doneText.setCharacterSize(20);
  doneText.setPosition(sf::Vector2f(5, 65));

  // main loop
  while (window.isOpen()) {
    // event loop
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
        // space to pause
        if (key_pressed->scancode == sf::Keyboard::Scancode::Space) {
          paused = !paused;
        }
        // r to reset
        if (key_pressed->scancode == sf::Keyboard::Scancode::R) {
          // reshuffle array
          std::shuffle(array.begin(), array.end(),
                       std::default_random_engine(std::time(0)));
          step = 0;
          done = false;
          doneText.setString("Sorting...");
        }   
      }
    }

    window.clear(sf::Color::Black);

    // draw a rectangle for each value
    for (int i = 0; i < SIZE; i++) {
      int num = array[i];

      // height and width of the rectangle
      float height = num * ((float)size.y / SIZE);
      float width = ((float)size.x / SIZE);

      // create rectangle and move it to the right place
      sf::RectangleShape rect(sf::Vector2f(width, height));
      rect.setFillColor(sf::Color::White);
      rect.setPosition(sf::Vector2f(width * i, size.y - height));

      // draw rectangle
      window.draw(rect);
    }

    if (!done && !paused) {
      selectionSort(array, step);
            
      if (std::is_sorted(array.begin(), array.end()))
        done = true;
            
      if (!done) step++;
      else doneText.setString("Done!");
    }

    stepCounter.setString("Steps: " + std::to_string(step));

    window.draw(text);
    window.draw(stepCounter);
    window.draw(helpText);
    window.draw(doneText);

    window.display();
  }

  return 0;
}
