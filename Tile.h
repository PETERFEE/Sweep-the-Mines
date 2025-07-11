#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "TextureManager.h"

class Tile {
public:
    // initailize them to default
    bool isRevealed = false;
    bool isFlagged = false;
    bool isMine = false;
    int adjacentMinesCount = 0;
    std::vector<Tile*> adjacentTiles;

    sf::Sprite baseSprite;   //  tile_hidden or tile_revealed
    sf::Sprite overlaySprite; // flag, number, or mine
    TextureManager tM;

    Tile() {
        baseSprite.setTexture(tM.getTexture("tile_hidden.png"));
    }

    void setPosition(int col, int row) {
        float  px = col * 32;
        float py = row * 32;
        baseSprite.setPosition(px, py);
        overlaySprite.setPosition(px, py);
    }

    void reveal() {
        if (isFlagged || isRevealed) {
               return; // if already revealed, or flaged, ignore the tile
        }

        isRevealed = true;

        baseSprite.setTexture(tM.getTexture("tile_revealed.png"));

        // if there's mine, change the top texture
        if (isMine) {
            overlaySprite.setTexture(tM.getTexture("mine.png"));
        } else if (adjacentMinesCount > 0) {
            // get the number image that same as ajacentMinesCount
            overlaySprite.setTexture(tM.getTexture("number_" + std::to_string(adjacentMinesCount) + ".png"));
        } else {
            // show the reaveled tile
            overlaySprite = sf::Sprite(); // clear overlay

        }
        //Ensure overlaySprite is positioned correctly after reset
        overlaySprite.setPosition(baseSprite.getPosition());
    }

    void toggleFlag() {
        if (isRevealed) return;
        //change the status of the flag to the opposite
        isFlagged = !isFlagged;

        if (isFlagged) {
            overlaySprite.setTexture(tM.getTexture("flag.png"));
            // ensure overlay position correctly
            overlaySprite.setPosition(baseSprite.getPosition());
        } else {
            overlaySprite = sf::Sprite(); // remove flag with defualt constructor
        }
    }

    void reset() {
        //everything back to defualt
        isRevealed = false;
        isFlagged = false;
        isMine = false;
        adjacentMinesCount = 0;
        adjacentTiles.clear();
        baseSprite.setTexture(tM.getTexture("tile_hidden.png"));
        overlaySprite = sf::Sprite();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(baseSprite);
        if (isRevealed || isFlagged || isMine) {
            window.draw(overlaySprite);
        }
    }

    void ShowMine() {
        if (isMine) {
            baseSprite.setTexture(tM.getTexture("tile_revealed.png"));
            overlaySprite.setTexture(tM.getTexture("mine.png"));
        }
    }
};
