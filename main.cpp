// Aidan Carey, Feburary 2026, main.cpp

#include <SFML/Graphics.hpp>

#include <array>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>

#include "algorithms.hpp"

// Draw the graph on screen with rectangles
void drawGraph(sf::RenderWindow *window, sf::Vector2u windowSize, std::array<int, SIZE> array) {
  for (int i = 0; i < SIZE; i++) {
    int num = array[i];

    // Rectangle height and width
    float height = num * ((float)windowSize.y / SIZE);
    float width = ((float)windowSize.x / SIZE);

    // Create and draw rectangle
    sf::RectangleShape rect(sf::Vector2f(width, height));
    rect.setFillColor(sf::Color::White);
    rect.setPosition(sf::Vector2f(width * i, windowSize.y - height));
    window->draw(rect);
  }
}

// Give text color, char size, optionally position at top left
void setupText(sf::Text *text, int index = -1) {
  // Color and char size
  text->setFillColor(sf::Color::Green);
  text->setCharacterSize(20);
  
  // Position
  if (index >= 0) {
    text->setPosition(sf::Vector2f(5, 20 * index + 5));
  }
}

int main(int argc, char const *argv[]) {
  sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1000, 1200)), "Sorting");
  window.setFramerateLimit(20); // Lower framerate to see the sorting
  
  sf::Vector2u windowSize = window.getSize();

  // Create, fill, and shuffle array
  std::array<int, SIZE> array;
  std::iota(array.begin(), array.end(), 1);
  std::shuffle(array.begin(), array.end(),
               std::default_random_engine(std::time(0)));

  int  step   = 0;
  bool done   = false;
  bool paused = false;

  // Sorting algorithm to use
  void (*sortingAlgorithm)(std::array<int, SIZE>&, int) = selectionSort;
  std::string algorithmName = "Selection Sort";
  
  // Text
  sf::Font font("Roboto-Light.ttf");
  sf::Text sortName(font), stepCounter(font), helpText(font), doneText(font);

  // Sorting algorithm name at the middle top
  sortName.setString(algorithmName);
  float sortNameWidth = sortName.getLocalBounds().size.x;
  float sortNameX = (windowSize.x - sortNameWidth) / 2;  
  sortName.setPosition(sf::Vector2f(static_cast<int>(sortNameX), 5));

  // Text at top left
  helpText.setString("Space to pause, R to reset");
  doneText.setString("Sorting...");

  setupText(&sortName);
  setupText(&helpText, 0);
  setupText(&stepCounter, 1);
  setupText(&doneText, 2);
  
  // Main loop
  while (window.isOpen()) {
    // Event loop
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
        // Pause
        if (key_pressed->scancode == sf::Keyboard::Scancode::Space) {
          paused = !paused;
        }
        // R to reset
        if (key_pressed->scancode == sf::Keyboard::Scancode::R) {
          // Reshuffle array
          std::shuffle(array.begin(), array.end(),
                       std::default_random_engine(std::time(0)));
          step = 0;
          done = false;
          doneText.setString("Sorting...");
        }   
      }
    }

    window.clear(sf::Color::Black);

    drawGraph(&window, windowSize, array);

    // Procced one step
    if (!done && !paused) {
      sortingAlgorithm(array, step);
           
      if (std::is_sorted(array.begin(), array.end())) {
        done = true;
        doneText.setString("Done!");
      } else {
        step++;
      }
    }

    stepCounter.setString("Steps: " + std::to_string(step));

    window.draw(sortName);
    window.draw(stepCounter);
    window.draw(helpText);
    window.draw(doneText);

    window.display();
  }

  return 0;
}
