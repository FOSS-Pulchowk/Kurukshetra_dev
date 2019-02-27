//
// Created by samip on 21/1/19.
//
#include <SFML/Network.hpp>
#include <iostream>
#include "GameServer.h"
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <SFML/Network/TcpSocket.hpp>

GameServer::GameServer(unsigned short port):position(0.f,0.f)
{
    m_running = true;
    if(m_listener.listen(port) == sf::Socket::Done)
    {
        std::cout << "Server is started on port: " << port <<  ". Waiting for clients.\n";
        m_selector.add(m_listener);
        m_playersConnected = 0;
        m_dataWaiting = false;
        t0 = std::thread(&GameServer::receive, this);
        t0.detach();
    }
    else
        std::cout << "Error - Failed to bind the port " << port << std::endl;
}

int GameServer::getM_playersConnected() const {
    return m_playersConnected;
}

GameServer::~GameServer(){
    m_running = false;
    socket.disconnect();
    m_listener.close();
}

void GameServer::receive() {
    while (m_running) {
        while (m_playersConnected == 0) {
            if (m_listener.accept(this->socket) == sf::Socket::Done) {
                std::cout << "Connected";
                ++m_playersConnected;
            }
        }
        if (this->m_dataWaiting){
            std::cout << "Sending data" << std::endl;
            if (socket.send(this->m_toSend) != sf::Socket::Done)
                std::cout << "Error sending KeyPress" << std::endl;
            this->m_dataWaiting = false;
        }

    }
}

void GameServer::update(sf::Vector2f position2,sf::Vector2f movement,sf::Vector2f bullet, bool isShooting) {
    sf::Packet keyPress;
    keyPress<<position2.x<<position2.y<<movement.x<<movement.y<<bullet.x<<bullet.y<<isShooting;
    std::cout<<position2.x;
        this->m_toSend = keyPress;
        this->m_dataWaiting = true;
}

