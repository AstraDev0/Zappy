/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Sprite
*/


#include "Sprite.hpp"

Sprite::Sprite(const std::string& textureFile, float x, float y, float scale)
{
    _texture = std::make_shared<sf::Texture>();
    if (!_texture->loadFromFile(textureFile)) {
        std::cerr << "Could not load texture" << std::endl;
        exit(84);
    }
    _sprite.setTexture(*_texture);
    if (textureFile == "Png/bck.jpg")
        _sprite.setScale(scale, scale);
    else
        _sprite.setScale(scale / _texture->getSize().x * 32, scale / _texture->getSize().y * 32);
    _sprite.setPosition(sf::Vector2f(x, y));
}

Sprite::~Sprite()
{
}

sf::Sprite Sprite::getSprite() const
{
    return _sprite;
}

void Sprite::setPosition(float x, float y)
{
    _sprite.setPosition(sf::Vector2f(x, y));
}

void Sprite::draw(sf::RenderWindow& window)
{
    window.draw(_sprite);
}
