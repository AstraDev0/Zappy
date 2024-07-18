/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Sprite.hpp"

class Button: public Sprite {
    public:
        Button(const std::string& textureFile, float x, float y, float scale);
        ~Button();

        bool isMouseOver(sf::RenderWindow &window);
};

#endif /* !BUTTON_HPP_ */
