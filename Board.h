#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "TextureManager.h"

class Board {
    int rows, cols, mineCount;

    vector<vector<Tile*>> board;
    TextureManager tM;

public:
    Board(int rows, int cols ,int mineCount ) : rows(rows), cols(cols), mineCount(mineCount) {
        //use built-in vector function resize to change the size into rows and cols
        // and initailize each of Tile* to nullptr
        board.resize(rows, std::vector<Tile*>(cols, nullptr));
        // Use nested loops to each Tile.
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                board[i][j] = new Tile(); // initailze a Tile object
                board[i][j]->setPosition(j, i); // col, row
            }
        }
        assignMines();
        findAdjacent();
    }

    ~Board() {
        //delete everthing inside
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                delete board[i][j];
    }

    // assign random mine
    void assignMines() {
        // srand gives different random numbers each time
        // time(0) return current time as time_t
        srand(static_cast<unsigned int>(time(0)));
        int placed = 0;
        while (placed < mineCount) {
            //
            int i = rand() % rows;
            int j = rand() % cols;
            if (!board[i][j]->isMine) {
                //set using -> pointer set the attribute to be true
                board[i][j]->isMine = true;
                placed++;
            }
        }
    }

    // base on the Tile* inputs , reveal defferent adjacent
    void revealAdjacent(Tile* tile) {

        // serve as a base case if the current has already be reavealed or flagged
        if (tile->isRevealed || tile->isFlagged) return;

        //reveal the current
        tile->reveal();

        // if there's no mines around and no current not a mine
        if (tile->adjacentMinesCount == 0 && !tile->isMine) {

            // for each Tile* in vector<Tile*>
            for (Tile* neighbor : tile->adjacentTiles) {
                // if not reveal yet and not a mine
                if (!neighbor->isRevealed && !neighbor->isMine)
                    //expand for each neighbor to discover if their neighbor can be revealed
                    revealAdjacent(neighbor);
            }
        }
    }


    void drawBoard(sf::RenderWindow &window) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // for each tile call the draw
                board[i][j]->draw(window);
            }
        }
        }


    void drawPaused(sf::RenderWindow& window) {for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Tile* tile = board[i][j];

            // Make a temp copy of the base sprite
            sf::Sprite tempBase = tile->baseSprite;

            // set it to tile_revealed
            tempBase.setTexture(tM.getTexture("tile_revealed.png"));
            tempBase.setPosition(tile->baseSprite.getPosition());

            // Draw only the base — no overlay at all
            window.draw(tempBase);
        }
    }
    }

    void drawDebug(sf::RenderWindow &window) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                Tile* tile = board[i][j];
                // Only draw mines on top if tile is hidden and is a mine
                if (!tile->isRevealed && tile->isMine) {
                    // draw a tempMine on top without changing the tile sprite
                    sf::Sprite tempMine;
                    tempMine.setTexture(tM.getTexture("mine.png"));
                    tempMine.setPosition(tile->baseSprite.getPosition());
                    window.draw(tempMine); // draw on top visually only
                }
            }
        }
    }



    // given a tile and find adjacent mines and updata the Count
    //Store those neighboring tiles
    void findAdjacent() {
        // 8 vector that represent the position related to the current tile
        const int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            { 0, -1},          { 0, 1},
            { 1, -1}, { 1, 0}, { 1, 1}
        };

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {

                // clear for reseting the game
                Tile* tile = board[i][j];
                tile->adjacentTiles.clear();
                tile->adjacentMinesCount = 0;

                for (int d = 0; d < 8; ++d) {
                    // on the position of the current tile
                    // calculation the neiborhood's position
                    int ni = i + directions[d][0];
                    int nj = j + directions[d][1];

                    // Check if the neighbor is in board
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols) {

                        Tile* neighbor = board[ni][nj];
                        //Save this neighbor in the tile’s adjacentTiles list
                        tile->adjacentTiles.push_back(neighbor);

                        //if neibor is a mine, increase adjacentMinesCount
                        if (neighbor->isMine)
                            tile->adjacentMinesCount++;
                    }
                }
            }
        }
    }


    bool checkWin() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                // if there's at least one tile is hidden without a mine under
                    // player still need to click it to win
                if (!board[i][j]->isMine && !board[i][j]->isRevealed)
                    return false;
        return true;
    }

    //call reset of every tile
    void reset() {
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                board[i][j]->reset();
        // reset the minecount and adjacenttile
        assignMines();
        findAdjacent();
    }

    // getter for tile pointer base on the position
    Tile* getTileAt(int row, int col) {
        //verfiy inside the board
        if (row >= 0 && row < rows && col >= 0 && col < cols)
            return board[row][col];
        return nullptr;
    }

    // return num of flags. use for remaining mines
    int countFlags() const {
        int flagCount = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (board[i][j]->isFlagged)
                    flagCount++;
            }
        }
        return flagCount;
    }
    //
    void printBoard() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << (board[i][j]->isRevealed ? " 0 " : " X ");
            }
            std::cout << std::endl;
        }
    }
};
