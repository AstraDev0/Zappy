/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** GameView
*/

#include "GameView.hpp"

GameView::GameView(const GameView& other) {
    _tiles = other._tiles;
    _scale = other._scale;
    _gridWidth = other._gridWidth;
    _gridHeight = other._gridHeight;
    _thread = other._thread;
    _resourceTextures = other._resourceTextures;
    _teams = other._teams;
}

GameView::GameView(int width, int height)
    : _gridWidth(width), _gridHeight(height)
{
    _scale = std::min(1080.0 / (static_cast<float>(_gridWidth) * TILE_SIZE), 1920.0 / (static_cast<float>(_gridHeight) * TILE_SIZE));
    _tiles = std::vector<std::vector<Tile>>(_gridWidth, std::vector<Tile>(_gridHeight, Tile(_scale)));

    for (int i = 0; i < Resource::ResourceTypeCount; i++)
        _resourceTextures[i] = std::make_shared<sf::Texture>();
    if (!_resourceTextures[Resource::Food]->loadFromFile("Png/food.png") ||
        !_resourceTextures[Resource::Linemate]->loadFromFile("Png/linemate.png") ||
        !_resourceTextures[Resource::Deraumere]->loadFromFile("Png/deraumere.png") ||
        !_resourceTextures[Resource::Sibur]->loadFromFile("Png/sibur.png") ||
        !_resourceTextures[Resource::Mendiane]->loadFromFile("Png/mendiane.png") ||
        !_resourceTextures[Resource::Phiras]->loadFromFile("Png/phiras.png") ||
        !_resourceTextures[Resource::Thystame]->loadFromFile("Png/thystame.png")) {
        std::cerr << std::endl;
        exit(84);
    }
}

GameView::~GameView()
{
}

void GameView::startThread()
{
    _thread = std::make_shared<std::thread>(&GameView::gameLoop, this);
    _thread->detach();
}

void GameView::addTeam(std::string name)
{
    std::shared_ptr<Team> team = std::make_shared<Team>(name, _scale, _teams.size());
    _teams.push_back(team);
}

void GameView::gameLoop()
{
    sf::Event event;
    int playerX, playerY;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(static_cast<float>(_gridWidth * TILE_SIZE * _scale), static_cast<float>(_gridHeight * TILE_SIZE * _scale)), "Zappy");
    Sprite title("Png/title.png", window.getSize().x / 2, window.getSize().y / 8, 10.0f);
    Sprite background("Png/bck.jpg", -425, 0, 1);
    float buttonScale = 4.0f;
    Button startButton("Png/play.png", window.getSize().x / 2 - 60, window.getSize().y / 2 + 200, buttonScale);
    Button quitButton("Png/stop.png", window.getSize().x / 2 - 60, window.getSize().y / 2 + 300, buttonScale);
    bool menu = true;

    title.setPosition(window.getSize().x / 2 + 20 - title.getSprite().getGlobalBounds().width / 2, window.getSize().y / 8);

    while (window.isOpen()) {
        if (menu) {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (startButton.isMouseOver(window)) {
                    if (event.type == sf::Event::MouseButtonPressed)
                        menu = false;
                }

                if (quitButton.isMouseOver(window)) {
                    if (event.type == sf::Event::MouseButtonPressed)
                        window.close();
                }
            }
            window.clear();
            background.draw(window);
            title.draw(window);
            startButton.draw(window);
            quitButton.draw(window);
        } else {
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Escape)
                        menu = true;
            }

            for (float x = 0; x < _gridWidth; ++x) {
                for (float y = 0; y < _gridHeight; ++y) {
                    _tiles[x][y].draw(window, x * _scale, y * _scale);
                }
            }

            for (auto& team: _teams)
                team->drawPlayers(window);
        }
        window.display();
        window.clear();
    }
}

