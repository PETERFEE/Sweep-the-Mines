#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "WelcomeScreen.h"
#include "Tile.h"
#include "Board.h"
#include "Leaderboard.h"
using namespace std;


int main() {

// load the config file
    ifstream config("files/config.cfg");
    int colCount, rowCount, mineCount;
    // dimenson greater than 22*16
    config >> colCount >> rowCount >> mineCount;

    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        cout << "Error loading font file." << endl;
    }

    int Width = colCount * 32;
    int Height = ( rowCount* 32) + 100 ;
    int tile_length = 32;


bool gamestart;
// welcome window section  //
    sf::RenderWindow welcomeWindow(sf::VideoMode(Width, Height), "Minesweeper");
    //use to get width and height of desktop

    std::string playerName;
    if (showWelcomeScreen(welcomeWindow, font, playerName, Width, Height)) {
        gamestart = true;
    }





    if (gamestart) {
        cout << "Starting game for: " << playerName << endl;
        // create a texture object
        TextureManager tm;
        // Load pause and play, debug, leaderboard button textures

        sf::Texture pauseTexture = tm.getTexture("pause.png");
        sf::Texture playTexture = tm.getTexture("play.png");

        sf::Sprite happyButton(tm.getTexture("face_happy.png"));
        sf::Sprite debugButton(tm.getTexture("debug.png"));
        sf::Sprite pauseButton(tm.getTexture("pause.png"));
        sf::Sprite leaderboardButton(tm.getTexture("leaderboard.png"));
        // load texture
        sf::Texture digitsTexture = tm.getTexture("digits.png");



        //generate the game board
        Board board(rowCount, colCount, mineCount);

        //base on the scale render the game window
        sf::RenderWindow gameWindow(sf::VideoMode(Width, Height), "Minesweeper");
        // initailze the game status
        bool isPaused = false;
        bool gameOver = false;
        bool debugMode = false;

        // Timer variable
        sf::Clock gameClock; // track real world time
        int elapsedTime = 0;  // In seconds
        float timeAccumulator = 0.0f;  // To track full seconds between updates




        //set position for each button
        happyButton.setPosition((colCount / 2.0f) * 32 - 32, 32 * (rowCount + 0.5f));
        debugButton.setPosition(colCount * 32 - 304, 32 * (rowCount + 0.5f));
        pauseButton.setPosition(colCount * 32 - 240, 32 * (rowCount + 0.5f));
        leaderboardButton.setPosition(colCount * 32 - 176, 32 * (rowCount + 0.5f));




        //start the game window loop
        while (gameWindow.isOpen()) {
            // digit diplay of remaining mine count
            // Calculate mine count and digits
            int remainingMines = mineCount - board.countFlags();
            // Clamp to 3-digit range:  -99 to 999 since we can't show more than that
            if (remainingMines < -99) remainingMines = -99;
            if (remainingMines > 999) remainingMines = 999;

            bool isNegative = remainingMines < 0;
            int absVal = abs(remainingMines);

            int hundreds = (absVal / 100) % 10;
            int tens     = (absVal / 10) % 10;
            int ones     = absVal % 10;


            // the timer

            //clampig the elapsed time so that we can display in 4 digits
            if (elapsedTime > 3599) elapsedTime = 3599;

            // the minutes digits
            int minutes = elapsedTime / 60;

            //seconds digits
            int seconds = elapsedTime % 60;

            // each digit
            int minTens  = (minutes / 10) % 10;
            int minOnes  = minutes % 10;
            int secTens  = (seconds / 10) % 10;
            int secOnes  = seconds % 10;

            //timer digit Y position
            float baseY = 32 * (rowCount + 0.5f) + 16;

            // generate a timerSprite to distingusih with the counter
            sf::Sprite timerSprite1(digitsTexture);
            sf::Sprite timerSprite2(digitsTexture);
            sf::Sprite timerSprite3(digitsTexture);
            sf::Sprite timerSprite4(digitsTexture);

            //  minitus x position
            int minStartX = (colCount * 32) - 97;

            timerSprite1.setTextureRect(sf::IntRect(minTens * 21, 0, 21, 32));
            timerSprite1.setPosition(minStartX, baseY);


            timerSprite2.setTextureRect(sf::IntRect(minOnes * 21, 0, 21, 32));
            // 21 is the interval
            timerSprite2.setPosition(minStartX + 21, baseY);


            // === Draw seconds ===
            int secStartX = (colCount * 32) - 54;

            timerSprite3.setTextureRect(sf::IntRect(secTens * 21, 0, 21, 32));
            timerSprite3.setPosition(secStartX, baseY);

            timerSprite4.setTextureRect(sf::IntRect(secOnes * 21, 0, 21, 32));
            timerSprite4.setPosition(secStartX + 21, baseY);
            //draw timer sprite later
            //
            // as long as it's not pause and game is still on
            if (!isPaused && !gameOver) {
                // restart() return the time object since last frame
                // convert into second and add it to timeAccmulator
                timeAccumulator += gameClock.restart().asSeconds();

                //after 1 second
                if (timeAccumulator >= 1.0f) {
                    elapsedTime++;
                    // set this count back to 0
                    timeAccumulator = 0.0f;
                    //clamp it
                    if (elapsedTime > 999) elapsedTime = 999;
                }
            } else {
                gameClock.restart();
            }

            //


            // make a array of 3 slots
            sf::Sprite digits[3];

            for (int i = 0; i < 3; ++i)
                digits[i].setTexture(digitsTexture);

            // Starting draw position
            // y is the same for all digits
            float drawY = 32 * (rowCount + 0.5f) + 16;

            if (isNegative) {

                sf::Sprite minus_(digitsTexture);
                // set the digit into the portion that has minus sign
                // setTextureRect : Only use this rectangular portion of the texture for the sprite
                // | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | - |
                // IntRect() is a rectangle
                // Use digits[0] and digits[1] for digits, digits[2] for '-'
                digits[0].setTextureRect(sf::IntRect(tens * 21, 0, 21, 32));
                digits[0].setPosition(33, drawY);

                digits[1].setTextureRect(sf::IntRect(ones * 21, 0, 21, 32));
                digits[1].setPosition(54, drawY);

                // this is the minus sign
                digits[2].setTextureRect(sf::IntRect(210, 0, 21, 32)); // minus sign
                digits[2].setPosition(12, drawY);
            } else {
                // handle the poistive
                digits[0].setTextureRect(sf::IntRect(hundreds * 21, 0, 21, 32));
                digits[0].setPosition(33, drawY);

                digits[1].setTextureRect(sf::IntRect(tens * 21, 0, 21, 32));
                digits[1].setPosition(54, drawY);

                digits[2].setTextureRect(sf::IntRect(ones * 21, 0, 21, 32));
                digits[2].setPosition(75, drawY);
            }

            //
            sf::Event event;
            // handle all user event
            while (gameWindow.pollEvent(event)) {
                // if user click close the window
                if (event.type == sf::Event::Closed)
                    gameWindow.close();

                // only Checks for a left-click
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

                    // Gets the current mouse position in terms of screen pixels and convert to game window position
                    sf::Vector2f mousePos = gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow));



                        //if mouse click on pause
                        if (pauseButton.getGlobalBounds().contains(mousePos) && !gameOver) {
                            // toggle pause

                            isPaused = !isPaused;
                            if (isPaused) {
                                board.drawPaused(gameWindow);
                                pauseButton.setTexture(tm.getTexture("play.png"));
                            }
                            else{
                                board.drawBoard(gameWindow);
                                pauseButton.setTexture(tm.getTexture("pause.png"));
                            }
                        }
                        // click on debug
                        if (debugButton.getGlobalBounds().contains(mousePos) && !isPaused && !gameOver) {
                            debugMode = !debugMode; // Toggle debug
                            // only toggle, draw later to upadat at once
                        }

                        // if happy button is clicked, reset the game
                        else if (happyButton.getGlobalBounds().contains(mousePos)) {
                            board.reset();     // Rebuild the board
                            isPaused = false;  // reset all status
                            gameOver = false;
                            debugMode = false;

                            // reset Timer
                            elapsedTime = 0;
                            timeAccumulator = 0.0f;
                            gameClock.restart();
                            //

                            happyButton.setTexture(tm.getTexture("face_happy.png"));
                        }

                        // if leaderboard button is press
                        else if (leaderboardButton.getGlobalBounds().contains(mousePos)) {
                            //
                            std::cout << "Leaderboard button clicked!" << std::endl;
                            // show and draw leaderboard window
                            showLeaderboard(font);

                        }

                        if (!isPaused && !gameOver) {
                            // game interaction
                            // each tile is 32*32 pixel,
                            //  divide 32 gives the column (X) and row (Y) in the grid
                            int tileX = static_cast<int>(mousePos.x) / 32;
                            int tileY = static_cast<int>(mousePos.y) / 32;

                            // verify and make sure it's inside the grid
                            if (tileX >= 0 && tileX < colCount && tileY >= 0 && tileY < rowCount) {

                                //get the *tile where the mouse is position
                                Tile* clickedTile = board.getTileAt(tileY, tileX);

                                //check to make sure the tile is hidden without flagg
                                if (!clickedTile->isRevealed && !clickedTile->isFlagged) {

                                    if (clickedTile->isMine) {
                                        // only reveal that tile
                                        clickedTile->reveal();
                                        gameOver = true;


                                        // use debug mode to show all mine
                                        //draw later
                                        debugMode = true;
                                        happyButton.setTexture(tm.getTexture("face_lose.png"));
                                    }
                                    else
                                    {
                                        // reveal adjacent if not a mine
                                        board.revealAdjacent(clickedTile);
                                        // after reveal check win condition
                                        if (board.checkWin()) {
                                            gameOver = true;
                                            saveToLeaderboard(playerName, elapsedTime);
                                            //  update face to win
                                            happyButton.setTexture(tm.getTexture("face_win.png"));
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // now handle the flag which is right click
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
                    sf::Vector2f mousePos = gameWindow.mapPixelToCoords(sf::Mouse::getPosition(gameWindow));

                    // if the game is running
                    if (!isPaused && !gameOver) {
                        int tileX = static_cast<int>(mousePos.x) / 32;
                        int tileY = static_cast<int>(mousePos.y) / 32;

                        //ensure inside the board
                        if (tileX >= 0 && tileX < colCount && tileY >= 0 && tileY < rowCount) {
                            // get the tile base on position
                            Tile* clickedTile = board.getTileAt(tileY, tileX);

                            if (!clickedTile->isRevealed) {
                                clickedTile->toggleFlag(); // change the texture and flag status
                            }
                        }
                    }
                }

                }

                // Draw the game
                gameWindow.clear(sf::Color::White);
                if (isPaused) {
                    board.drawPaused(gameWindow);
                }
                else {
                    board.drawBoard(gameWindow);
                }
                //draw all button
                gameWindow.draw(happyButton);
                gameWindow.draw(debugButton);
                gameWindow.draw(pauseButton);
                gameWindow.draw(leaderboardButton);
            // Draw the 3-digit mine counter

            gameWindow.draw(digits[0]);
            gameWindow.draw(digits[1]);
            gameWindow.draw(digits[2]);

            // draw timer
            gameWindow.draw(timerSprite1);
            gameWindow.draw(timerSprite2);
            gameWindow.draw(timerSprite3);
            gameWindow.draw(timerSprite4);

            if (isPaused) {
                board.drawPaused(gameWindow); // override everything
            }
            else if (debugMode) {
                board.drawDebug(gameWindow); // only shows mines on hidden tiles
            }
            else {
                board.drawBoard(gameWindow); // normal gameplay view
            }
                gameWindow.display();


            }
        }


    return 0;
}
