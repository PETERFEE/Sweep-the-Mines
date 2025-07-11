//
// Created by fengh on 4/23/2025.
//

#include "WelcomeScreen.h"

inline void setText(sf::Text& text, float x, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    text.setPosition(x, y);
}

bool showWelcomeScreen(sf::RenderWindow& welcomeWindow, sf::Font& font, std::string& playerName, int Width, int Height) {
        sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
    sf::Text enterName("Enter your Name:", font, 20);

    // set it with empty string
    playerName = "";
    // use playername as string input
    sf::Text NameInput(playerName, font, 18);
    NameInput.setFillColor(sf::Color::Yellow);

    welcomeText.setFillColor(sf::Color::White);
    enterName.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Underlined);

    // position text elements
    setText(welcomeText, Width/2, Height/2-150);
    setText(enterName, Width/2, Height/2-75);
    setText(NameInput, Width/2, Height/2-45);

    // control to go to Game window
    bool goToGame = false;

    // run the event as long as the window is open
    //Handles drawing and updating every frame.
    while(welcomeWindow.isOpen()) {

        // check all window events that occurred
        sf::Event event;
        // Processes all events in the event queue before the next frame.
        while(welcomeWindow.pollEvent(event)) {

            if(event.type == sf::Event::Closed) {
                welcomeWindow.close(); // Exit the program fully
                return 0;
            }

            //show welcome screen
            // play name  entered
            if (event.type == sf::Event::TextEntered) {

                // Backspace = 8
                if (event.text.unicode == 8) {
                    if (!playerName.empty()) {
                        // remove the last entered character
                        playerName.pop_back();
                    }
                }
                // Enter = 13
                else if (event.text.unicode == 13) {
                    // only exit with enter when input is not empty
                    if (!playerName.empty()) {
                        welcomeWindow.close(); // You can launch the game window here
                        goToGame = true;
                    }
                }

                // normal typing
                else if (playerName.size() < 10) {
                    //casting unicode into char store in typedChar
                    char typedChar = static_cast<char>(event.text.unicode);
                    // check if typedChar is a Letter
                    if (isalpha(typedChar)) {
                        // all typedChar to lowercase
                        typedChar = tolower(typedChar);
                        // add to string playerName
                        playerName += typedChar;
                    }
                }
                // Format name with capital first letter, rest lowercase
                if (!playerName.empty()) {
                    // the first typed character to Uppercase
                    playerName[0] = toupper(playerName[0]);
                    // for the rest of the string
                    for (size_t i = 1; i < playerName.size(); ++i) {
                        playerName[i] = tolower(playerName[i]);
                    }
                }

                // change text object NameInput
                NameInput.setString(playerName + '|');
                //in the while loop so it will updata and re-center as it changes
                setText(NameInput, Width / 2, Height / 2 - 45);
            }


        }

        // draw everything
        welcomeWindow.setPosition(sf::Vector2i(200, 200));
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(enterName);
        welcomeWindow.draw(NameInput);
        welcomeWindow.display();
    }
    return goToGame;
}