void GameView::addTile(std::vector<std::string> commandParts)
{
    int x = std::stoi(commandParts[1]);
    int y = std::stoi(commandParts[2]);
    int food = std::stoi(commandParts[3]);
    int linemate = std::stoi(commandParts[4]);
    int deraumere = std::stoi(commandParts[5]);
    int sibur = std::stoi(commandParts[6]);
    int mendiane = std::stoi(commandParts[7]);
    int phiras = std::stoi(commandParts[8]);
    int thystame = std::stoi(commandParts[9]);

    if (food != 0)
        _tiles[x][y].addResource(Resource::Food, _resourceTextures[Resource::Food], _scale);
    if (linemate != 0)
        _tiles[x][y].addResource(Resource::Linemate, _resourceTextures[Resource::Linemate], _scale);
    if (deraumere != 0)
        _tiles[x][y].addResource(Resource::Deraumere, _resourceTextures[Resource::Deraumere], _scale);
    if (sibur != 0)
        _tiles[x][y].addResource(Resource::Sibur, _resourceTextures[Resource::Sibur], _scale);
    if (mendiane != 0)
        _tiles[x][y].addResource(Resource::Mendiane, _resourceTextures[Resource::Mendiane], _scale);
    if (phiras != 0)
        _tiles[x][y].addResource(Resource::Phiras, _resourceTextures[Resource::Phiras], _scale);
    if (thystame != 0)
        _tiles[x][y].addResource(Resource::Thystame, _resourceTextures[Resource::Thystame], _scale);
}

void GameView::createPlayer(std::vector<std::string> parameters)
{
    for (auto& team: _teams) {
        if (team->getName() == parameters[6]) {
            team->addPlayer(parameters);
            return;
        }
    }
}

void GameView::movePlayer(std::vector<std::string> parameters)
{
    int id = std::stoi(parameters[1]);
    int x = std::stoi(parameters[2]);
    int y = std::stoi(parameters[3]);
    int direction = std::stoi(parameters[4]);

    for (auto& team: _teams) {
        if (team->getPlayer(id) != nullptr)
            team->getPlayer(id)->move(x, y, direction);
    }
}

void GameView::updatePlayerLevel(std::vector<std::string> parameters)
{
    int id = std::stoi(parameters[1]);
    int level = std::stoi(parameters[2]);

    for (auto& team: _teams) {
        if (team->getPlayer(id) != nullptr) {
            team->getPlayer(id)->setLevel(level);
            team->getPlayer(id)->getLevelText();
        }
    }
}

void GameView::startLevelUp(std::vector<std::string> parameters)
{
    int id = 0;

    for (int i = 4; i < parameters.size(); ++i) {
        id = std::stoi(parameters[i]);
        for (auto& team: _teams) {
            if (team->getPlayer(id) != nullptr) {
                team->getPlayer(id)->move(std::stoi(parameters[1]), std::stoi(parameters[2]), 3);
                team->getPlayer(id)->startAura(std::stoi(parameters[3]));
            }
        }
    }
}

void GameView::endLevelUp(std::vector<std::string> parameters)
{
    for (auto& team: _teams) {
        for (auto& player: team->getAllPlayers()) {
            if (player->getAuraActive() && player->getPosition().x == std::stoi(parameters[1])
                && player->getPosition().y == std::stoi(parameters[2]))
                player->stopAura();
        }
    }
}

void GameView::deletePlayer(int id)
{
    for (auto& team : _teams) {
        if (team->getPlayer(id) != nullptr)
            team->deletePlayer(id);
    }
}

void GameView::takeObject(int id, int resource)
{
    for (auto& team : _teams) {
        if (team->getPlayer(id) != nullptr)
            team->getPlayer(id)->collectResources(_tiles, resource);
    }
}

void GameView::dropObject(int id, int resource)
{
    for (auto& team : _teams) {
        if (team->getPlayer(id) != nullptr)
            team->getPlayer(id)->dropResources(_resourceTextures, _tiles, resource);
    }
}
