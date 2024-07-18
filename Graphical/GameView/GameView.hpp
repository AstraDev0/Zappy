/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameView
*/

#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <array>
#include <random>
#include <thread>
#include <memory>
#include <vector>
#include "Tile.hpp"
#include "Button.hpp"
#include "../Team/Team.hpp"

class GameView
{
private:
    std::shared_ptr<std::thread> _thread;
    std::array<std::shared_ptr<sf::Texture>, Resource::ResourceTypeCount> _resourceTextures;
    std::vector<std::vector<Tile>> _tiles;
    std::vector<std::shared_ptr<Team>> _teams;
    int _gridWidth;
    int _gridHeight;

public:
    float _scale;
    GameView() = default;
    GameView(const GameView &other);
    GameView(int gridWidth, int gridHeight);
    ~GameView();

    void startThread();

    void addTeam(std::string name);
    void gameLoop();
    void addTile(std::vector<std::string> commandParts);
    void createPlayer(std::vector<std::string> parameters);
    void movePlayer(std::vector<std::string> parameters);
    void updatePlayerLevel(std::vector<std::string> parameters);
    void startLevelUp(std::vector<std::string> parameters);
    void endLevelUp(std::vector<std::string> parameters);
    void deletePlayer(int id);
    void takeObject(int id, int resource);
    void dropObject(int id, int resource);
};

#endif /* !GAMEVIEW_HPP_ */
