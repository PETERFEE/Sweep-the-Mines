#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;


// Create textures.
class TextureManager {
private:
    std::unordered_map<std::string, sf::Texture> textures;

public:
    TextureManager() {
        loadTextures();
    }
    sf::Texture debugTexture;
    sf::Texture digitsTexture;
    sf::Texture faceHappyTexture;
    sf::Texture faceLoseTexture;
    sf::Texture faceWinTexture;
    sf::Texture flagTexture;
    sf::Texture leaderboardTexture;
    sf::Texture mineTexture;
    sf::Texture number1Texture;
    sf::Texture number2Texture;
    sf::Texture number3Texture;
    sf::Texture number4Texture;
    sf::Texture number5Texture;
    sf::Texture number6Texture;
    sf::Texture number7Texture;
    sf::Texture number8Texture;
    sf::Texture pauseTexture;
    sf::Texture playTexture;
    sf::Texture tileHiddenTexture;
    sf::Texture tileRevealedTexture;



    // Load textures from file.
    void loadTextures() {
        sf::Texture temp;

        if (temp.loadFromFile("files/images/debug.png"))
            textures["debug.png"] = temp;
        else std::cerr << "Failed to load debug.png\n";

        if (temp.loadFromFile("files/images/digits.png"))
            textures["digits.png"] = temp;
        else std::cerr << "Failed to load digits.png\n";

        if (temp.loadFromFile("files/images/face_happy.png"))
            textures["face_happy.png"] = temp;
        else std::cerr << "Failed to load face_happy.png\n";

        if (temp.loadFromFile("files/images/face_lose.png"))
            textures["face_lose.png"] = temp;
        else std::cerr << "Failed to load face_lose.png\n";

        if (temp.loadFromFile("files/images/face_win.png"))
            textures["face_win.png"] = temp;
        else std::cerr << "Failed to load face_win.png\n";

        if (temp.loadFromFile("files/images/flag.png"))
            textures["flag.png"] = temp;
        else std::cerr << "Failed to load flag.png\n";

        if (temp.loadFromFile("files/images/leaderboard.png"))
            textures["leaderboard.png"] = temp;
        else std::cerr << "Failed to load leaderboard.png\n";

        if (temp.loadFromFile("files/images/mine.png"))
            textures["mine.png"] = temp;
        else std::cerr << "Failed to load mine.png\n";

        if (temp.loadFromFile("files/images/number_1.png"))
            textures["number_1.png"] = temp;
        else std::cerr << "Failed to load number_1.png\n";

        if (temp.loadFromFile("files/images/number_2.png"))
            textures["number_2.png"] = temp;
        else std::cerr << "Failed to load number_2.png\n";

        if (temp.loadFromFile("files/images/number_3.png"))
            textures["number_3.png"] = temp;
        else std::cerr << "Failed to load number_3.png\n";

        if (temp.loadFromFile("files/images/number_4.png"))
            textures["number_4.png"] = temp;
        else std::cerr << "Failed to load number_4.png\n";

        if (temp.loadFromFile("files/images/number_5.png"))
            textures["number_5.png"] = temp;
        else std::cerr << "Failed to load number_5.png\n";

        if (temp.loadFromFile("files/images/number_6.png"))
            textures["number_6.png"] = temp;
        else std::cerr << "Failed to load number_6.png\n";

        if (temp.loadFromFile("files/images/number_7.png"))
            textures["number_7.png"] = temp;
        else std::cerr << "Failed to load number_7.png\n";

        if (temp.loadFromFile("files/images/number_8.png"))
            textures["number_8.png"] = temp;
        else std::cerr << "Failed to load number_8.png\n";

        if (temp.loadFromFile("files/images/pause.png"))
            textures["pause.png"] = temp;
        else std::cerr << "Failed to load pause.png\n";

        if (temp.loadFromFile("files/images/play.png"))
            textures["play.png"] = temp;
        else std::cerr << "Failed to load play.png\n";

        if (temp.loadFromFile("files/images/tile_hidden.png"))
            textures["tile_hidden.png"] = temp;
        else std::cerr << "Failed to load tile_hidden.png\n";

        if (temp.loadFromFile("files/images/tile_revealed.png"))
            textures["tile_revealed.png"] = temp;
        else std::cerr << "Failed to load tile_revealed.png\n";
    }

    //later just call sprite.setTexture(tM.getTexture("..."))
    sf::Texture& getTexture(const std::string& name) {
        return textures[name];
    }

};