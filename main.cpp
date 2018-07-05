#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <thread>
#include <iostream>
#include <cmath>

using namespace std;
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

std::vector<sf::CircleShape> draw_stuff(
  sf::RenderWindow* window,
  double point_a,
  double point_b,
  double amplitude,
  double phase,
  double wave_number,
  double angular_frequency,
  double t,
  sf::Color color
) {
  std::vector<sf::CircleShape> points;
  for(double i = point_a; i < point_b; i = i + 0.01) {
    sf::CircleShape point(2);
    double y = amplitude * cos(wave_number * i - angular_frequency * t + phase);
    point.setPosition(WINDOW_WIDTH / 2 + i * 100, WINDOW_HEIGHT / 2  - y * 10);
    point.setFillColor(color);
    points.push_back(point);
  }
  for(int i = 0; i < points.size(); i++) {
    window->draw(points.at(i));
  }
  return points;
}

void draw_superposition(
  sf::RenderWindow* window,
  std::vector<sf::CircleShape> wave_one,
  std::vector<sf::CircleShape> wave_two,
  sf::Color color
)
{
  std::vector<sf::CircleShape> points;
  for(int i = 0; i < wave_one.size(); i++) {
    sf::CircleShape resultant(2);
    double y_value = wave_one.at(i).getPosition().y + wave_two.at(i).getPosition().y - WINDOW_HEIGHT;
    resultant.setPosition(wave_one.at(i).getPosition().x, WINDOW_HEIGHT / 2 + y_value);
    resultant.setFillColor(color);
    points.push_back(resultant);
  }
  for(int i = 0; i < points.size(); i++) {
    window->draw(points.at(i));
  }
}

void display_window() {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Inteference pattern");
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
          window.close();
        }
    }
    window.clear();
    sf::CircleShape origin(5);
    origin.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    origin.setFillColor(sf::Color::Blue);
    window.draw(origin);
    auto wave_one = draw_stuff(&window, - 2 * M_PI, 2 * M_PI, 5, 0, 2 * M_PI / 1, 2 * M_PI * 1, 0, sf::Color::Blue);
    auto wave_two = draw_stuff(&window, - 2 * M_PI, 2 * M_PI, 5, M_PI, 2 * M_PI / 1, 2 * M_PI * 1, 0, sf::Color::Red);
    draw_superposition(&window, wave_one, wave_two, sf::Color::Green);
    window.display();
  }
}

int main()
{
  display_window();
  return 0;
}
