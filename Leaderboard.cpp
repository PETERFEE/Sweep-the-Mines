#include "Leaderboard.h"
// Created by fengh on 4/22/2025.
//
// Show the leaderboard window


void showLeaderboard(sf::Font& font) {
    // Read data from leaderboard.txt
    std::ifstream file("files/leaderboard.txt");
    std::vector<LeaderboardLines> entries; // vector represent each line
    std::string line; // use to get lines for file

    // read each line of the leaderbaord txt file
    while (std::getline(file, line)) {

        // we are load CSV-like lines, so we use stringstream
        std::stringstream ss(line);
        std::string time, name;
        //Reads from ss up to the first comma. and store in time // rest store in name
        if (std::getline(ss, time, ',') && std::getline(ss, name)) {
            // set the object attribute
            LeaderboardLines entry;
            entry.timeStr = time;
            entry.name = name;
            entries.push_back(entry); // add each into the vector
        }
    }

    // Create leaderboard window
    sf::RenderWindow leaderboardWindow(sf::VideoMode(400, 400), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    leaderboardWindow.setPosition(sf::Vector2i(400, 100));

    // Create and set title text
    sf::Text title; //use to display Leaderboard underline on this window
    title.setFont(font);
    title.setString("LEADERBOARD");
    title.setCharacterSize(20);
    title.setStyle(sf::Text::Bold | sf::Text::Underlined); // add under and bold
    title.setFillColor(sf::Color::White);
    setText(title, 200, 80); // use the setText function to center the position

    // Create leaderboard list
    std::string contentStr;
    for (size_t i = 0; i < entries.size(); ++i) {
        ///         convert that iterator to string                               // there's a extra line in the middle
        contentStr += std::to_string(i+1) + "\t" + entries[i].timeStr + "\t" + entries[i].name + "\n\n";
    }

    // Create and set content text
    sf::Text content;
    content.setFont(font);
    content.setFont(font);
    content.setString(contentStr);
    content.setCharacterSize(18);
    content.setFillColor(sf::Color::White);
    setText(content, 200, 220); // starting at 220
    // Show leaderboard window
    while (leaderboardWindow.isOpen()) {
        sf::Event event;
        while (leaderboardWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                leaderboardWindow.close();
            }
        }
        leaderboardWindow.clear(sf::Color::Blue);
        leaderboardWindow.draw(title);
        leaderboardWindow.draw(content);
        leaderboardWindow.display();
    }
}

// convert minutes: seconds into  seconds in int
// use for comapring two object's second in string
int timeToSeconds(const std::string& timeStr) {
    int minutes = std::stoi(timeStr.substr(0, 2));
    int seconds = std::stoi(timeStr.substr(3, 2));
    return minutes * 60 + seconds;
}

// Save the record by name and second after the game over
void saveToLeaderboard(const std::string& playerName, int totalSeconds) {
    std::ifstream file("files/leaderboard.txt");
    std::vector<LeaderboardLines> entries;
    std::string line;

    // read line by line
    while (std::getline(file, line)) {
        // each line into ss
        std::stringstream ss(line);
        std::string time, name;
        if (std::getline(ss, time, ',') && std::getline(ss, name)) {
            LeaderboardLines entry;
            entry.timeStr = time;
            entry.name = name;
            entries.push_back(entry);
        }
    }
    file.close();

    // Convert to record to put on the board
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    //output stream name newTime
    std::ostringstream newTime;
    // Convert minutes to string and add leading zero if needed
    std::string minStr;
    if (minutes < 10) {
        minStr = "0" + std::to_string(minutes);
    } else {
        minStr = std::to_string(minutes);
    }

    // Convert seconds to string and add leading zero if needed
    std::string secStr;
    if (seconds < 10) {
        secStr = "0" + std::to_string(seconds);
    } else {
        secStr = std::to_string(seconds);
    }

    // Combine into minutes : seconds format
    newTime << minStr << ":" << secStr;


    //add new record into the list
    entries.push_back({ newTime.str(), playerName});

                                                                    // use a lambda function that compare two leaderboardline object's time string in seconds
    std::sort(entries.begin(), entries.end(), [](const LeaderboardLines& a, const LeaderboardLines& b) {
        return timeToSeconds(a.timeStr) < timeToSeconds(b.timeStr);
    });

    // can't fit more then 5 or out of the page
    if (entries.size() > 5) entries.resize(5);

    // Write back                                   // clear all exisiting and write new list to it
    std::ofstream outFile("files/leaderboard.txt", std::ios::trunc);

    for (const auto& entry : entries) {
        outFile << entry.timeStr << "," << entry.name << "\n";
    }
    outFile.close();
}