/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Resource
*/

#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Sprite.hpp"

class Resource: public Sprite {
    public:
        enum ResourceType {
            Food,
            Linemate,
            Deraumere,
            Sibur,
            Mendiane,
            Phiras,
            Thystame,
            ResourceTypeCount // used to get the number of resource types
        } _resourceType;

        Resource(std::shared_ptr<sf::Texture> textureFile, ResourceType type, sf::Vector2f pos, float scale);
        ~Resource();

        ResourceType getType() const;
        void setPosition(float x, float y);

    private:
        ResourceType _type;
};

#endif /* !RESOURCE_HPP_ */
