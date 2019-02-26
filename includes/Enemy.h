//
// Created by samip on 25/2/19.
//
//
// Created by safal on 13/2/19.
//

#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include "Animation.h"
#include "Collider.h"
#include "GameServer.h"
#include "Bullet.h"
#include <vector>

class Enemy {
public:
    Enemy(){};
    Enemy(std::unique_ptr<sf::TcpSocket> *socket, int id);
    void SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
    void Update(sf::Texture* bulletTexture, float deltaTime, sf::View &gameView, float &baseHeight, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
    Collider GetCollider() { return Collider(body); }
    void SetPosition(sf::Vector2f position);
    void setName(const std::string& name);
    void setTimeout(sf::Time time);
    void setConnected(bool status);
    void setPing(unsigned short ping);
    sf::Vector2f getPosition();
    sf::TcpSocket* getSocket();
    sf::Time getTimeout();
    std::string getName();
    bool isConnected();
    unsigned short getPing();
    int getId();
protected:
    void HitCheck(Bullet& bullet);
    bool isDead(){ return health<=0;}
    bool isUp(sf::RectangleShape& shape, float& baseHeight);
protected:
    sf::RectangleShape body;
    Animation animation;
    unsigned row;
    bool faceRight, isJumping, isShooting;
    sf::Vector2f m_position;
    sf::Time m_timeout;
    std::string m_name;
    std::unique_ptr<sf::TcpSocket> m_socket = nullptr;
    bool m_connected;
    int m_id;
    unsigned short m_ping;
    sf::Vector2f velocity, bulletVelocity, moveDirection;
    std::vector <Bullet> bullets;
public:
    int health, mana;
};