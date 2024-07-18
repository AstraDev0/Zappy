/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include "Resource.hpp"
#include "Sprite.hpp"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int TILE_SIZE = 32;

class Tile: public Sprite {
    private:
        std::vector<std::shared_ptr<Resource>> _resources;

    public:
        Tile(float scale);
        ~Tile();

        sf::Sprite getSprite() const;
        std::vector<std::shared_ptr<Resource>> getResources() const;

        void addResource(Resource::ResourceType type, std::shared_ptr<sf::Texture> texture, float scale);
        void draw(sf::RenderWindow& window, float x, float y);

        void removeResource(Resource::ResourceType type);
};

#endif /* !TILE_HPP_ */
