/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ServerConnection
*/

#include "ServerConnection.hpp"

ServerConnection::ServerConnection(int client_fd): _client_fd(client_fd)
{
    _gameView = nullptr;
    std::string hello = "GRAPHIC\n";
    send(client_fd, hello.c_str(), hello.length(), 0);
    _thread = nullptr;
}

ServerConnection::~ServerConnection()
{
    if (_thread->joinable())
        _thread->join();
    close(_client_fd);
}

void ServerConnection::start()
{
    _thread = std::make_unique<std::thread>(&ServerConnection::receive, this);
}

std::vector<std::string> ServerConnection::split(std::string str, char delim)
{
    std::vector<std::string> result;
    size_t pos = 0;

    while ((pos = str.find(delim)) != std::string::npos) {
        std::string pizzaStr = str.substr(0, pos);
        if (pizzaStr.length() != 0)
            result.push_back(pizzaStr);
        str.erase(0, pos + 1);
    }
    if (str.length() != 0)
        result.push_back(str);
    return result;
}

std::string ServerConnection::receive()
{
    std::string command;
    std::vector<std::string> commandParts;
    char buffer[1];
    int valread;
    bool isRunning = false;

    while (1)
    {
        valread = read(_client_fd, buffer, sizeof(buffer));
        std::cout << buffer;

        if (buffer[0] == '\n') {
            command += "\0";
            commandParts = split(command, ' ');

            if (commandParts[0] == "msz" && !isRunning) {
                _gameView = std::make_unique<GameView>(std::stoi(commandParts[1]), std::stoi(commandParts[2]));
                _gameView->startThread();
                isRunning = true;
            } else if (commandParts[0] == "bct")
                _gameView->addTile(commandParts);
            else if (commandParts[0] == "tna")
                _gameView->addTeam(commandParts[1]);
            else if (commandParts[0] == "pnw")
                _gameView->createPlayer(commandParts);
            else if (commandParts[0] == "ppo")
                _gameView->movePlayer(commandParts);
            else if (commandParts[0] == "plv")
                _gameView->updatePlayerLevel(commandParts);
            else if (commandParts[0] == "pic")
                _gameView->startLevelUp(commandParts);
            else if (commandParts[0] == "pie")
                _gameView->endLevelUp(commandParts);
            else if (commandParts[0] == "pdi")
                _gameView->deletePlayer(std::stoi(commandParts [1]));
            else if (commandParts[0] == "pgt")
                _gameView->takeObject(std::stoi(commandParts [1]), std::stoi(commandParts [2]));
            else if (commandParts[0] == "pdr")
                _gameView->dropObject(std::stoi(commandParts [1]), std::stoi(commandParts [2]));

            command = "";
        } else
            command += buffer;
    }
}
