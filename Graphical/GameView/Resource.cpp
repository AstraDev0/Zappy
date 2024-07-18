/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Resource
*/

#include "Resource.hpp"

Resource::Resource(std::shared_ptr<sf::Texture> textureFile, ResourceType type, sf::Vector2f pos, float scale)
{
    _texture = std::make_shared<sf::Texture>();
    _texture = textureFile;
    _sprite.setTexture(*textureFile);
    _sprite.setScale(scale / _texture->getSize().x * 32 / 2, scale / _texture->getSize().y * 32 / 2);
    _position = pos;
    _type = type;
}

Resource::~Resource()
{
}

Resource::ResourceType Resource::getType() const
{
    return _type;
}

void Resource::setPosition(float x, float y)
{
    _sprite.setPosition(x * 32 + _position.x, y * 32 + _position.y);
}
