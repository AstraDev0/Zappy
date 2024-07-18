/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Menu
*/

#include "Button.hpp"

Button::Button(const std::string& textureFile, float x, float y, float scale)
{
    _texture = std::make_shared<sf::Texture>();
    if (!_texture->loadFromFile(textureFile)) {
        std::cerr << "Could not load texture" << std::endl;
        exit(84);
    }
    _sprite.setTexture(*_texture);
    _sprite.setScale(scale, scale);
    _sprite.setPosition(sf::Vector2f(x, y));
}

Button::~Button()
{
}

bool Button::isMouseOver(sf::RenderWindow &window)
{
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = _sprite.getPosition().x;
    float btnPosY = _sprite.getPosition().y;

    float btnxPosWidth = btnPosX + _sprite.getGlobalBounds().width;
    float btnyPosHeight = btnPosY + _sprite.getGlobalBounds().height;

    return (mouseX > btnPosX && mouseX < btnxPosWidth && mouseY > btnPosY && mouseY < btnyPosHeight);
}
