/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Team
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <array>
#include <random>
#include <thread>
#include <memory>
#include <vector>
#include "Player.hpp"

class Team {
    public:
        Team(std::string name, float scale, int color);
        ~Team();

        std::string getName() const;
        std::shared_ptr<Player> getPlayer(int id) const;
       std::vector<std::shared_ptr<Player>> getAllPlayers() const;

        void addPlayer(std::vector<std::string> parameters);
        void drawPlayers(sf::RenderWindow& window);
        void deletePlayer(int id);

    private:
        std::vector<std::shared_ptr<Player>> _players;
        std::string _name;
        float _scale;
        sf::Color _color;
};

#endif /* !TEAM_HPP_ */
