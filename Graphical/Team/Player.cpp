/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(std::vector<std::string> parameters, float scale, sf::Color color): _scale(scale), _auraActive(false)
{
    _sprite.setScale(scale, scale);
    _id = std::stoi(parameters[1]);
    _sprite.setColor(color);
    setPosition(std::stof(parameters[2]), std::stof(parameters[3]));
    _direction = static_cast<Direction>(std::stoi(parameters[4]) - 1);
    _lvl = std::stoi(parameters[5]);
    _aura = std::make_unique<Sprite>("Png/aura.png", std::stof(parameters[2]), std::stof(parameters[3]), _scale);

    for (int i = 0; i < DirectionCount; i++)
        _textures[i] = std::make_unique<sf::Texture>();
    if (!_textures[static_cast<int>(Direction::Up)]->loadFromFile("Png/player0.png") ||
        !_textures[static_cast<int>(Direction::Right)]->loadFromFile("Png/player1.png") ||
        !_textures[static_cast<int>(Direction::Down)]->loadFromFile("Png/player2.png") ||
        !_textures[static_cast<int>(Direction::Left)]->loadFromFile("Png/player3.png")) {
        throw std::runtime_error("Failed to load player textures");
    }
    _sprite.setTexture(*_textures[static_cast<int>(Direction::Up)]);

    if (!_font.loadFromFile("Png/lvl.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    _levelText.setFont(_font);
    _levelText.setCharacterSize(24); // choose an appropriate size
    _levelText.setFillColor(sf::Color::Black); // choose an appropriate color
}

Player::~Player()
{
}

void Player::setPosition(float x, float y) {
    _posTile = sf::Vector2f(x, y);
    _position.x = x * TILE_SIZE * _scale;
    _position.y = y * TILE_SIZE * _scale;
    _sprite.setPosition(_position.x, _position.y);

    _levelText.setPosition(_position.x, _position.y - 30);
}

sf::Vector2f Player::getPosition() const
{
    return _position;
}

int Player::getId() const
{
    return _id;
}

bool Player::getAuraActive() const
{
    return _auraActive;
}

void Player::move(int x, int y, int direction)
{
    setPosition(x, y);
    _aura->setPosition(x * TILE_SIZE * _scale, y * TILE_SIZE * _scale);
    _direction = static_cast<Direction>(direction - 1);
    _sprite.setTexture(*_textures[static_cast<int>(_direction)]);
}

void Player::collectResources(std::vector<std::vector<Tile>>& _tyles, int resourceType) {
    for(auto& resource : _tyles[_posTile.x][_posTile.y].getResources()) {
        if (resource->getType() == resourceType) {
            _tyles[_posTile.x][_posTile.y].removeResource(resource->getType());
            return;
        }
    }
}

void Player::dropResources(std::array<std::shared_ptr<sf::Texture>, Resource::ResourceTypeCount> resourceTextures, std::vector<std::vector<Tile>>& _tyles, int resourceType) {
    switch(resourceType) {
        case(0): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Food, resourceTextures[0], _scale);
            break;
        case(1): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Linemate, resourceTextures[1], _scale);
            break;
        case(2): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Deraumere, resourceTextures[2], _scale);
            break;
        case(3): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Sibur, resourceTextures[3], _scale);
            break;
        case(4): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Mendiane, resourceTextures[4], _scale);
            break;
        case(5): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Phiras, resourceTextures[5], _scale);
            break;
        case(6): _tyles[_posTile.x][_posTile.y].addResource(Resource::ResourceType::Thystame, resourceTextures[6], _scale);
            break;
    }
}

void Player::setLevel(int level)
{
    _lvl = level;
    std::stringstream ss;
    ss << "Lvl " << _lvl;
    _levelText.setString(ss.str());
}

sf::Text& Player::getLevelText() {
    std::stringstream ss;
    ss << "Lvl " << _lvl;
    _levelText.setString(ss.str());
    return _levelText;
}

void Player::startAura(int lvl)
{
    _lvl = lvl;
    _auraActive = true;
}

void Player::stopAura()
{
    _auraActive = false;
}

void Player::drawAura(sf::RenderWindow& window) {
        _aura->draw(window);
}
