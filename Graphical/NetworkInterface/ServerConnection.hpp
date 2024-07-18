/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ServerConnection
*/

#ifndef SERVERCONNECTION_HPP_
#define SERVERCONNECTION_HPP_

#include <string>
#include <stdexcept>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include "../GameView/GameView.hpp"

class ServerConnection {
    public:
        ServerConnection(int client_fd);
        ~ServerConnection();

        void start();
        void updatePlayerLevel(std::vector<std::string> parameters);

        std::vector<std::string> split(std::string str, char delim);
        std::string receive();

    private:
        std::unique_ptr<std::thread> _thread;
        std::unique_ptr<GameView> _gameView;
        int _client_fd;
};

#endif // SERVERCONNECTION_HPP_
