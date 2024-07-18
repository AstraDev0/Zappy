/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <SFML/Graphics.hpp>
#include "../GameView/Tile.hpp"
#include <sstream>

class Player: public Sprite {
    public:
        enum Direction {
            Down,
            Right,
            Up,
            Left,
            DirectionCount
        } _direction;

        Player(std::vector<std::string> parameters, float scale, sf::Color color);
        ~Player();

        sf::Vector2f getPosition() const;
        int getId() const;
        sf::Text& getLevelText();
        bool getAuraActive() const;
        void setPosition(float x, float y);

        void move(int x, int y, int direction);
        void collectResources(std::vector<std::vector<Tile>>& _tyles, int resourceType);
        void dropResources(std::array<std::shared_ptr<sf::Texture>, Resource::ResourceTypeCount> _resourceTextures, std::vector<std::vector<Tile>>& _tyles, int resourceType);
        void setLevel(int level);
        void drawAura(sf::RenderWindow& window);
        void startAura(int lvl);
        void stopAura();

    private:
        std::array<std::unique_ptr<sf::Texture>, DirectionCount>  _textures;
        std::unique_ptr<Sprite> _aura;
        sf::Text _levelText;
        sf::Font _font;
        sf::Vector2f _posTile;
        float _scale;
        int _lvl;
        int _id;
        bool _auraActive;
};

#endif /* !PLAYER_HPP_ */
