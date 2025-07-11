#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

void setText(sf::Text& text, float x, float y);
bool showWelcomeScreen(sf::RenderWindow& window, sf::Font& font, std::string& playerName, int width, int height);
