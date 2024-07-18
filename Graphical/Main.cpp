/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include "GameView/GameView.hpp"

#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include "NetworkInterface/ServerConnection.hpp"

int main(int argc, char const* argv[])
{
    std::unique_ptr<ServerConnection> network = nullptr;
    std::string machine;
    struct sockaddr_in serv_addr;
    int status;
    int client_fd;
    int port = 0;

    if (argc != 3 && argc != 5) {
        std::cerr << "USAGE: ./zappy_ai -p port -h machine" << std::endl;
        std::cout << "\tport\tis the port number" << std::endl;
        std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
        return 84;
    }

    if (std::string(argv[1]) == "-p") {
        try {
            port = std::atoi(argv[2]);
        } catch (std::exception &e) {
            std::cerr << "Invalid port" << std::endl;
            return 84;
        }
    } else {
        std::cerr << "Invalid parameters" << std::endl;
        return 84;
    }

    if (argc == 5 && std::string(argv[3]) == "-h") {
        try {
            machine = argv[4];
        } catch (std::exception &e) {
            std::cerr << "Invalid machine" << std::endl;
            return 84;
        }
    } else if (argc == 3) {
        machine = "localhost";
    } else {
        std::cerr << "Invalid parameters" << std::endl;
        return 84;
    }

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return 84;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return 84;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return 84;
    }

    network = std::make_unique<ServerConnection>(client_fd);
    network->start();

    return 0;
}