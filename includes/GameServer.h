//
// Created by samip on 21/1/19.
//

#pragma once
#include <SFML/System/Time.hpp>
#include <SFML/Network.hpp>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <SFML/Network/TcpSocket.hpp>

class GameServer {
public:
    GameServer(){};
    GameServer(unsigned short port,std::string name);
    ~GameServer();

    void receive();
    void update(sf::Vector2f position2,sf::Vector2f movement,sf::Vector2f bullet,bool isShooting,bool isJumping);
    int getM_playersConnected() const;

private:
    std::string player_name;
    bool m_running;
    bool m_dataWaiting;
    sf::Packet m_toSend;
    int m_playersConnected;
    sf::TcpListener m_listener;
    sf::SocketSelector m_selector;
    std::thread t0;
    std::mutex m_mutex;
    sf::TcpSocket socket;
};
