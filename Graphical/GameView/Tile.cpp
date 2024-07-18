/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameView
*/

#include "Tile.hpp"

void menu(sf::RenderWindow& window);

Tile::Tile(float scale)
{
    _texture = std::make_shared<sf::Texture>();
    if (!_texture->loadFromFile("Png/grass.jpg")) {
        std::cerr << std::endl;
        exit(84);
    }
    _sprite.setTexture(*_texture);
    _sprite.setScale(scale, scale);
}

Tile::~Tile()
{
}

sf::Sprite Tile::getSprite() const
{
    return _sprite;
}

std::vector<std::shared_ptr<Resource>> Tile::getResources() const
{
    return _resources;
}

void Tile::addResource(Resource::ResourceType type, std::shared_ptr<sf::Texture> texture, float scale)
{
    for (auto& resource : _resources) {
        if (resource->getType() == type)
            return;
    }
    int posX = std::rand() % static_cast<int>(scale * TILE_SIZE / 2);
    int posY = std::rand() % static_cast<int>(scale * TILE_SIZE / 2);
    std::shared_ptr<Resource> resource = std::make_shared<Resource>(texture, type, sf::Vector2f(posX, posY), scale);

    _resources.push_back(resource);
}

void Tile::draw(sf::RenderWindow& window, float x, float y)
{
    _sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
    window.draw(_sprite);

    for (auto& resource : _resources) {
        resource->setPosition(x, y);
        resource->draw(window);
    }
}

void Tile::removeResource(Resource::ResourceType type) {
    for (auto it = _resources.begin(); it != _resources.end(); ) {
        if ((*it)->getType() == type) {
            it = _resources.erase(it);
        } else
            ++it;
    }
}