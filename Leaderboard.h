#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// this is what display on the window
struct LeaderboardLines{
    std::string timeStr;  // holds time spent
    std::string name;     // holds player's name
};

// inline avoid multiple definition
inline void setText(sf::Text& text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(x, y);
}

void showLeaderboard(sf::Font& font);
void saveToLeaderboard(const std::string& playerName, int totalSeconds);