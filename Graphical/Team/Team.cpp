/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Team
*/

#include "Team.hpp"

Team::Team(std::string name, float scale, int color): _name(name), _scale(scale)
{
    if (color == 0) {
        _color = sf::Color::Blue;
    } else if (color == 1) {
        _color = sf::Color::Red;
    } else if (color == 2) {
        _color = sf::Color::Green;
    } else if (color == 3) {
        _color = sf::Color::Yellow;
    }
}

Team::~Team()
{
}

std::string Team::getName() const
{
    return _name;
}

std::shared_ptr<Player> Team::getPlayer(int id) const
{
    for (auto& player: _players) {
        if (player->getId() == id)
            return player;
    }

    return nullptr;
}

std::vector<std::shared_ptr<Player>> Team::getAllPlayers() const
{
    return _players;
}

void Team::addPlayer(std::vector<std::string> parameters) //send color here
{
    std::shared_ptr<Player> player = std::make_shared<Player>(parameters, _scale, _color);
    _players.push_back(player);
}

void Team::drawPlayers(sf::RenderWindow& window)
{
    for (auto& player: _players) {
        player->draw(window);
        window.draw(player->getLevelText());
        if (player->getAuraActive())
            player->drawAura(window);
    }
}

void Team::deletePlayer(int id)
{
    for (auto it = _players.begin(); it != _players.end(); ) {
        if ((*it)->getId() == id) {
            it = _players.erase(it);
            return;
        }
        ++it;
    }
}
