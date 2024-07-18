/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite() = default;
        Sprite(const std::string& textureFile, float x, float y, float scale);
        ~Sprite();

        sf::Sprite getSprite() const;
        void setPosition(float x, float y);

        void draw(sf::RenderWindow& window);

    protected:
        std::shared_ptr<sf::Texture> _texture;
        sf::Sprite _sprite;
        sf::Vector2f _position;
};

#endif /* !SPRITE_HPP_ */
